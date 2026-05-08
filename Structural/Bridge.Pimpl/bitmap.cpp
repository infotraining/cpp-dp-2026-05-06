#include "bitmap.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>

using namespace std;

struct Bitmap::BitmapImpl
{
    std::deque<std::uint8_t> image_;

    BitmapImpl(size_t size, char fill_char)
        : image_(size, fill_char)
    {
    }
};

Bitmap::Bitmap(size_t size, char fill_char) : pimpl_(BitmapImpl{size, fill_char})
{
}

Bitmap::~Bitmap() = default;

void Bitmap::draw()
{
    cout << "Image: ";
    for (size_t i = 0; i < pimpl_->image_.size(); ++i)
        cout << pimpl_->image_[i];
    cout << endl;
}
