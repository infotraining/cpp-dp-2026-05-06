#include "bitmap.hpp"
#include <algorithm>
#include <array>

using namespace std;

Bitmap::Bitmap(size_t size, char fill_char) : image_{new char[size]}, size_{size}
{
    fill_n(image_, size, fill_char);
}

Bitmap::~Bitmap()
{
    delete[] image_;
}

void Bitmap::draw()
{
    cout << "Image: ";
    for (size_t i = 0; i < size_; ++i)
        cout << image_[i];
    cout << endl;
}
