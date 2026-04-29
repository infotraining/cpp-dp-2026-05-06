#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

#include <memory>

namespace Drawing
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int dx, int dy) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<Shape> clone() const = 0;
    };

    template <typename Type, typename BaseType = Shape>
    class CloneableShape : public BaseType
    {
    public:
        using BaseType::BaseType;

        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<Type>(static_cast<const Type&>(*this));
        }
    };

    template <typename Type>
    class ShapeBase : public CloneableShape<Type>
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
} // namespace Drawing

#endif // SHAPE_HPP
