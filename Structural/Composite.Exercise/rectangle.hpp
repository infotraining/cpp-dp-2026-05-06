#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace Drawing
{

    class Rectangle : public ShapeBase<Rectangle>
    {
        int width_, height_;

    public:
        static constexpr const char* id = "Rectangle";

        Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);

        int width() const
        {
            return width_;
        }

        void set_width(int w)
        {
            width_ = w;
        }

        int height() const
        {
            return height_;
        }

        void set_height(int h)
        {
            height_ = h;
        }

        void draw() const override;
    };
}
#endif // RECTANGLE_HPP
