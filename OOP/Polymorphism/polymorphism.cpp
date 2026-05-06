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
    {}

    int x() const { return x_; }
    int y() const { return y_; }

    void move(int dx, int dy)
    {
        x_ += dx;
        y_ += dy;
    }
};

class Shape
{
    Coordinate coord_;
public:

    Shape(int x, int y) : coord_{x, y}
    {}

    Shape(const Shape& other) = default;
    Shape& operator=(const Shape& other) = default;
    Shape(Shape&& other) = default;
    Shape& operator=(Shape&& other) = default;
 
    virtual ~Shape() = default;

    virtual void draw() = 0; // abstract method

    void move(int dx, int dy)
    {
        coord_.move(dx, dy);
    }
protected:
    int x() const { return coord_.x(); }
    int y() const { return coord_.y(); }
};

class Square : public Shape
{
    int size_;
public:

    Square(int x, int y, int size) : Shape{x, y}, size_{size}
    {
        assert(size_ >= 0);
    }

    void draw() override
    {
        std::cout << "Square(x: " << x() << ", y: " << y()   << ", size: " << size_ << ")\n";
    }
};

class Rectangle : public Shape
{
    int width_;
    int height_;
public:
    Rectangle(int x, int y, int width, int height) : Shape{x, y}, width_{width}, height_{height}
    {
        assert(width_ >= 0);
        assert(height_ >= 0);
    }

    void draw() override
    {
        std::cout << "Rectangle(x: " << x() << ", y: " << y() << ", width: " << width_ << ", height: " << height_ << ")\n";
    }
};

// Clients using Shape base class (interface)

void draw_shape(Shape& shp)
{
    shp.draw();
    shp.move(10, 20);
    shp.draw();
}

void draw_shapes(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    for(const auto& shp : shapes)
    {
        shp->draw();
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

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(100, 200, 40, 6));

    shapes.push_back(std::make_unique<Square>(600, 300, 42));

    draw_shapes(shapes);
}