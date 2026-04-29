#include "square.hpp"
#include <cassert>

Drawing::Square::Square(int x, int y, int size)
    : rect_{x, y, size, size}
{
}

void Drawing::Square::move(int x, int y)
{
    rect_.move(x, y);
}

Drawing::Point Drawing::Square::coord() const
{
    return rect_.coord();
}

void Drawing::Square::set_coord(const Drawing::Point& pt)
{
    rect_.set_coord(pt);
}

int Drawing::Square::size() const
{
    return rect_.height();
}

void Drawing::Square::set_size(int size)
{
    rect_.set_width(size);
    rect_.set_height(size);

    assert(rect_.width() == rect_.height());
}

void Drawing::Square::draw() const
{
    rect_.draw();
}
