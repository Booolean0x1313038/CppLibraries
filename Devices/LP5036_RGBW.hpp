#ifndef __LP5036_RGBW_HPP__
#define __LP5036_RGBW_HPP__

#include "LP5036.hpp"

namespace _Boolean::Devices
{
    class LP5036_RGBW : public LP5036
    {
    public:
        /// @brief 初始化
        /// @param addr 设备 I2C 地址, 手册中地址
        /// @param _ReadRs 执行 I2C 读取数据的函数指针
        /// @param _WriteRs 执行 I2C 写入数据的函数指针
        LP5036_RGBW(unsigned char addr, bool (*_ReadRs)(unsigned char deviceAddr, const unsigned char reg, unsigned char *dataPtr, unsigned char count), bool (*_WriteRs)(const unsigned char deviceAddr, const unsigned char reg, const unsigned char *dataPtr, unsigned char count)) : LP5036(addr, _ReadRs, _WriteRs) {}

        static const int LedCount = 9;

        /// @brief 获取 LED 颜色值, 存为 RGBW 格式
        /// @param rgbws RGBW 数组的地址
        /// @param count RGBW 数组的长度, 也是读取的数量
        /// @param index 读取的起始位置
        /// @return 读取了所有数据
        inline bool GetRGBWs(_Boolean::Media::Color::RGBW *rgbws, int count, int index)
        {
            unsigned char channelCount = count << 2;
            unsigned char data[channelCount];
            bool successed = GetValues(data, channelCount, LedIndexToRegister(index));
            for (int i = 0; i < count; i++)
            {
                int offset = i * 4;
                rgbws[i] = _Boolean::Media::Color::RGBW(data[offset], data[offset + 1], data[offset + 2], data[offset + 3]);
            }
            return successed;
        }

        /// @brief 获取 LED 颜色值, 存为 Color 格式
        /// @param colors Color 数组的地址
        /// @param count Color 数组的长度, 也是读取的数量
        /// @param index 读取的起始位置
        /// @return
        inline bool GetColors(_Boolean::Media::Color *colors, int count, int index)
        {
            _Boolean::Media::Color::RGBW rgbws[count];
            bool successed = GetRGBWs(rgbws, count, index);
            for (int i = 0; i < count; i++)
            {
                colors[i] = _Boolean::Media::Color::FromRGBW(rgbws[i]);
            }
            return successed;
        }

        /// @brief 获取一个 LED 的颜色值, 存储为 RGBW 格式
        /// @param index 位置
        /// @param successed 是否成功
        /// @return 值
        inline _Boolean::Media::Color::RGBW GetRGBW(int index, bool *successed = nullptr)
        {
            _Boolean::Media::Color::RGBW rgbw;
            *successed = GetRGBWs(&rgbw, 1, index);
            return rgbw;
        }

        /// @brief 获取一个 LED 的颜色值, 存储为 Color 格式
        /// @param index 位置
        /// @param successed 是否成功
        /// @return 值
        inline _Boolean::Media::Color GetColor(int index, bool *successed = nullptr)
        {
            _Boolean::Media::Color color;
            *successed = GetColors(&color, 1, index);
            return color;
        }

        /// @brief 以 RGBW 格式数据为源设置多个 LED 颜色
        /// @param rgbws RGBW 数组的指针
        /// @param count RGBW 数组的长度, 也是设置的数量
        /// @param index 起始位置
        /// @return 设置了足够数量的 LED
        inline bool SetRGBWs(const _Boolean::Media::Color::RGBW *rgbws, int count, int index)
        {
            LimitLedCount(count, index);
            unsigned char channelCount = count << 2;
            unsigned char data[channelCount];
            for (int i = 0; i < count; i++)
            {
                int offset = i << 2;
                data[offset] = rgbws[i].R;
                data[offset + 1] = rgbws[i].G;
                data[offset + 2] = rgbws[i].B;
                data[offset + 3] = rgbws[i].W;
            }
            return SetValues(data, channelCount, LedIndexToRegister(index));
        }

        /// @brief 以 Color 格式数据为原设置多个 LED 颜色
        /// @param colors Color 数组的指针
        /// @param count Color 数组的长度, 也是设置的数量
        /// @param index 起始位置
        /// @return 设置了足够数量的 LED
        inline bool SetColors(_Boolean::Media::Color *colors, int count, int index)
        {
            _Boolean::Media::Color::RGBW rgbws[count];
            for (int i = 0; i < count; i++)
            {
                rgbws[i] = colors[i].toRGBW();
            }
            bool successed = SetRGBWs(rgbws, count, index);
            return successed;
        }

        /// @brief 以 RGBW 格式数据为原设置一个 LED 颜色
        /// @param index 位置
        /// @param rgbw 颜色
        /// @return 成功
        inline bool SetRGBW(int index, const _Boolean::Media::Color::RGBW &rgbw)
        {
            return SetRGBWs(&rgbw, 1, index);
        }

        /// @brief 以 Color 格式数据为原设置一个 LED 颜色
        /// @param index 位置
        /// @param color 颜色
        /// @return 成功
        inline bool SetColor(int index, _Boolean::Media::Color &color)
        {
            return SetColors(&color, 1, index);
        }

    private:
        /// @brief LED 索引转 Registers 枚举
        /// @param index 索引
        /// @return Registers
        inline static Registers LedIndexToRegister(int index) { return (Registers)((int)Registers::OUT0_COLOR + (index << 2)); }

        /// @brief 限制索引在 LED 数量之内
        /// @param count LED 数
        /// @param index 索引
        inline static void LimitLedCount(int &count, int index)
        {
            if (count + index > LedCount)
            {
                count = LedCount - index;
            }
        }
    };
}

#endif