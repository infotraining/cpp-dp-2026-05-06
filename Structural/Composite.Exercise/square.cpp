#include "square.hpp"
#include "shape_factories.hpp"
#include <cassert>

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance()
                             .register_creator(Square::id, [] { return make_unique<Square>(); });
}

Square::Square(int x, int y, int size) : rect_{x, y, size, size}
{
}

void Square::move(int dx, int dy)
{
    rect_.move(dx, dy);
}

Point Square::coord() const
{
    return rect_.coord();
}

void Square::set_coord(const Point& pt)
{
    rect_.set_coord(pt);
}

int Square::size() const
{
    return rect_.height();
}

void Square::set_size(int size)
{
    rect_.set_width(size);
    rect_.set_height(size);

    assert(rect_.width() == rect_.height());
}

void Square::draw() const
{
    rect_.draw();
}
