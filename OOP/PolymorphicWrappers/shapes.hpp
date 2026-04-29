#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <array>
#include <iostream>
#include <memory>
#include <vector>

namespace PolymorphicWrappers
{
    ////////////////////////////////////////////////////////////
    // Polymorphic wrapper for shapes   
    ////////////////////////////////////////////////////////////

    class Shape
    {
        // shape interface - implementation detail
        class IShape
        {
        public:
            virtual ~IShape() = default;
            virtual void move(int x, int y) = 0;
            virtual void draw() const = 0;
            virtual std::unique_ptr<IShape> clone() = 0;
        };

        template <typename T>
        class ShapeWrapper : public IShape
        {
            T shape_;

        public:
            ShapeWrapper(const T& shp)
                : shape_(shp)
            {
            }

            ShapeWrapper(T&& shp)
                : shape_(std::move(shp))
            {
            }

            void draw() const override
            {
                shape_.draw();
            }

            void move(int x, int y) override
            {
                shape_.move(x, y);
            }

            std::unique_ptr<IShape> clone() override
            {
                return std::make_unique<ShapeWrapper<T>>(shape_);
            }
        };

    public:
        template <typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, Shape>>>
        Shape(T&& shp)
            : shape_(std::make_unique<ShapeWrapper<std::decay_t<T>>>(std::forward<T>(shp)))
        {
        }

        Shape(const Shape& src)
            : shape_{src.shape_->clone()}
        {
        }

        Shape& operator=(const Shape& src)
        {
            Shape temp(src);
            swap(temp);

            return *this;
        }

        template <class T>
        Shape& operator=(T&& src)
        {
            Shape(std::forward<T>(src)).swap(*this);
            return *this;
        }

        Shape(Shape&&) noexcept = default;
        Shape& operator=(Shape&&) noexcept = default;

        void swap(Shape& other)
        {
            shape_.swap(other.shape_);
        }

        void draw() const
        {
            shape_->draw();
        }

        void move(int x, int y)
        {
            shape_->move(x, y);
        }

    private:
        std::unique_ptr<IShape> shape_;
    };

    ////////////////////////////////////////////////////////////
    // Concrete shapes
    ////////////////////////////////////////////////////////////

    struct Circle
    {
        int x, y;
        int r;

        Circle(int x, int y, int r)
            : x{x}
            , y{y}
            , r{r}
        {
        }

        void draw() const
        {
            std::cout << "Circle([" << x << ", " << y << "], " << r << ")\n";
        }

        void move(int dx, int dy)
        {
            x += dx;
            y += dy;
        }
    };

    struct Square
    {
        int x, y;
        int size;

        Square(int x, int y, int r)
            : x{x}
            , y{y}
            , size{r}
        {
        }

        void draw() const
        {
            std::cout << "Square([" << x << ", " << y << "], " << size << ")\n";
        }

        void move(int dx, int dy)
        {
            x += dx;
            y += dy;
        }
    };

    struct Point
    {
        int x, y;
    };

    struct Triangle
    {
        std::array<Point, 3> vertices;

        void draw() const
        {
            std::cout << "Triangle({ ";
            for (const Point& v : vertices)
                std::cout << "[" << v.x << ", " << v.y << "]"
                          << " ";
            std::cout << "})\n";
        }

        void move(int dx, int dy)
        {
            for (auto& v : vertices)
            {
                v.x += dx;
                v.y += dy;
            }
        }
    };

} // namespace PolymorphicWrappers

#endif