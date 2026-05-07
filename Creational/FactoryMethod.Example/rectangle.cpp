#include "rectangle.hpp"
#include <memory>
#include "generic_factory.hpp"

static bool is_registered = SingletonShapeFactory::instance().register_creator(Drawing::Rectangle::id, []() { return std::make_unique<Drawing::Rectangle>(); });

Drawing::Rectangle::Rectangle(int x, int y, int w, int h)
    : ShapeBase{x, y}
    , width_{w}
    , height_{h}
{
}

void Drawing::Rectangle::draw() const
{
    std::cout << "Drawing rectangle at " << coord() << " with width: " << width_
              << " and height: " << height_ << std::endl;
}
