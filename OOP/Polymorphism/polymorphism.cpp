#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <set>
#include <variant>
#include <vector>
#include <cassert>

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
    virtual void draw() = 0;
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

protected:
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

    void draw() override
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

    void draw() override
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

    void draw() override
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

    void draw() override
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

// Clients using Shape base class (interface)

void draw_shape(IShape &shp)
{
    shp.draw();
    shp.move(10, 20);
    shp.draw();
}

void draw_shapes(const std::vector<std::unique_ptr<IShape>> &shapes)
{
    for (const auto &shp : shapes)
    {
        shp->draw(); // late binding (dynamic dispatch) to call the correct draw() method for each shape type
    }
}

int main()
{
    std::cout << "Polymorphism" << std::endl;

    // Shape shp_1{100, 200};
    Square sq_1{100, 200, 50};
    draw_shape(sq_1);

    Rectangle rec_1{100, 200, 50, 70};

    draw_shape(rec_1);

    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(100, 200, 40, 6));

    shapes.push_back(std::make_unique<Square>(600, 300, 42));
    shapes.push_back(std::make_unique<Circle>(400, 500, 30));
    shapes.push_back(std::make_unique<Triangle>(Coordinate{100, 200}, Coordinate{150, 250}, Coordinate{200, 200}));

    draw_shapes(shapes);
}