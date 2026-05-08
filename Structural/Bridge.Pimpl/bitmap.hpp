#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Bitmap
{
    struct BitmapImpl;
    std::indirect<BitmapImpl> pimpl_;

public:
    Bitmap(size_t size, char fill_char = '*');
    ~Bitmap();

    Bitmap(const Bitmap&) = default;
    Bitmap& operator=(const Bitmap&) = default;

    Bitmap(Bitmap&&) = default;
    Bitmap& operator=(Bitmap&&) = default;

    void draw();
};

#endif // BITMAP_HPP
