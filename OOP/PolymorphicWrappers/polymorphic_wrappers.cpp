#include "shapes.hpp"

#include <variant>

using namespace PolymorphicWrappers;

class GraphicsDoc
{
    std::vector<Shape> shapes_;

public:
    GraphicsDoc() = default;

    GraphicsDoc(const std::vector<Shape>& shapes)
        : shapes_(shapes)
    {
    }

    void add(Shape shp)
    {
        shapes_.push_back(shp);
    }

    void draw() const
    {
        std::cout << "GraphicsDoc{\n";
        for (const auto& shp : shapes_)
        {
            std::cout << " + ";
            shp.draw();
        }
        std::cout << "}\n";
    }

    void move(int dx, int dy)
    {
        for (auto& shp : shapes_)
            shp.move(dx, dy);
    }
};

int main(int argc, char* argv[])
{
    Shape shp1 = Circle(1, 2, 10);
    shp1.draw();
    shp1 = Square(50, 10, 120);

    std::cout << "\n\n";

    Shape shp2 = shp1;
    shp1 = Square(30, 40, 100);

    shp1.draw();
    shp2.draw();

    std::cout << "\n\n";

    Shape shp3 = Circle(10, 20, 100);
    Shape shp4 = Square(100, 200, 10);
    Shape temp = shp3;
    shp3 = shp4;
    shp4 = temp;

    shp3.draw();
    shp4.draw();

    std::cout << "\n\n";

    std::vector<Shape> shapes = {shp1, shp2, Circle(100, 200, 2), Square{10, 20, 300}, Triangle{{Point{0, 10}, Point{10, 20}, Point{40, 70}}}};

    shp1.move(10, 1000);
    shp1.draw();

    for (const auto& shp : shapes)
        shp.draw();

    std::cout << "\n\n";
    std::cout << "Graphics document:\n";

    GraphicsDoc doc(shapes);
    doc.add(Circle(1, 1, 20));
    doc.add(Square(2, 3, 10));
    doc.add(Triangle{{Point{0, 0}, Point{10, 0}, Point{10, 10}}});
    doc.draw();

    std::cout << "\n\nMoving coordinates:\n";
    doc.move(1, 2);
    doc.draw();
}

/////////////////////////////////////////////////////////////////////////////
// Restricted polymorphism with std::variant

class ShapeVariant
{
    using ShapeVariantT = std::variant<Circle, Triangle, Square>;
    ShapeVariantT shape_;

public:
    template <typename T>
    ShapeVariant(const T& shp)
        : shape_{shp}
    { }

    void draw() const
    {
        std::visit([](const auto& s) { s.draw(); }, shape_);
    }

    void move(int dx, int dy)
    {
        std::visit([dx, dy](auto& s) { s.move(dx, dy); }, shape_);
    }
};

void test_shape_variant()
{
    ShapeVariant sv = Circle(10, 20, 100);
    sv.draw();
    sv.move(10, 20);
    sv.draw();
}