#ifndef DECORATOR_HPP_
#define DECORATOR_HPP_

#include <SFML/Graphics.hpp>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <string>

template <size_t N>
struct StaticString
{
    char str_[N]{};

    constexpr StaticString(const char (&s)[N])
    {
        std::ranges::copy(s, str_);
    }

    constexpr operator const char*() const { return str_; }
    constexpr std::string_view view() const { return {str_, N - 1}; }
    operator std::string() const { return std::string{str_}; }

    auto operator<=>(const StaticString&) const = default;

    constexpr bool empty() const { return N <= 1; }
};

struct BoundingBox
{
    int x, y;
    size_t width, height;
};

class PhotoBuilder;

class Photo
{
public:
    virtual ~Photo() = default;
    virtual void draw(sf::RenderWindow& render_wnd, size_t x, size_t y) const = 0;
    virtual BoundingBox bounding_box() const = 0;

    static PhotoBuilder load_photo(const std::filesystem::path& image_path);
};

class PhotoComponent : public Photo
{
    sf::Texture image_;
    static constexpr size_t width_ = 300;
    static constexpr size_t height_ = 200;

public:
    explicit PhotoComponent(const std::filesystem::path& image_path)
        : image_{image_path}
    {
    }

    void draw(sf::RenderWindow& render_wnd, size_t x, size_t y) const override
    {
        sf::Sprite sprite(image_);
        sprite.setPosition(sf::Vector2f{static_cast<float>(x), static_cast<float>(y)});
        render_wnd.draw(sprite);
    }

    BoundingBox bounding_box() const override
    {
        return {0, 0, width_, height_};
    }
};

class PhotoDecorator : public Photo, public std::enable_shared_from_this<PhotoDecorator>
{
    std::shared_ptr<Photo> photo_;
    std::optional<std::string> decorator_tag_;

public:
    explicit PhotoDecorator(std::shared_ptr<Photo> photo, std::optional<std::string> decorator_tag = std::nullopt)
        : photo_{std::move(photo)}
        , decorator_tag_{std::move(decorator_tag)}
    {
    }

    void draw(sf::RenderWindow& render_wnd, size_t x, size_t y) const override
    {
        assert(photo_);
        photo_->draw(render_wnd, x, y);
    }

    BoundingBox bounding_box() const override
    {
        assert(photo_);
        return photo_->bounding_box();
    }

    void set_photo(std::shared_ptr<Photo> photo)
    {
        photo_ = std::move(photo);
    }

    void set_tag(const std::string& tag)
    {
        decorator_tag_ = tag;
    }

    std::shared_ptr<Photo> remove_decorator(const std::string& tag)
    {                                
        if (decorator_tag_ == tag)
        {
            return photo_;
        }
        else
        {
            if (auto decorator = std::dynamic_pointer_cast<PhotoDecorator>(photo_); decorator)
            {
                photo_ = decorator->remove_decorator(tag);
            }
        }
        return shared_from_this();
    }
};

class BorderedPhoto : public PhotoDecorator
{
    sf::Color border_color_;
    size_t border_width_;

public:
    BorderedPhoto(std::shared_ptr<Photo> photo, sf::Color border_color = sf::Color::White, size_t border_width = 100)
        : PhotoDecorator(std::move(photo))
        , border_color_{border_color}
        , border_width_{border_width}
    {
    }

    void draw(sf::RenderWindow& render_wnd, size_t x, size_t y) const override
    {
        BoundingBox bbox = PhotoDecorator::bounding_box();
        sf::RectangleShape border(sf::Vector2f{static_cast<float>(bbox.width + (2 * border_width_)), static_cast<float>(bbox.height) + (2 * border_width_)});
        border.setPosition({static_cast<float>(x), static_cast<float>(y)});
        border.setOutlineColor(sf::Color::Black);
        border.setOutlineThickness(1);
        border.setFillColor(border_color_);

        // Draw the border first
        render_wnd.draw(border);

        // Then draw the photo
        PhotoDecorator::draw(render_wnd, x + border_width_, y + border_width_);
    }

    BoundingBox bounding_box() const override
    {
        // Adjust the bounding box to account for the border
        BoundingBox bbox = PhotoDecorator::bounding_box();
        return {bbox.x, bbox.y, bbox.width + 2 * border_width_, bbox.height + 2 * border_width_};
    }
};

class TaggedPhoto : public PhotoDecorator
{
    std::string tag_;

public:
    TaggedPhoto(std::shared_ptr<Photo> photo, const std::string& tag)
        : PhotoDecorator(std::move(photo))
        , tag_{tag}
    {
    }

    void draw(sf::RenderWindow& render_wnd, size_t x, size_t y) const override
    {
        sf::Font font("roboto.ttf");   // Load a font file
        sf::Text text(font, tag_, 20); // Create a text object with the font and tag

        // Draw the photo first
        PhotoDecorator::draw(render_wnd, x, y);

        // Then draw the tag
        BoundingBox bbox = PhotoDecorator::bounding_box();
        text.setPosition({static_cast<float>(x), static_cast<float>(y + bbox.height)});
        text.setFillColor(sf::Color::White);
        render_wnd.draw(text); // Draw the text on the window
    }

    BoundingBox bounding_box() const override
    {
        // Adjust the height to account for the text
        BoundingBox bbox = PhotoDecorator::bounding_box();
        return {bbox.x, bbox.y, bbox.width, bbox.height + 20}; // Add space for the tag
    }
};

class PhotoBuilder
{
    std::shared_ptr<Photo> photo_;

public:
    PhotoBuilder(std::shared_ptr<Photo> photo)
        : photo_{std::move(photo)}
    {
    }

    template <StaticString decorator_tag = "">
    PhotoBuilder& add_border(sf::Color border_color = sf::Color::White, size_t border_width = 100)
    {
        auto decorated_photo = std::make_shared<BorderedPhoto>(photo_, border_color, border_width);

        if (!decorator_tag.empty())
            decorated_photo->set_tag(decorator_tag);

        photo_ = decorated_photo;
        return *this;
    }

    template <StaticString decorator_tag = "">
    PhotoBuilder& add_tag(const std::string& tag)
    {
        auto decorated_photo = std::make_shared<TaggedPhoto>(photo_, tag);

        if (!decorator_tag.empty())
            decorated_photo->set_tag(decorator_tag);

        photo_ = decorated_photo;
        return *this;
    }

    std::shared_ptr<Photo> build() const
    {
        return photo_;
    }
};

PhotoBuilder Photo::load_photo(const std::filesystem::path& image_path)
{
    auto photo = std::make_shared<PhotoComponent>(image_path);
    return PhotoBuilder{std::move(photo)};
}

#endif /*DECORATOR_HPP_*/
