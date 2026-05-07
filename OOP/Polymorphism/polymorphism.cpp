#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <set>
#include <variant>
#include <vector>
#include <cassert>

namespace Polymorphism
{
    class Coordinate
    {
        int x_;
        int y_;

    public:
        Coordinate(int x, int y) : x_{x}, y_{y}
        {
        }

        int x() const { return x_; }
        int y() const { return y_; }

        void move(int dx, int dy)
        {
            x_ += dx;
            y_ += dy;
        }

        friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord)
        {
            os << "(" << coord.x() << ", " << coord.y() << ")";
            return os;
        }
    };

    // Interface for shapes
    class IShape
    {
    public:
        virtual void draw() const = 0;
        virtual void move(int dx, int dy) = 0;
        virtual ~IShape() = default;
    };

    // Abstract base class for shapes with common functionality: position (x, y) and move() method
    class ShapeBase : public IShape
    {
        Coordinate coord_;

    public:
        ShapeBase(int x, int y) : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.move(dx, dy);
        }

        int x() const { return coord_.x(); }
        int y() const { return coord_.y(); }
    };

    class Rectangle : public ShapeBase // hybrid inheritance: inherits from ShapeBase (abstract base class) and implements IShape interface
    {
        int width_;
        int height_;

    public:
        Rectangle(int x, int y, int width, int height) : ShapeBase{x, y}, width_{width}, height_{height}
        {
            assert(width_ >= 0);
            assert(height_ >= 0);
        }

        Rectangle(const Rectangle &source) : ShapeBase{source}, width_{source.width_}, height_{source.height_}
        {
            std::cout << "Rectangle(cc - coordinate: " << source.x() << ", " << source.y() << ", width: " << source.width_ << ", height: " << source.height_ << ")\n";
        }

        Rectangle &operator=(const Rectangle &source)
        {
            if (this != &source)
            {
                ShapeBase::operator=(source); // copy base class part
                width_ = source.width_;
                height_ = source.height_;
                std::cout << "Rectangle(= - coordinate: " << source.x() << ", " << source.y() << ", width: " << source.width_ << ", height: " << source.height_ << ")\n";
            }
            return *this;
        }

        Rectangle(Rectangle&&) = default;
        Rectangle& operator=(Rectangle&&) = default;

        void draw() const override
        {
            std::cout << "Rectangle(x: " << x() << ", y: " << y() << ", width: " << width_ << ", height: " << height_ << ")\n";
        }

        int width() const { return width_; }
        int height() const { return height_; }

        void set_width(int width)
        {
            assert(width >= 0);
            width_ = width;
        }

        void set_height(int height)
        {
            assert(height >= 0);
            height_ = height;
        }
    };

    class Square : public IShape
    {
        Rectangle rect_; // composition: Square has a Rectangle to reuse its functionality for width and height management
    public:
        Square(int x, int y, int size) : rect_{x, y, size, size}
        {
            assert(rect_.width() == rect_.height()); // invariant: width and height must be equal for a square
        }

        Square(const Square &source) : rect_{source.rect_}
        {
            std::cout << "Square(cc - coordinate: " << source.rect_.x() << ", " << source.rect_.y() << ", size: " << source.size() << ")\n";
        }

        Square &operator=(const Square &source)
        {
            if (this != &source)
            {
                rect_ = source.rect_;
                std::cout << "Square(= - coordinate: " << source.rect_.x() << ", " << source.rect_.y() << ", size: " << source.size() << ")\n";
            }
            return *this;
        }

        Square(Square&&) = default;
        Square& operator=(Square&&) = default;

        void draw() const override
        {
            rect_.draw(); // delegate drawing to the Rectangle's draw() method
        }

        void move(int dx, int dy) override
        {
            rect_.move(dx, dy); // delegate movement to the Rectangle's move() method
        }

        int size() const { return rect_.width(); }

        void set_size(int size)
        {
            assert(size >= 0);
            rect_.set_width(size);
            rect_.set_height(size);
            assert(rect_.width() == rect_.height()); // invariant: width and height must be equal for a square
        }
    };

    class Circle : public ShapeBase
    {
        int radius_;

    public:
        Circle(int x, int y, int radius) : ShapeBase{x, y}, radius_{radius}
        {
            assert(radius_ >= 0);
        }

        Circle(const Circle &source) : ShapeBase{source}, radius_{source.radius_}
        {
            std::cout << "Circle(cc - coordinate: " << source.x() << ", " << source.y() << ", radius: " << source.radius_ << ")\n";
        }

        Circle &operator=(const Circle &source)
        {
            if (this != &source)
            {
                ShapeBase::operator=(source); // copy base class part
                radius_ = source.radius_;
                std::cout << "Circle(= - coordinate: " << source.x() << ", " << source.y() << ", radius: " << source.radius_ << ")\n";
            }
            return *this;
        }

        Circle(Circle&&) = default;
        Circle& operator=(Circle&&) = default;

        void draw() const override
        {
            std::cout << "Circle(x: " << x() << ", y: " << y() << ", radius: " << radius_ << ")\n";
        }
    };

    class Triangle : public IShape // interface inheritance
    {
        std::array<Coordinate, 3> vertices_;

    public:
        Triangle(const Coordinate &v1, const Coordinate &v2, const Coordinate &v3) : vertices_{v1, v2, v3}
        {
        }

        Triangle(const Triangle &source) : vertices_{source.vertices_}
        {
            std::cout << "Triangle(cc - v1: " << source.vertices_[0] << ", v2: " << source.vertices_[1] << ", v3: " << source.vertices_[2] << ")\n";
        }

        Triangle &operator=(const Triangle &source)
        {
            if (this != &source)
            {
                vertices_ = source.vertices_;
                std::cout << "Triangle(= - v1: " << source.vertices_[0] << ", v2: " << source.vertices_[1] << ", v3: " << source.vertices_[2] << ")\n";
            }
            return *this;
        }

        Triangle(Triangle&&) = default;
        Triangle& operator=(Triangle&&) = default;

        void draw() const override
        {
            std::cout << "Triangle(v1: " << vertices_[0] << ", v2: " << vertices_[1] << ", v3: " << vertices_[2] << ")\n";
        }

        void move(int dx, int dy) override
        {
            for (auto &vertex : vertices_)
            {
                vertex.move(dx, dy);
            }
        }
    };
}

