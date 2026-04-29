#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <variant>
#include <vector>
#include <cstdint>

struct Color
{
    uint8_t r, g, b;
};

namespace Inheritance
{
    class TextParagraph
    {
        std::string text_;
        Color color_;

    public:
        TextParagraph(std::string text, Color color)
            : text_(std::move(text))
            , color_(std::move(color))
        {
        }

        const std::string& text() const
        {
            return text_;
        }

        virtual void render(size_t line_width) const
        {
            std::cout << "[" << text() << std::setw(line_width - text().length()) << std::right << "" << "]\n";
        }

        virtual ~TextParagraph() noexcept = default;

        // other methods...
    };

    class RightAlignedTextParagraph : public TextParagraph
    {
    public:
        using TextParagraph::TextParagraph;

        void render(size_t line_width) const override
        {
            std::cout << "[" << std::setw(line_width) << std::right << text() << "]\n";
        }
    };

    class CenteredAlignedTextParagraph : public TextParagraph
    {
    public:
        using TextParagraph::TextParagraph;

        void render(size_t line_width) const override
        {
            auto pad_left = (line_width - text().length()) / 2;
            auto pad_right = line_width - text().length() - pad_left;
            std::cout << "[" << std::setw(pad_left) << "" << text() << std::setw(pad_right) << "" << "]\n";
        }
    };
} // namespace Inheritance

namespace Delegation
{
    class TextAlignment
    {
    public:
        virtual std::string aligned_text(const std::string& text, size_t line_width) const = 0;
        virtual ~TextAlignment() = default;
    };

    class LeftAlignment : public TextAlignment
    {
    public:
        std::string aligned_text(const std::string& text, size_t line_width) const override
        {
            std::stringstream out_str;
            out_str << text << std::setw(line_width - text.length()) << std::right << "";
            return out_str.str();
        }
    };

    class CenterAlignment : public TextAlignment
    {
    public:
        std::string aligned_text(const std::string& text, size_t line_width) const override
        {
            std::stringstream out_str;
            auto pad_left = (line_width - text.length()) / 2;
            auto pad_right = line_width - text.length() - pad_left;
            out_str << std::setw(pad_left) << "" << text << std::setw(pad_right) << "";
            return out_str.str();
        }
    };

    class RightAlignment : public TextAlignment
    {
    public:
        std::string aligned_text(const std::string& text, size_t line_width) const override
        {
            std::stringstream out_str;
            out_str << std::setw(line_width) << std::right << text;
            return out_str.str();
        };
    };

    class TextParagraph
    {
        std::string text_;
        Color color_;
        std::unique_ptr<TextAlignment> alignment_;

    public:
        TextParagraph(std::string text, Color color, std::unique_ptr<TextAlignment> alignment = std::make_unique<LeftAlignment>())
            : text_(std::move(text))
            , color_(std::move(color))
            , alignment_{std::move(alignment)}
        {
        }

        void set_alignment(std::unique_ptr<TextAlignment> alignment)
        {
            alignment_ = std::move(alignment);
        }

        void render(size_t line_width) const
        {
            std::cout << "[" << alignment_->aligned_text(text_, line_width) << "]\n";
        }
    };
} // namespace Delegation

void use_inheritance()
{
    using namespace Inheritance;

    TextParagraph left_aligned{"This is sample of text...", Color{0, 0, 0}};
    RightAlignedTextParagraph right_aligned{"This is sample of text...", Color{0, 0, 0}};
    CenteredAlignedTextParagraph center_aligned{"This is sample of text...", Color{0, 0, 0}};

    left_aligned.render(80);
    right_aligned.render(80);
    center_aligned.render(80);
}

void use_delegation()
{
    using namespace Delegation;
    
    TextParagraph text{"This is sample of text...", Color{0, 0, 0}};
    text.render(80);

    text.set_alignment(std::make_unique<RightAlignment>());
    text.render(80);

    text.set_alignment(std::make_unique<CenterAlignment>());
    text.render(80);
}

int main()
{
    use_inheritance();

    std::cout << "\n-----------------\n\n";

    use_delegation();
}