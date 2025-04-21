#ifndef __LP5036_HPP__
#define __LP5036_HPP__

#include "../Media/Color.hpp"

namespace _Boolean::Devices
{
    class LP5036
    {
    private:
        static const unsigned char RegistersOffset = 4;

    public:
        LP5036(unsigned char addr, bool (*_ReadRs)(unsigned char deviceAddr, const unsigned char reg, unsigned char *dataPtr, unsigned char count), bool (*_WriteRs)(const unsigned char deviceAddr, const unsigned char reg, const unsigned char *dataPtr, unsigned char count))
        {
            DeviceAddress = addr;
            _ReadRegisters = _ReadRs;
            _WriteRegisters = _WriteRs;
        }
        enum class Registers : unsigned char
        {
            BANK_BRIGHTNESS = 0,
            BANK_A_COLOR,
            BANK_B_COLOR,
            BANK_C_COLOR,
            LED00_BRIGHTNESS,
            LED01_BRIGHTNESS,
            LED02_BRIGHTNESS,
            LED03_BRIGHTNESS,
            LED04_BRIGHTNESS,
            LED05_BRIGHTNESS,
            LED06_BRIGHTNESS,
            LED07_BRIGHTNESS,
            LED08_BRIGHTNESS,
            LED09_BRIGHTNESS,
            LED10_BRIGHTNESS,
            LED11_BRIGHTNESS,
            OUT0_COLOR,
            OUT1_COLOR,
            OUT2_COLOR,
            OUT3_COLOR,
            OUT4_COLOR,
            OUT5_COLOR,
            OUT6_COLOR,
            OUT7_COLOR,
            OUT8_COLOR,
            OUT9_COLOR,
            OUT10_COLOR,
            OUT11_COLOR,
            OUT12_COLOR,
            OUT13_COLOR,
            OUT14_COLOR,
            OUT15_COLOR,
            OUT16_COLOR,
            OUT17_COLOR,
            OUT18_COLOR,
            OUT19_COLOR,
            OUT20_COLOR,
            OUT21_COLOR,
            OUT22_COLOR,
            OUT23_COLOR,
            OUT24_COLOR,
            OUT25_COLOR,
            OUT26_COLOR,
            OUT27_COLOR,
            OUT28_COLOR,
            OUT29_COLOR,
            OUT30_COLOR,
            OUT31_COLOR,
            OUT32_COLOR,
            OUT33_COLOR,
            OUT34_COLOR,
            OUT35_COLOR,
        };

        static const int RegistersCount = (int)Registers::OUT35_COLOR - (int)Registers::BANK_BRIGHTNESS + 1;

