#include "rectangle.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance()
                             .register_creator(Rectangle::id, [] { return make_unique<Rectangle>(); });
}

Rectangle::Rectangle(int x, int y, int w, int h)
    : ShapeBase{x, y}, width_{w}, height_{h}
{
}

void Rectangle::draw() const
{
    std::cout << "Drawing rectangle at " << coord() << " with width: " << width_
              << " and height: " << height_ << std::endl;
}
