#ifndef __GRADIENTBRUSH_HPP__
#define __GRADIENTBRUSH_HPP__

#include "../Color.hpp"
#include "../../Geometry.hpp"
#include "../../Collections/Linked.hpp"
#include "../Bitmap.hpp"
#include "../../Math.hpp"
#include "initializer_list"

namespace _Boolean::Media::Brush::GradientBrush
{
    /// @brief 渐变的关键点
    /// @tparam T
    template <typename T>
    struct GradientStop
    {
        double Offset = 0;
        T Value;
        GradientStop() {}
        GradientStop(T value, double offset)
        {
            Offset = offset;
            Value = value;
        }
    };

    /// @brief 渐变的基础实现, 除了实现渐变画刷, 也可以用于处理运算折线上任意点的值等. 使用方法参考 WPF
    /// @tparam T 必须支持 operator + 和 operator *
    template <typename T>
    class Base
    {
    private:
        double _Offset = 0;

    public:
        /// @brief 偏移值, 采样时向正方向偏移的百分比, [0, 1]
        /// @return 偏移
        double Offset()
        {
            return _Offset;
        }

        /// @brief 设置偏移值, [0, 1]
        /// @param offset 新偏移值, 可为任意实数, 会自动舍去整数
        void SetOffset(double offset)
        {
            _Offset = offset - _Boolean::Math::Floor(offset);
        }

        /// @brief 起始点 [0, 1]
        _Boolean::Geometry::Point<double> StartPoint = _Boolean::Geometry::Point<double>(0, 0);
        /// @brief 终止点 [0, 1]
        _Boolean::Geometry::Point<double> EndPoint = _Boolean::Geometry::Point<double>(1, 0);
        /// @brief 默认值, 若关键点列表为空时返回的值
        T DefaultValue;

        /// @brief 设置关键点
        /// @param value 关键点的值
        /// @param stop 关键点的位置, [0, 1], 如果存在相同的点则会覆盖原来的点
        void SetGradientStop(T value, double stop)
        {
            SetGradientStop(GradientStop<T>(value, stop));
        }

        /// @brief 设置关键点
        /// @param grandient 关键点, 如果存在 Stop 相同的点则会覆盖原来的点
        void SetGradientStop(GradientStop<T> grandient)
        {
            for (int i = 1; i < _Stops.Length(); i++)
            {
                GradientStop<T> &gradientStop = _Stops[i];
                if (gradientStop.Offset == grandient.Offset)
                {
                    gradientStop.Value = grandient.Value;
                    return;
                }
                if (gradientStop.Offset > grandient.Offset)
                {
                    _Stops.Insert(i, grandient);
                    return;
                }
            }
            _Stops.Append(grandient);
        }

        /// @brief 移除任意位置的关键点
        /// @param stop 关键点的位置
        /// @return 是否成功, 没找到则为不成功, 返回 False
        bool RemoveGradientStop(double stop)
        {
            for (int i = 1; i < _Stops.Length(); i++)
            {
                const _Boolean::Collections::Linked::Node<GradientStop<T>> *node = _Stops.Node(i);
                if (node->Value.Offset == stop)
                {
                    _Stops.RemoveNode(node);
                    return true;
                }
            }
            return false;
        }

        /// @brief 根据位置计算值
        /// @param pct 位置
        /// @return 值
        T GetValue(double pct)
        {
            pct = pct + 1 - _Offset;
            pct -= (double)((int)pct);
            if (_Stops.Length() == 0)
            {
                return DefaultValue;
            }
            GradientStop<T> start = _Stops[0];
            if (pct <= start.Offset)
            {
                return start.Value;
            }
            GradientStop<T> end = _Stops[-1];
            if (pct >= end.Offset)
            {
                return end.Value;
            }

            GradientStop<T> right = _Stops[-1];
            GradientStop<T> last = _Stops[0];
            for (int i = 1; i < _Stops.Length(); i++)
            {
                GradientStop<T> stop = _Stops[i];
                if (stop.Offset > pct)
                {
                    right = stop;
                    break;
                }
                last = stop;
            }
            double pct1 = (pct - last.Offset) / (right.Offset - last.Offset);
            return last.Value * (1 - pct1) + right.Value * pct1;
        }

    protected:
        _Boolean::Collections::Linked::List<GradientStop<T>> _Stops;
    };

    template <typename T>
    class LinearBase : public Base<T>
    {
    public:
        LinearBase() {}
        /// @brief 初始化并使用花括号添加多个变量
        /// @param values 若干初始值
        LinearBase(std::initializer_list<GradientStop<T>> values)
        {
            for (const GradientStop<_Boolean::Media::Color> *beg = values.begin(); beg != values.end(); ++beg)
            {
                Base<T>::SetGradientStop(*beg);
            }
        };

