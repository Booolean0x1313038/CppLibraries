#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

namespace _Boolean::Geometry
{
    template <typename T>
    struct Point
    {
    public:
        T X = 0;
        T Y = 0;

        Point() {}
        Point(T x, T y)
        {
            X = x;
            Y = y;
        }

        bool operator==(const Point &p) { return p.X == X && p.Y == Y; }
    };
    template <typename T>
    struct Size
    {
    public:
        T Width = 0;
        T Height = 0;
        Size() {}
        Size(T width, T height)
        {
            Width = width;
            Height = height;
        }

        bool operator==(const Size &p) { return p.Width == Width && p.Height == Height; }
    };
    template <typename T>
    struct Rectangle
    {
    public:
        T X = 0;
        T Y = 0;
        T Width = 0;
        T Height = 0;

        Rectangle() {}
        Rectangle(T x, T y, T width, T height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
        Rectangle(Point<T> point, Size<T> size)
        {
            X = point.X;
            Y = point.Y;
            Width = size.Width;
            Height = size.Height;
        }

        _Boolean::Geometry::Point<T> Location() { return _Boolean::Geometry::Point<T>(X, Y); }
        _Boolean::Geometry::Size<T> Size() { return _Boolean::Geometry::Size<T>(Width, Height); }

        T Left() { return X; }
        T Top() { return Y; }
        T Right() { return X + Width - 1; }
        T Bottom() { return Y + Height - 1; }

        bool operator==(const Rectangle &r) { return r.X == X && r.Y == Y && r.Width == Width && r.Height == Height; }
    };
}

#endif
