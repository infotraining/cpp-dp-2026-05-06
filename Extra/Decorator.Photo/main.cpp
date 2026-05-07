#include "decorator.hpp"

#include <iostream>
#include <memory>
#include <ranges>
#include <vector>

void render_album(sf::RenderWindow& render_wnd, const std::vector<std::shared_ptr<Photo>>& photos)
{
    const size_t dx = 10;
    const size_t dy = 20;

    size_t x = 10;
    size_t y = 10;

    for (const auto& photo : photos)
    {
        photo->draw(render_wnd, x, y);
        x += photo->bounding_box().width + dx; // Adjust x position for the next photo

        if (x > render_wnd.getSize().x - photo->bounding_box().width) // If the next photo goes out of bounds, reset x and move down
        {
            x = 10;                                 // Reset x position
            y += photo->bounding_box().height + dy; // Adjust y position for the next row
        }
    }
}

int main()
{
    // Load the photos from the current directory
    std::vector<std::shared_ptr<Photo>> photos;

    auto is_jpg_file = [](const std::filesystem::directory_entry& entry) {
        return entry.is_regular_file() && entry.path().extension() == ".jpg";
    };

    // for (const auto& entry : std::filesystem::directory_iterator(".") | std::views::filter(is_jpg_file))
    // {
    //     auto photo = std::make_shared<PhotoComponent>(entry.path());
    //     auto bordered_photo_1 = std::make_shared<BorderedPhoto>(photo, sf::Color(210, 210, 200), 10);
    //     auto bordered_photo_2 = std::make_shared<BorderedPhoto>(bordered_photo_1, sf::Color::White, 40);
    //     auto tagged_photo = std::make_shared<TaggedPhoto>(bordered_photo_2, entry.path().filename().string());
    //     tagged_photo = std::make_shared<TaggedPhoto>(tagged_photo, "Mountains");

    //     photos.push_back(tagged_photo);
    // }

    for (const auto& entry : std::filesystem::directory_iterator(".") | std::views::filter(is_jpg_file))
    {
        auto photo = Photo::load_photo(entry.path())
                         .add_border<"border-1">(sf::Color(210, 210, 200), 20)
                         .add_border<"border-2">(sf::Color::White, 50)
                         .add_tag<"filename">(entry.path().filename().string())
                         .add_tag<"keyword">("Mountains");
        photos.push_back(photo.build());
    }

    // photos[1] = std::dynamic_pointer_cast<PhotoDecorator>(photos[1])->remove_decorator("border-1");
    // photos[2] = std::dynamic_pointer_cast<PhotoDecorator>(photos[2])->remove_decorator("border-2");
    // photos[3] = std::dynamic_pointer_cast<PhotoDecorator>(photos[3])->remove_decorator("filename");
    // photos[4] = std::dynamic_pointer_cast<PhotoDecorator>(photos[4])->remove_decorator("keyword");

    // Create the window
    sf::RenderWindow window(sf::VideoMode({1500, 1000}), "My window");

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        render_album(window, photos);

        window.display();
    }
}