    protected:
        /// @brief 渐变方向和垂线斜率等信息
        struct DirectionLine
        {
            double DirectionK = 1;
            double DirectionB = 0;
            double PerpendicularK = 1;
            double Length = 1;
            double StartX = 0;
            bool IsHorizontal = false;
            bool IsVertical = false;
            DirectionLine(int width, int height, _Boolean::Geometry::Point<double> startP, _Boolean::Geometry::Point<double> endP)
            {
                StartX = (double)(width - 1) * (startP.X);
                double p1X = (double)(width - 1) * (endP.X);
                double p0Y = (double)(height - 1) * (startP.Y);
                double p1Y = (double)(height - 1) * (endP.Y);
                IsHorizontal = (p0Y == p1Y);
                IsVertical = (StartX == p1X);
                Length = p1X - StartX; // 渐变范围在 x 轴上的投影 L 的长度
                // 假设我们要在 y0 = k0 * x + b0 方向上绘制渐变, 根据直线方程, 该直线的垂线, 即 y1 = -1 / k0 * x + b1 上的像素的颜色是一样的
                // 据此, 在绘制任意像素时, 首先计算直线 y0 过该像素的垂线与直线 y0 的交点的横坐标 x1, 再计算 x1 在 L 上的位置, 最后计算像素的颜色
                DirectionK = (p1Y - p0Y) / (p1X - StartX); // 直线 y0 表达式中的 k0
                DirectionB = p0Y - StartX * DirectionK;    // 直线 y0 表达式中的 b0
                PerpendicularK = -1 / DirectionK;          // 直线 y0 的垂线 y1 的表达式中的 k1
            }
        };

        /// @brief 计算百分比
        /// @param line 渐变方向
        /// @param x 在 Bitmap 中的位置
        /// @param y 在 Bitmap 中的位置
        /// @return 百分比
        double Percent(const DirectionLine &line, int x, int y)
        {
            double bTarget = (double)y - line.PerpendicularK * (double)x;                     // 直线 y0 过点 (col, row) 的垂线 y1 的表达式中的 b1
            double X = (line.DirectionB - bTarget) / (line.PerpendicularK - line.DirectionK); // 求两直线的交点的横坐标 x1
            double pct = (X - line.StartX) / line.Length;                                     // 求 x1 在 L 中的位置
            pct = _Boolean::Math::Max<double>(pct, 0);
            pct = _Boolean::Math::Min<double>(pct, 1);
            return pct;
        }
    };
    class Linear : public LinearBase<_Boolean::Media::Color>
    {
    public:
        Linear() : LinearBase<_Boolean::Media::Color>() { LinearBase<_Boolean::Media::Color>::DefaultValue = _Boolean::Media::Color::FromARGB(0, 0, 0, 0); }
        Linear(std::initializer_list<GradientStop<_Boolean::Media::Color>> values) : LinearBase<_Boolean::Media::Color>(values) { LinearBase<_Boolean::Media::Color>::DefaultValue = _Boolean::Media::Color::FromARGB(0, 0, 0, 0); }
        /// @brief 在 Bitmap 的第一行绘制渐变
        /// @param bitmap 目标Bitmap
        void DrawH(_Boolean::Media::Bitmap &bitmap)
        {
            double left = (double)(bitmap.Width() - 1) * (Base<_Boolean::Media::Color>::StartPoint.X);
            double right = (double)(bitmap.Width() - 1) * (Base<_Boolean::Media::Color>::EndPoint.X);
            double w = right - left;
            for (int index = 0; index < bitmap.Width(); index++)
            {
                double pct = (index - left) / w;
                if (pct < 0)
                    pct = 0;
                else if (pct > 1)
                    pct = 1;
                bitmap.SetPixel(index, 0, Base<_Boolean::Media::Color>::GetValue(pct));
            }
        }

        /// @brief 在 Bitmap 的第一列绘制渐变
        /// @param bitmap 目标Bitmap
        void DrawV(_Boolean::Media::Bitmap &bitmap)
        {
            double left = (double)(bitmap.Height() - 1) * (Base<_Boolean::Media::Color>::StartPoint.Y);
            double right = (double)(bitmap.Height() - 1) * (Base<_Boolean::Media::Color>::EndPoint.Y);
            double w = right - left;
            for (int index = 0; index < bitmap.Height(); index++)
            {
                double pct = (index - left) / w;
                if (pct < 0)
                    pct = 0;
                else if (pct > 1)
                    pct = 1;
                bitmap.SetPixel(0, index, Base<_Boolean::Media::Color>::GetValue(pct));
            }
        }

        /// @brief 在 Bitmap 上绘制渐变
        /// @param bitmap 目标 Bitmap
        void Draw(_Boolean::Media::Bitmap &bitmap)
        {
            LinearBase<_Boolean::Media::Color>::DirectionLine directionLine(bitmap.Width(), bitmap.Height(), Base<_Boolean::Media::Color>::StartPoint, Base<_Boolean::Media::Color>::EndPoint);
            if (directionLine.IsHorizontal)
            {
                DrawH(bitmap);
                for (int col = 0; col < bitmap.Width(); col++)
                {
                    for (int row = 0; row < bitmap.Height(); row++)
                    {
                        bitmap.SetPixel(col, row, bitmap.Pixel(col, 0));
                    }
                }
            }
            else if (directionLine.IsVertical)
            {
                DrawV(bitmap);
                for (int col = 0; col < bitmap.Width(); col++)
                {
                    for (int row = 0; row < bitmap.Height(); row++)
                    {
                        bitmap.SetPixel(col, row, bitmap.Pixel(0, row));
                    }
                }
            }
            else
            {
                for (int row = 0; row < bitmap.Height(); row++)
                {
                    for (int col = 0; col < bitmap.Width(); col++)
                    {
                        bitmap.SetPixel(col, row, Base<_Boolean::Media::Color>::GetValue(Percent(directionLine, col, row))); // 根据位置获取颜色, 并绘制像素
                    }
                }
            }
        }
    };
}

#endif
