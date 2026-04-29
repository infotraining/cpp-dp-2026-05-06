#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace Drawing
{
    struct Point
    {
        int x = 0;
        int y = 0;

        Point(int x = 0, int y = 0) : x{x}, y{y}
        {
        }

        void translate(int dx, int dy)
        {
            x += dx;
            y += dy;
        }
    };
}

std::ostream& operator<<(std::ostream& out, const Drawing::Point& pt);

std::istream& operator>>(std::istream& in, Drawing::Point& pt);

#endif // POINT_HPP
