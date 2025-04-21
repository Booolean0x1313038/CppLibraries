#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include "Color.hpp"

#include <iostream>

namespace _Boolean::Media
{
    class Bitmap
    {
    public:
        Bitmap(int width, int height)
        {
            _Width = width;
            _Height = height;
            pixels = new _Boolean::Media::Color[width * height];
        }
        ~Bitmap()
        {
            delete[] pixels;
        }
        _Boolean::Media::Color &Pixel(int x, int y)
        {
            return pixels[x + y * _Width];
        }
        void SetPixel(int x, int y, _Boolean::Media::Color pixel)
        {
            pixels[x + y * _Width] = pixel;
        }

        int Width() { return _Width; }
        int Height() { return _Height; }

    private:
        int _Width = 0;
        int _Height = 0;

        _Boolean::Media::Color *pixels;
    };
}

#endif
