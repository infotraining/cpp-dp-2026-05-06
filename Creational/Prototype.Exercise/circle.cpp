#include "circle.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance()
                             .register_creator(Circle::id, [] { return make_unique<Circle>(); });
}

Circle::Circle(int x, int y, int r)
    : ShapeBase{x, y}
    , radius_{r}
{
}

void Circle::draw() const
{
    std::cout << "Drawing a circle at " << coord() << " with radius: " << radius_ << std::endl;
}
