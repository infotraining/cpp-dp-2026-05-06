#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"
#include <string>

namespace Drawing
{
    // TODO: Adapt LegacyCode::Paragraph class to Shape interface
    // Hint#1: Use Class Adapter
    // Hint#2: Register Text creator in SingletonShapeFactory
    class Text : public ShapeBase, private LegacyCode::Paragraph
    {
    public:
        static constexpr const char *id = "Text";

        Text(int x = 0, int y = 0, const std::string &txt = "");
        std::string text() const;
        void set_text(const std::string &txt);
        void draw() const override;
    };
}

#endif
