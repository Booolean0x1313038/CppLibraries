#ifndef __MATH_HPP__
#define __MATH_HPP__

namespace _Boolean
{
    class Math
    {
    public:
        template <typename T>
        inline static T Max(T v0, T v1) { return v0 > v1 ? v0 : v1; }

        template <typename T>
        inline static T Min(T v0, T v1) { return v0 < v1 ? v0 : v1; }

        template <typename T>
        inline static T Min3(T v0, T v1, T v2) { return Min(Min(v0, v1), v2); }

        template <typename T>
        inline static T Floor(T v) { return (int)v - (v < 0 ? 1 : 0); }

        template <typename T>
        inline static T Ceiling(T v) { return Floor(v + 1); }

        template <typename T>
        inline static T Abs(T v) { return v > 0 ? v : -v; }

        inline static double Sqrt(double value, double e = 0.000000001)
        {
            double t = 0;
            while (Abs(value - t) > e)
            {
                t = value;
                value = 0.5 * (t + value / t);
            }
            return value;
        }
    };
}

#endif
