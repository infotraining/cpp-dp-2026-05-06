#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"

namespace Drawing
{
    class Text : public ShapeBase<Text>, private LegacyCode::Paragraph
    {
    public:
        static constexpr const char* id = "Text";

        Text(int x = 0, int y = 0, const std::string& content = "");

        std::string text() const;

        void set_text(const std::string& text);

        void draw() const override;
    };
}

#endif // TEXT_HPP