// Clients using Shape base class (interface)

void draw_shape(Polymorphism::IShape &shp)
{
    shp.draw();
    shp.move(10, 20);
    shp.draw();
}

void draw_shapes(const std::vector<std::unique_ptr<Polymorphism::IShape>> &shapes)
{
    for (const auto &shp : shapes)
    {
        shp->draw(); // late binding (dynamic dispatch) to call the correct draw() method for each shape type
    }
}

namespace Cpp26
{
    class Picture
    {
        using ShapePtr = std::polymorphic<Polymorphism::IShape>;
        std::vector<ShapePtr> shapes_;

    public:
        Picture() = default;

        template <typename TShape>
        void add_shape(TShape&& shape)
        {
            shapes_.emplace_back(std::forward<TShape>(shape)); // store shapes as polymorphic pointers
        }

        void draw() const
        {
            for(const auto& shp : shapes_)
            {
                shp->draw();
            }
        }
    };
};

void polymorphism_demo()
{
    using namespace Polymorphism;

    Square sq{100, 200, 50};
    draw_shape(sq);

    Rectangle rec{100, 200, 50, 70};
    draw_shape(rec);

    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(100, 200, 40, 60));
    shapes.push_back(std::make_unique<Square>(600, 300, 42));
    shapes.push_back(std::make_unique<Circle>(400, 500, 30));
    shapes.push_back(std::make_unique<Triangle>(Coordinate{100, 200}, Coordinate{150, 250}, Coordinate{200, 200}));

    draw_shapes(shapes);
}

void cpp26_polymorphic_demo()
{
    using namespace Polymorphism;

    // C++26 polymorphic pointer usage
    std::polymorphic<IShape> shape{Rectangle{100, 200, 50, 70}};
    shape->draw();

    shape = std::polymorphic<IShape>{Square{300, 400, 60}}; // polymorphic pointer can point to different shape types
    shape->draw();

    shape = std::polymorphic<IShape>{Circle{500, 600, 40}};
    shape->draw();

    std::cout << "\nDrawing picture with multiple shapes:\n";

    Cpp26::Picture picture;
    picture.add_shape(Rectangle{100, 200, 40, 60});
    picture.add_shape(Square{600, 300, 42});
    picture.add_shape(Circle{400, 500, 30});
    picture.add_shape(Triangle{Coordinate{100, 200}, Coordinate{150, 250}, Coordinate{200, 200}});
    picture.draw();

    std::cout << "\nCopying picture:\n";

    Cpp26::Picture picture2 = picture; // copy constructor of Picture will copy the polymorphic pointers, which will in turn copy the shapes they point to
    std::cout << "\nDrawing copied picture:\n";
    picture2.draw();
}

int main()
{
    //polymorphism_demo();


    cpp26_polymorphic_demo();
}