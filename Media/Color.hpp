#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "../Math.hpp"

namespace _Boolean::Media
{
    class Color
    {
    public:
        struct RGBW
        {
        public:
            unsigned char R = 0;
            unsigned char G = 0;
            unsigned char B = 0;
            unsigned char W = 0;
            static RGBW FromColor(const _Boolean::Media::Color &color)
            {
                _Boolean::Media::Color c = _Boolean::Media::Color::FromRGB(color.R / 255.0f * color.A, color.G / 255.0f * color.A, color.B / 255.0f * color.A) ;
                unsigned char w = _Boolean::Math::Min3(c.R, c.G, c.B);
                return RGBW(c.R - w, c.G - w, c.B - w, w);
            }
            RGBW() {}
            RGBW(unsigned char r, unsigned char g, unsigned char b, unsigned char w)
            {
                R = r;
                G = g;
                B = b;
                W = w;
            }
        };
        static Color FromRGB(const unsigned char r, const unsigned char g, const unsigned char b)
        {
            Color color;
            color.R = r;
            color.G = g;
            color.B = b;
            return color;
        }
        static Color FromARGB(const unsigned char a, const unsigned char r, const unsigned char g, const unsigned char b)
        {
            Color color;
            color.A = a;
            color.R = r;
            color.G = g;
            color.B = b;
            return color;
        }
        static Color FromHSV(unsigned char h, unsigned char s, unsigned char v)
        {
            int i;
            float f, a, b, c;

            unsigned char red, green, blue;

            if (h >= 360)
            {
                h = 0;
            }

            if (s == 0)
            {
                red = ((int)(v * 255));
                green = ((int)(v * 255));
                blue = ((int)(v * 255));
            }
            else
            {
                h /= 60.0;                    // sector 0 to 5, h_max=360 360/60=6[0,1,2,3,4,5]
                i = _Boolean::Math::Floor(h); // floor(h)
                f = h - i;                    // factorial path of h
                a = v * (1 - s);
                b = v * (1 - s * f);
                c = v * (1 - s * (1 - f));
                switch (i)
                {
                case 0:
                    red = (unsigned char)((int)(v * 255));   // v*255
                    green = (unsigned char)((int)(c * 255)); // c*255;
                    blue = (unsigned char)((int)(a * 255));  // a*255;
                    break;
                case 1:
                    red = (unsigned char)((int)(b * 255));   // b*255;
                    green = (unsigned char)((int)(v * 255)); // v*255;
                    blue = (unsigned char)((int)(a * 255));  // a*255;
                    break;
                case 2:
                    red = (unsigned char)((int)(a * 255));   // a*255;
                    green = (unsigned char)((int)(v * 255)); // v*255;
                    blue = (unsigned char)((int)(c * 255));  // c*255;
                    break;
                case 3:
                    red = (unsigned char)((int)(a * 255));   // a*255;
                    green = (unsigned char)((int)(b * 255)); // b*255;
                    blue = (unsigned char)((int)(v * 255));  // v*255;
                    break;
                case 4:
                    red = (unsigned char)((int)(c * 255));   // c*255;
                    green = (unsigned char)((int)(a * 255)); // a*255;
                    blue = (unsigned char)((int)(v * 255));  // v*255;
                    break;
                default:
                    red = (unsigned char)((int)(v * 255));   // v*255;
                    green = (unsigned char)((int)(a * 255)); // a*255;
                    blue = (unsigned char)((int)(b * 255));  // b*255;
                    break;
                }
            }

            return FromRGB(red, green, blue);
        }
        static Color FromRGBW(RGBW &rgbw) { return Color::FromRGB(rgbw.W + rgbw.R, rgbw.W + rgbw.G, rgbw.W + rgbw.B); }

        RGBW toRGBW()
        {
            return RGBW::FromColor(*this);
        }

        unsigned char R = 0;
        unsigned char G = 0;
        unsigned char B = 0;
        unsigned char A = 0xFF;

    private:
        template <typename T>
        inline T Limit(T value, T left, T right)
        {
            return _Boolean::Math::Max<T>(_Boolean::Math::Min<T>(value, right), left);
        }
        inline Color FromDoubleARGB(int a, double r, int g, int b)
        {
            return FromARGB(Limit<int>(a, 0, 255), Limit<int>(r, 0, 255), Limit<int>(g, 0, 255), Limit<int>(b, 0, 255));
        }

    public:
        Color operator*(const double &value)
        {
            return FromDoubleARGB(A * value, R * value, G * value, B * value);
        }
        Color operator+(const Color &value)
        {
            return FromDoubleARGB(A + value.A, R + value.R, G + value.G, B + value.B);
        }
    };
}

#endif
