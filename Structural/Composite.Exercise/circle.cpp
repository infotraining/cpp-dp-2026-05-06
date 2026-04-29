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
    : ShapeBase{x, y}, radius_{r}
{
}

int Circle::radius() const
{
    return radius_;
}

void Circle::set_radius(int radius)
{
    radius_ = radius;
}

void Circle::draw() const
{
    cout << "Drawing a circle at " << coord() << " with radius " << radius() << endl;
}