        inline bool GetChipEN(bool *successed = nullptr) { return GetChipEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG0, successed)); }
        inline bool GetLogScale(bool *successed = nullptr) { return GetLogScale(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }
        inline bool GetPowerSave(bool *successed = nullptr) { return GetPowerSave(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }
        inline bool GetAutoIncr(bool *successed = nullptr) { return GetAutoIncr(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }
        inline bool GetPWMDithering(bool *successed = nullptr) { return GetPWMDithering(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }
        inline bool GetMaxCurrentOption(bool *successed = nullptr) { return GetMaxCurrentOption(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }
        inline bool GetLEDGlobalOff(bool *successed = nullptr) { return GetLEDGlobalOff(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, successed)); }

        inline bool GetLED0BankEN(bool *successed = nullptr) { return GetLED0BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED1BankEN(bool *successed = nullptr) { return GetLED1BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED2BankEN(bool *successed = nullptr) { return GetLED2BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED3BankEN(bool *successed = nullptr) { return GetLED3BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED4BankEN(bool *successed = nullptr) { return GetLED4BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED5BankEN(bool *successed = nullptr) { return GetLED5BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED6BankEN(bool *successed = nullptr) { return GetLED6BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED7BankEN(bool *successed = nullptr) { return GetLED7BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, successed)); }
        inline bool GetLED8BankEN(bool *successed = nullptr) { return GetLED8BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, successed)); }
        inline bool GetLED9BankEN(bool *successed = nullptr) { return GetLED9BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, successed)); }
        inline bool GetLED10BankEN(bool *successed = nullptr) { return GetLED10BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, successed)); }
        inline bool GetLED11BankEN(bool *successed = nullptr) { return GetLED11BankEN(ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, successed)); }

        inline bool GetValues(unsigned char *data, unsigned char &count, Registers reg) { return ReadRegisters(DeviceAddress, RegisterToChipRegister(reg), data, count); }
        inline unsigned char GetValue(Registers reg, bool *successed = nullptr)
        {
            return ReadRegister(DeviceAddress, RegisterToChipRegister(reg), successed);
        }

        inline bool SetEn(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG0, &succ);
            if (GetChipEN(data) != on && succ)
            {
                SetEn(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLogScale(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetLogScale(data) != on && succ)
            {
                SetLogScale(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetPowerSave(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetPowerSave(data) != on && succ)
            {
                SetPowerSave(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetAutoIncr(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetAutoIncr(data) != on && succ)
            {
                SetAutoIncr(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetPWMDithering(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetPWMDithering(data) != on && succ)
            {
                SetPWMDithering(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetMaxCurrentOption(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetMaxCurrentOption(data) != on && succ)
            {
                SetMaxCurrentOption(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetLEDGlobalOff(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, &succ);
            if (GetLEDGlobalOff(data) != on && succ)
            {
                SetLEDGlobalOff(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::DEVICE_CONFIG1, data);
            }
            return succ;
        }

        inline bool SetLED0BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED0BankEN(data) != on && succ)
            {
                SetLED0BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED1BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED1BankEN(data) != on && succ)
            {
                SetLED1BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED2BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED2BankEN(data) != on && succ)
            {
                SetLED2BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED3BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED3BankEN(data) != on && succ)
            {
                SetLED3BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED4BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED4BankEN(data) != on && succ)
            {
                SetLED4BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED5BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED5BankEN(data) != on && succ)
            {
                SetLED5BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED6BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED6BankEN(data) != on && succ)
            {
                SetLED6BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED7BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, &succ);
            if (GetLED7BankEN(data) != on && succ)
            {
                SetLED7BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG0, data);
            }
            return succ;
        }
        inline bool SetLED8BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, &succ);
            if (GetLED8BankEN(data) != on && succ)
            {
                SetLED8BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetLED9BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, &succ);
            if (GetLED9BankEN(data) != on && succ)
            {
                SetLED9BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetLED10BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, &succ);
            if (GetLED10BankEN(data) != on && succ)
            {
                SetLED10BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, data);
            }
            return succ;
        }
        inline bool SetLED11BankEN(const bool on)
        {
            bool succ;
            unsigned char data = ReadRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, &succ);
            if (GetLED11BankEN(data) != on && succ)
            {
                SetLED11BankEN(data, on);
                return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::LED_CONFIG1, data);
            }
            return succ;
        }

        inline bool RESET() { return WriteRegister(DeviceAddress, (unsigned char)PrivateRegisters::RESET, RESET_VALUE); }

        inline bool SetValues(unsigned char *data, unsigned char &count, Registers reg) { return WriteRegisters(DeviceAddress, RegisterToChipRegister(reg), data, count); }
        inline bool SetValue(Registers reg, unsigned char value) { return WriteRegister(DeviceAddress, (unsigned char)reg + RegistersOffset, value); }

    private:
        unsigned char DeviceAddress = 0x30;
        static const unsigned char RESET_VALUE = 0xFF;

        bool (*_ReadRegisters)(const unsigned char deviceAddr, const unsigned char reg, unsigned char *dataPtr, unsigned char count);
        bool (*_WriteRegisters)(const unsigned char deviceAddr, const unsigned char reg, const unsigned char *dataPtr, unsigned char count);

        enum BIT_DEV_CONFIG0
        {
            Chip_EN = 0b01000000,
        };
        enum BIT_DEV_CONFIG1
        {
            Log_Scale_EN = 0b00100000,
            Power_Save_EN = 0b00010000,
            Auto_Incr_EN = 0b00001000,
            PWM_Dithering_EN = 0b00000100,
            Max_Current_Option = 0b00000010,
            LED_Global_Off = 0b00000001,
        };
        enum BIT_LED_CONFIG0
        {
            LED7_Bank_EN = 0b10000000,
            LED6_Bank_EN = 0b01000000,
            LED5_Bank_EN = 0b00100000,
            LED4_Bank_EN = 0b00010000,
            LED3_Bank_EN = 0b00001000,
            LED2_Bank_EN = 0b00000100,
            LED1_Bank_EN = 0b00000010,
            LED0_Bank_EN = 0b00000001,
        };
        enum BIT_LED_CONFIG1
        {
            LED11_Bank_EN = 0b00001000,
            LED10_Bank_EN = 0b00000100,
            LED9_Bank_EN = 0b00000010,
            LED8_Bank_EN = 0b00000001,
        };
        enum class PrivateRegisters : unsigned char
        {
            DEVICE_CONFIG0 = 0,
            DEVICE_CONFIG1,
            LED_CONFIG0,
            LED_CONFIG1,
            RESET = 0x38,
        };

        inline static bool LimitCount(unsigned char reg, unsigned char &count)
        {
            if (reg + count - 1 > (unsigned char)PrivateRegisters::RESET)
            {
                count = (unsigned char)PrivateRegisters::RESET - reg + 1;
            }
            return count > 0;
        }

        inline bool ReadRegisters(const unsigned char deviceAddr, const unsigned char reg, unsigned char *dataPtr, unsigned char &count)
        {
            if (LimitCount(reg, count) == false)
            {
                return false;
            }
            return _ReadRegisters(deviceAddr, reg, dataPtr, count);
        }
        inline unsigned char ReadRegister(const unsigned char deviceAddr, const unsigned char reg, bool *successed = nullptr)
        {
            unsigned char data;
            unsigned char count = 1;
            bool succ = ReadRegisters(deviceAddr, reg, &data, count);
            if (successed != nullptr)
            {
                *successed = succ;
            }
            return data;
        }
        inline bool WriteRegisters( const unsigned char deviceAddr, const unsigned char reg, const unsigned char *dataPtr, unsigned char &count)
        {
            if (LimitCount(reg, count) == false)
            {
                return false;
            }
            return _WriteRegisters(deviceAddr, reg, dataPtr, count);
        }
        inline bool WriteRegister(const unsigned char deviceAddr, const unsigned char reg, unsigned char data)
        {
            unsigned char count = 1;
            return WriteRegisters(deviceAddr, reg, &data, count);
        }

        inline static bool GetChipEN(unsigned char value) { return value & Chip_EN; }
        inline static bool GetLogScale(unsigned char value) { return value & Log_Scale_EN; }
        inline static bool GetPowerSave(unsigned char value) { return value & Power_Save_EN; }
        inline static bool GetAutoIncr(unsigned char value) { return value & Auto_Incr_EN; }
        inline static bool GetPWMDithering(unsigned char value) { return value & PWM_Dithering_EN; }
        inline static bool GetMaxCurrentOption(unsigned char value) { return value & Max_Current_Option; }
        inline static bool GetLEDGlobalOff(unsigned char value) { return value & LED_Global_Off; }

        inline static bool GetLED0BankEN(unsigned char value) { return value & LED0_Bank_EN; }
        inline static bool GetLED1BankEN(unsigned char value) { return value & LED1_Bank_EN; }
        inline static bool GetLED2BankEN(unsigned char value) { return value & LED2_Bank_EN; }
        inline static bool GetLED3BankEN(unsigned char value) { return value & LED3_Bank_EN; }
        inline static bool GetLED4BankEN(unsigned char value) { return value & LED4_Bank_EN; }
        inline static bool GetLED5BankEN(unsigned char value) { return value & LED5_Bank_EN; }
        inline static bool GetLED6BankEN(unsigned char value) { return value & LED6_Bank_EN; }
        inline static bool GetLED7BankEN(unsigned char value) { return value & LED7_Bank_EN; }
        inline static bool GetLED8BankEN(unsigned char value) { return value & LED8_Bank_EN; }
        inline static bool GetLED9BankEN(unsigned char value) { return value & LED9_Bank_EN; }
        inline static bool GetLED10BankEN(unsigned char value) { return value & LED10_Bank_EN; }
        inline static bool GetLED11BankEN(unsigned char value) { return value & LED11_Bank_EN; }

        inline static void SetRegisterBit(unsigned char &value0, const bool on, const unsigned char value1)
        {
            if (on)
            {
                value0 |= value1;
            }
            else
            {
                value0 &= ~value1;
            }
        }

        inline static void SetEn(unsigned char &value, bool on) { SetRegisterBit(value, on, Chip_EN); }

        inline static void SetLogScale(unsigned char &value, bool on) { SetRegisterBit(value, on, Log_Scale_EN); }
        inline static void SetPowerSave(unsigned char &value, bool on) { SetRegisterBit(value, on, Power_Save_EN); }
        inline static void SetAutoIncr(unsigned char &value, bool on) { SetRegisterBit(value, on, Auto_Incr_EN); }
        inline static void SetPWMDithering(unsigned char &value, bool on) { SetRegisterBit(value, on, PWM_Dithering_EN); }
        inline static void SetMaxCurrentOption(unsigned char &value, bool on) { SetRegisterBit(value, on, Max_Current_Option); }
        inline static void SetLEDGlobalOff(unsigned char &value, bool on) { SetRegisterBit(value, on, LED_Global_Off); }

        inline static void SetLED0BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED0_Bank_EN); }
        inline static void SetLED1BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED1_Bank_EN); }
        inline static void SetLED2BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED2_Bank_EN); }
        inline static void SetLED3BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED3_Bank_EN); }
        inline static void SetLED4BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED4_Bank_EN); }
        inline static void SetLED5BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED5_Bank_EN); }
        inline static void SetLED6BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED6_Bank_EN); }
        inline static void SetLED7BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED7_Bank_EN); }
        inline static void SetLED8BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED8_Bank_EN); }
        inline static void SetLED9BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED9_Bank_EN); }
        inline static void SetLED10BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED10_Bank_EN); }
        inline static void SetLED11BankEN(unsigned char &value, bool on) { SetRegisterBit(value, on, LED11_Bank_EN); }

        inline static unsigned char RegisterToChipRegister(Registers reg) { return (unsigned char)reg + RegistersOffset; }
    };
}

#endif