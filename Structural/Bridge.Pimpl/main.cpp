#include "bitmap.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Bitmap bmp1(20);
    bmp1.draw();

    Bitmap bmp2(10, '%');
    bmp2.draw();
}