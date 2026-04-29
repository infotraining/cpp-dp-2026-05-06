#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

namespace Drawing
{
    class Circle : public ShapeBase<Circle>
    {
        int radius_;

    public:
        static constexpr const char* id = "Circle";

        Circle(int x = 0, int y = 0, int r = 0);

        int radius() const;

        void set_radius(int radius);

        void draw() const override;
    };
}

#endif // CIRCLE_H
