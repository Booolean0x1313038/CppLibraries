#ifndef __MODBUS_RTU_SLAVE_H__
#define __MODBUS_RTU_SLAVE_H__

/////////////////////////////////////////////////////////////////////////////////
// 需要使用 写入多次生效 Feature
#define USE_WRITE_SEVEIAL_TIMES

// 启用 Feature: 1Bit 寄存器
#define USE_COIL

// 选择计算 CRC 的方法
//      1 = 查短表法, 均衡速度与空间占用
//      2 = 查长表法, 速度最快, 占用空间最多
//      其他或不定义 = 直接计算法, 占用空间最小, 速度最慢
#define MODBUS_CRC_METHOD 1

// 使用 Feature: C++ Class
// #define USE_CPLUSPLUS_CLASS
/////////////////////////////////////////////////////////////////////////////////

typedef unsigned short MODBUS_RTU_Register_UINT16;
#ifdef USE_COIL
typedef unsigned char MODBUS_RTU_Register_BIT;
#endif
// #define nullptr 0
// #define MODBUS_RTU_NO_TO_BIG_ENDIAN
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
/// @brief 功能码
typedef enum
{
    /// @brief 读取多个线圈 (1 Bit)
    MODBUS_RTU_FUNCTIONCODE_READ_MULTIPLE_COILS = 0x01,
    /// @brief 读取多个离散输入 (1 Bit)
    MODBUS_RTU_FUNCTIONCODE_READ_MULTIPLE_DISCRETE_INPUTS = 0x02,
    /// @brief 读取多个保持寄存器 (16 Bits)
    MODBUS_RTU_FUNCTIONCODE_READ_MULTIPLE_HOLDING_REGISTERS = 0x03,
    /// @brief 读取多个输入寄存器 (16 Bits)
    MODBUS_RTU_FUNCTIONCODE_READ_MULTIPLE_INPUT_REGISTERS = 0x04,
    /// @brief 写入单个线圈 (1 Bit)
    MODBUS_RTU_FUNCTIONCODE_WRITE_SINGLE_COIL = 0x05,
    /// @brief 写入单个保持寄存器 (16 Bit)
    MODBUS_RTU_FUNCTIONCODE_WRITE_SINGLE_HOLDING_REGISTER = 0x06,
    /// @brief 读取异常状态 (仅串行线)
    /// @warning 不受支持
    MODBUS_FunctionCode_SerialLineOnly_ReadExceptionStatus = 0x07,
    /// @brief 通信系统诊断 (仅串行线)
    /// @warning 不受支持
    MODBUS_FunctionCode_SerialLineOnly_Diagnostics = 0x08,
    /// @brief  获取通信事件计数器 (仅串行线)
    /// @warning 不受支持
    MODBUS_FunctionCode_SerialLineOnly_GetCommunicateEventCounter0 = 0x0B,
    /// @brief  获取通信事件日志 (仅串行线)
    /// @warning 不受支持
    MODBUS_FunctionCode_SerialLineOnly_GetCommunicateEventLog = 0x0C,
    /// @brief  写多个线圈 (1 Bit)
    MODBUS_RTU_FUNCTIONCODE_WRITE_MULTIPLE_COILS = 0x0F,
    /// @brief  写多个保持寄存器 (16 Bits)
    MODBUS_RTU_FUNCTIONCODE_WRITE_MULTIPLE_HOLDING_REGISTERS = 0x10,
    /// @brief 报告服务器ID (仅串行线)
    /// @warning 不受支持
    MODBUS_FunctionCode_SerialLineOnly_ReportServerID = 0x11,
    /// @brief 读文件记录
    /// @warning 不受支持
    MODBUS_FunctionCode_ReadFileRecord = 0x14,
    /// @brief 写文件记录
    /// @warning 不受支持
    MODBUS_FunctionCode_WriteFileRecord = 0x15,
    /// @brief 带屏蔽字写入寄存器
    /// @warning 不受支持
    MODBUS_FunctionCode_MaskWriteRegister = 0x16,
    /// @brief 读/写多个寄存器
    /// @warning 不受支持
    MODBUS_FunctionCode_ReadWriteMultipleRegisters = 0x17,
    /// @brief 读取先进先出 (FIFO) 队列
    /// @warning 不受支持
    MODBUS_FunctionCode_ReadFIFOQueue = 0x18,
    /// @brief 封装接口传输
    /// @warning 不受支持
    MODBUS_FunctionCode_EncapsulatedInterfaceTransport = 0x2B,
} MODBUS_RTU_FunctionCodes;

// 功能码的属性
// Reserved | IsSingle (0) or Multiple(1) |  Is 1Bit (0) or 16Bits (1) | Is Read (0) or Writa (1)
typedef enum
{
    MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN = 0,
    MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE = 0b1,
    MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS = 0b10,
    MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE = 0b100,
} MODBUS_RTU_FunctionCodeAttribute;

/// @brief 错误码
typedef enum
{
    /// @brief 功能码不受支持
    MODBUS_RTU_EXCEPTIONCODE_INVALID_FUNCTIONCODE = 1,
    /// @brief 寄存器不存在
    MODBUS_RTU_EXCEPTIONCODE_INVALID_REGISTER_ADDRESS,
    /// @brief 请求帧中值不正确
    MODBUS_RTU_EXCEPTIONCODE_INVALID_REQUEST_VALUE,
    MODBUS_RTU_EXCEPTIONCODE_SERVER_FAILED,
    MODBUS_RTU_EXCEPTIONCODE_PROCESSING,

} MODBUS_RTU_ExceptionCode;

/// @brief 操作结果
typedef enum
{
    /// @brief 无异常
    MODBUS_RTU_RESULT_OK = 0,
    /// @brief 目标设备不是本设备
    MODBUS_RTU_RESULT_NOT_THIS_DEVICE,
    /// @brief CRC 不匹配
    MODBUS_RTU_RESULT_CRC_WRONG,
    /// @brief 功能码不受支持
    MODBUS_RTU_RESULT_FUNCTIONCODE_IS_NOT_SUPPORT,
    /// @brief 数据长度不符合预期
    MODBUS_RTU_RESULT_DATA_LENGTH_IS_INVALID,
    /// @brief 寄存器类型不正确
    MODBUS_RTU_RESULT_REGISTER_TYPE_IS_INCORRECT,
    /// @brief 目标寄存器不存在
    MODBUS_RTU_RESULT_REGISTER_NOT_EXIST,
    /// @brief 目标寄存器超出区域
    MODBUS_RTU_RESULT_REGISTER_OUT_OF_RANGE,
    /// @brief 要读取的寄存器不可读
    MODBUS_RTU_RESULT_REGISTER_NOT_READABLE,
    /// @brief 要写入的急寄存器不可写
    MODBUS_RTU_RESULT_REGISTER_NOT_WRITEABLE,
    /// @brief 广播要读取数据
    MODBUS_RTU_RESULT_BROADCAST_READ,
    /// @brief 写入次数太多或太少
    MODBUS_RTU_RESULT_WRITE_TIME_NOT_MATCH,
    /// @brief 写入单个线圈时传入的值不正确
    MODBUS_RTU_RESULT_WRITE_SINGLE_COIL_DATA_IS_INCORRECT,
    /// @brief 未知
    MODBUS_RTU_RESULT_UNKNOWN,
} MODBUS_RTU_ResultCode;
/// @brief 寄存器属性
typedef enum
{
    /// @brief 可读
    MODBUS_RTU_REGISTER_ATTRIBUTE_READABLE = 0b01,
    /// @brief 可写
    MODBUS_RTU_REGISTER_ATTRIBUTE_WRITABLE = 0b10,
} MODBUS_RTU_Register_Attribute;

/// @brief 寄存器属性
typedef enum
{
    /// @brief 线圈或离散输入
    MODBUS_RTU_REGISTER_TYPE_BIT = 1,
    /// @brief 16 字节寄存器
    MODBUS_RTU_REGISTER_TYPE_UINT16,
} MODBUS_RTU_Register_Type;

/// @brief 地址连续的若干寄存器
typedef struct
{
    /// @brief 寄存器 Array
    void *Registers;
    /// @brief 寄存器属性 Array
    MODBUS_RTU_Register_Attribute *RegistersAttribute;
    /// @brief 寄存器起始的地址
    uint16_t FirstRegisterAddress;
    /// @brief Sizeof (寄存器 Array)
    uint16_t Bytes;
#ifdef USE_COIL
    /// @brief 寄存器类型
    MODBUS_RTU_Register_Type RegisterType;
#endif
#ifdef USE_WRITE_SEVEIAL_TIMES
    /// @brief 需要操作的次数
    uint8_t WriteTimes;
#endif
} MODBUS_RTU_CoiledRegistersArea;

#ifdef USE_CPLUSPLUS_CLASS
namespace _Boolean::Communication
{
class MODBUS_RTU_Slave
{
#endif

#define MODBUS_RTU_MAX_LENGTH 256
#define MODBUS_RTU_DEVICE_ADDRESS_BROADCAST 0
    typedef unsigned short uint16_t;
    typedef unsigned char uint8_t;
#ifdef USE_CPLUSPLUS_CLASS
public:
#endif

#ifndef USE_CPLUSPLUS_CLASS
    typedef struct
    {
#endif
        /// @brief 设备地址
        uint8_t _DeviceAddress;
        /// @brief 连续寄存器区
        MODBUS_RTU_CoiledRegistersArea *_CoiledRegistersAreas;
        /// @brief 连续寄存器区的数量
        size_t _CoiledRegistersAreasAmount;
        /// @brief 返回数据
        uint8_t _ReturnFrame[MODBUS_RTU_MAX_LENGTH];
        /// @brief 返回帧的长度
        size_t _ReturnFrameBytes;
        /// @brief 上次操作的结果
        MODBUS_RTU_ResultCode _LastResult;
#ifdef USE_WRITE_SEVEIAL_TIMES
        /// @brief 上次收到的数据
        uint8_t _Data_LastTime[MODBUS_RTU_MAX_LENGTH - 4]; // 存储的数据不包括 设备地址(00) 操作码(01) CRC(-2 -1)
        /// @brief 上次收到的数据的长度
        size_t _DataLength_LastTime;
        /// @brief 连续收到相同数据的次数, 如果不是写入操作则是 0, 不相同则是 1, 相同则是 2, 3, ...
        uint8_t _Counter_RecvDataIsSame;
#endif
#ifdef USE_CPLUSPLUS_CLASS
    public:
#endif
        /// @brief 解析_设备地址 (FromFrame)
        uint8_t _Prase_RequestFrame_DeviceAddress;
        /// @brief 解析_功能码 (FromFrame)
        MODBUS_RTU_FunctionCodes _Prase_RequestFrame_FunctionCode;
        /// @brief 解析_寄存器地址 (FromFrame)
        uint16_t _Prase_RequestFrame_RegisterAddress;
        /// @brief 解析_请求的寄存器数 (FromFrame)
        uint16_t _Prase_RequestFrame_RequestAmount;
        /// @brief 解析_接收帧的预期长度 (字节数)
        uint16_t _Prase_Calculate_RequestFrameBytes;
        /// @brief 解析_目标寄存器区
        MODBUS_RTU_CoiledRegistersArea *_Prase_Calculate_TargetCoiledRegistersAreaPtr;
        /// @brief 解析_第一个要操作的寄存器的相对于所在区域首个寄存器的偏移地址
        uint16_t _Prase_Calculate_TargetRegistersMemoryAddressOffset;
        /// @brief 解析_要操作的寄存器的字节数
        uint16_t _Prase_Calculate_TargetRegistersBytes;
        /// @brief 解析_操作_写入
        bool _Prase_Calculate_FunctionCodeAttribute_Write;
        /// @brief 解析_操作_多个
        bool _Prase_Calculate_FunctionCodeAttribute_Multiple;
#ifdef USE_COIL
        /// @brief 解析_位偏移
        uint16_t _Prase_Calculate_TargetRegistersBitOffset;
        /// @brief 解析_操作_16位寄存器
        bool _Prase_Calculate_FunctionCodeAttribute_16Bits;
#endif

#ifndef USE_CPLUSPLUS_CLASS
    } MODBUS_RTU_Slave;
#endif

#ifdef USE_CPLUSPLUS_CLASS
public:
#endif

#if (MODBUS_CRC_METHOD == 1) /* 半字节CRC16(Dow_右移逆序) 0xA001 余式表*/
    inline const static uint16_t CRC_16_Tab[] = {
        0x0000, 0xCC01, 0xD801, 0x1400,
        0xF001, 0x3C00, 0x2800, 0xE401,
        0xA001, 0x6C00, 0x7800, 0xB401,
        0x5000, 0x9C01, 0x8801, 0x4400};
    static uint16_t CalculateCRC(const uint8_t *data, const size_t len)
    {
        uint16_t crc = 0xffff;
        uint16_t i;
        uint8_t ch;

        for (i = 0; i < len; i++)
        {
            ch = data[i];
            crc = CRC_16_Tab[(ch ^ crc) & 15] ^ (crc >> 4);
            crc = CRC_16_Tab[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
        }
        return crc;
    }

#elif (MODBUS_CRC_METHOD == 2)
const static uint16_t auchCRC[] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};

static uint16_t CalculateCRC(const uint8_t *data, const size_t length)
{
    uint16_t CRC = 0xffff; // 0xff与数据异或就相当于取反，故只需要一开始把CRC初始值设置为0xffff即可
    uint8_t index;
    for (size_t i = 0; i < length; i++)
    {
        index = (CRC & 0xFF) ^ data[i]; // 取上一字节的CRC低八位，与本字节异或
        CRC >>= 8;						// 取上一字节的高八位
        CRC ^= auchCRC[index];			// 与查表后的结果异或
    }
    return (CRC);
}

#else
static uint16_t CalculateCRC(const uint8_t *data, const size_t length)
{
    uint16_t crc = 0xFFFF;
    uint8_t j;
    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i]; // 将字节与当前 CRC 值异或
        // 对 CRC 值进行 8 次位移和异或操作
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001; // 多项式 0x8005 反向是 0xA001
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc; // 返回计算出的 CRC 值
}
#endif
    static const char *
#ifdef USE_CPLUSPLUS_CLASS
    GetLastResultString
#else
MODBUS_RTU_Slave_GetLastResultString
#endif
        (const MODBUS_RTU_Slave *thisPtr)
    {
        static const char *resultCodeStrings[MODBUS_RTU_RESULT_UNKNOWN + 1] = {
            "MODBUS_RTU_RESULT_OK",
            "MODBUS_RTU_RESULT_NOT_THIS_DEVICE",
            "MODBUS_RTU_RESULT_CRC_WRONG",
            "MODBUS_RTU_RESULT_FUNCTIONCODE_IS_NOT_SUPPORT",
            "MODBUS_RTU_RESULT_DATA_LENGTH_IS_INVALID",
            "MODBUS_RTU_RESULT_REGISTER_TYPE_IS_INCORRECT",
            "MODBUS_RTU_RESULT_REGISTER_NOT_EXIST",
            "MODBUS_RTU_RESULT_REGISTER_OUT_OF_RANGE",
            "MODBUS_RTU_RESULT_REGISTER_NOT_READABLE",
            "MODBUS_RTU_RESULT_REGISTER_NOT_WRITEABLE",
            "MODBUS_RTU_RESULT_BROADCAST_READ",
            "MODBUS_RTU_RESULT_WRITE_TIME_NOT_MATCH",
            "MODBUS_RTU_RESULT_WRITE_SINGLE_COIL_DATA_IS_INCORRECT",
            "MODBUS_RTU_RESULT_UNKNOWN"};
        return resultCodeStrings[thisPtr->_LastResult];
    }

#ifdef USE_CPLUSPLUS_CLASS

private:
#endif
    uint8_t static _GetFunctionCodeAttribute(const uint8_t code)
    {
        /// @brief 所有受支持的功能码的 Attribute
        const static uint8_t attributes[17] = {
        // 0x01
#ifdef USE_COIL
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE,
#else
        MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
#endif
        // 0x02
#ifdef USE_COIL
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE,
#else
        MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
#endif
            // 0x03
            (MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE),
            // 0x04
            (MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE),
        // 0x05
#ifdef USE_COIL
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE,
#else
        MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
#endif
            // 0x06
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS,
            // 0x07
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x08
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x09
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x0A
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x0B
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x0C
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x0D
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
            // 0x0E
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
        // 0x0F
#ifdef USE_COIL
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE,
#else
        MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_UNKNOWN,
#endif
            // 0x10
            MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS | MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE,

        };
        if (code - 1 >= sizeof(attributes))
        {
            return 0;
        }
        return attributes[code - 1];
    }
    inline static uint16_t _ToBigEndian(uint16_t value)
    {
#ifndef MODBUS_RTU_NO_TO_BIG_ENDIAN
        return (value >> 8) | (value << 8);
#else
    return value;
#endif
    }

    /// @brief 初始化
    /// @param thisPtr 实体
    /// @param deviceAddress 本机地址
    /// @param coiledRegisters 寄存器区 Array
    /// @param coiledRegistersAmount 寄存器区的数量
    static void MODBUS_RTU_Slave_Initialize(MODBUS_RTU_Slave *thisPtr, uint8_t deviceAddress, MODBUS_RTU_CoiledRegistersArea *coiledRegisters, size_t coiledRegistersAmount)
    {
        thisPtr->_DeviceAddress = deviceAddress;
        thisPtr->_CoiledRegistersAreas = coiledRegisters;
        thisPtr->_CoiledRegistersAreasAmount = coiledRegistersAmount;
        thisPtr->_ReturnFrameBytes = 0;
        thisPtr->_LastResult = MODBUS_RTU_RESULT_UNKNOWN;
#ifdef USE_WRITE_SEVEIAL_TIMES
        thisPtr->_DataLength_LastTime = 0;
        thisPtr->_Counter_RecvDataIsSame = 0;
#endif
    }

    static void _GenerateExceptionFrame(MODBUS_RTU_Slave *thisPtr)
    {
        thisPtr->_ReturnFrame[0] = thisPtr->_Prase_RequestFrame_DeviceAddress;
        thisPtr->_ReturnFrame[1] = thisPtr->_Prase_RequestFrame_FunctionCode + 0x80;
        switch (thisPtr->_LastResult)
        {
        case MODBUS_RTU_RESULT_FUNCTIONCODE_IS_NOT_SUPPORT:
            thisPtr->_ReturnFrame[2] = MODBUS_RTU_EXCEPTIONCODE_INVALID_FUNCTIONCODE;
            break;
        case MODBUS_RTU_RESULT_REGISTER_NOT_EXIST:
        case MODBUS_RTU_RESULT_REGISTER_NOT_READABLE:
        case MODBUS_RTU_RESULT_REGISTER_NOT_WRITEABLE:
            thisPtr->_ReturnFrame[2] = MODBUS_RTU_EXCEPTIONCODE_INVALID_REGISTER_ADDRESS;
            break;
        case MODBUS_RTU_RESULT_REGISTER_OUT_OF_RANGE:
        case MODBUS_RTU_RESULT_WRITE_SINGLE_COIL_DATA_IS_INCORRECT:
            thisPtr->_ReturnFrame[2] = MODBUS_RTU_EXCEPTIONCODE_INVALID_REQUEST_VALUE;
            break;
        default:
            thisPtr->_ReturnFrameBytes = 0;
            return;
        }
        uint16_t crcValue = CalculateCRC(thisPtr->_ReturnFrame, 3);
        thisPtr->_ReturnFrame[3] = crcValue & 0xFF;
        thisPtr->_ReturnFrame[3] = crcValue >> 8;
        thisPtr->_ReturnFrameBytes = 5;
    }

    /// @brief 检查 MODBUS RTU Request Frame Head,
    /// @details 校验地址是否是本设备;
    /// @details 校验功能码是否受支持
    /// @details 校验功能码对应的功能是否能执行
    /// @details 校验目标寄存器是否都在正确范围内
    /// @details 计算预期的请求帧长度;
    /// @details 计算读取或写入的数据的长度;
    /// @details 计算返回帧的长度
    /// @param thisPtr 实体
    /// @param dataPtr 接收到的数据
    /// @param length 数据长度, 至少 6 Bytes
    /// @return
    static bool
#ifdef USE_CPLUSPLUS_CLASS
    CheckHeader
#else
MODBUS_RTU_Slave_CheckHeader
#endif
        (MODBUS_RTU_Slave *thisPtr, const uint8_t *dataPtr, const size_t length)
    {
        int index;
        // 检查数据长度, MODBUS 帧长度至少为 8, 除去 CRC 则至少为 6, 头长度为 4 或 6
        if (length < 6)
        {
            thisPtr->_LastResult = MODBUS_RTU_RESULT_DATA_LENGTH_IS_INVALID;
        }
        else
        {
            // 格式化输入数据
            thisPtr->_Prase_RequestFrame_DeviceAddress = *dataPtr;
            thisPtr->_Prase_RequestFrame_FunctionCode = (MODBUS_RTU_FunctionCodes) * (dataPtr + 1);
            thisPtr->_Prase_RequestFrame_RegisterAddress = _ToBigEndian(*(uint16_t *)(dataPtr + 2));
            thisPtr->_Prase_RequestFrame_RequestAmount = _ToBigEndian(*(uint16_t *)(dataPtr + 4));
            // 检查报文中的设备地址
            if (thisPtr->_Prase_RequestFrame_DeviceAddress != thisPtr->_DeviceAddress && thisPtr->_Prase_RequestFrame_DeviceAddress != MODBUS_RTU_DEVICE_ADDRESS_BROADCAST)
            {
                thisPtr->_LastResult = MODBUS_RTU_RESULT_NOT_THIS_DEVICE;
            }
            else
            {
                // Summary
                // Definition:
                //     TargetRegOffset = RegisterAddress - AreaFirstAddress
                //     RequestAmount   = thisPtr->_Prase_RequestFrame_RequestAmount
                // Description:
                //     Code                 功能码
                //     Name                 功能码名称
                //     R/W                  操作类型 读 / 写
                //     Amount               操作类型 单个 / 多个
                //     Size                 操作类型 目标寄存器的类型
                //     TargetRegOffsetAddr  要操作的第一个寄存器相对于寄存器数组首个寄存器的偏移地址
                //     TargetRegsBytes      要操作的字节数
                //     BitOffset            操作线圈时的位偏移
                //     DataBytesIn_Frame    读取或写入时数据区的字节数
                //     RequestFrameBytes    请求帧的期望长度
                //     ReturnFrameBytes     返回帧的长度
                //  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                // | Code | Name                             | R/W |  Amount  |  Size  | TargetRegOffsetAddr |  TargetRegsBytes  |      BitOffset      |      DataBytesIn_Frame      |   RequestFrameBytes   |      ReturnFrameBytes       |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // |      |                                  |     |          |        |                     | (RequestAmount +  |                     |                             |                       |                             |
                // | 0x01 | Read Multiple Coils              |  R  | Multiple |  1Bit  | TargetRegOffset / 8 | TargetRegOffset % | TargetRegOffset % 8 | (RequestAmount - 1) / 8 + 1 |           8           |    DataBytesIn_Frame + 7    |
                // |      |                                  |     |          |        |                     |  8 - 1) / 8 + 1   |                     |                             |                       |                             |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // |      |                                  |     |          |        |                     | (RequestAmount +  |                     |                             |                       |                             |
                // | 0x02 | Read Multiple Discrete Inputs    |  R  | Multiple |  1Bit  | TargetRegOffset / 8 | TargetRegOffset % | TargetRegOffset % 8 | (RequestAmount - 1) / 8 + 1 |           8           |    DataBytesIn_Frame + 7    |
                // |      |                                  |     |          |        |                     |  8 - 1) / 8 + 1   |                     |                             |                       |                             |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // | 0x03 | Read Multiple Holding Registers  |  R  | Multiple | 16Bits | TargetRegOffset * 2 | RequestAmount * 2 |          0          |      RequestAmount * 2      |           8           |    DataBytesIn_Frame + 5    |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // | 0x04 | Read Multiple Input Registers    |  R  | Multiple | 16Bits | TargetRegOffset * 2 | RequestAmount * 2 |          0          |      RequestAmount * 2      |           8           |    DataBytesIn_Frame + 5    |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // |      |                                  |     |          |        |                     | (RequestAmount +  |                     |                             |                       |                             |
                // | 0x05 | Write Single Coil                |  W  |  Single  |  1Bit  | TargetRegOffset / 8 | TargetRegOffset % | TargetRegOffset % 8 |              2              |           8           |              8              |
                // |      |                                  |     |          |        |                     |  8 - 1) / 8 + 1   |                     |                             |                       |                             |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // | 0x06 | Write Single Holding Registers   |  W  |  Single  | 16Bits | TargetRegOffset * 2 | RequestAmount * 2 |          0          |              2              |           8           |              8              |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // |      |                                  |     |          |        |                     | (RequestAmount +  |                     | Ceiling(Ceiling(            |                       |                             |
                // | 0x0F | Write Multiple Coils             |  W  | Multiple |  1Bit  | TargetRegOffset / 8 | TargetRegOffset % | TargetRegOffset % 8 | RequestAmount - 1) /        | DataBytesIn_Frame + 9 |              9              |
                // |      |                                  |     |          |        |                     |  8 - 1) / 8 + 1   |                     | 2) * 2                      |                       |                             |
                // |------|----------------------------------|-----|----------|--------|---------------------|-------------------|---------------------|-----------------------------|-----------------------|-----------------------------|
                // | 0x10 | Write Multiple Holding Registers |  W  | Multiple | 16Bits | TargetRegOffset * 2 | RequestAmount * 2 |          0          |      RequestAmount * 2      | DataBytesIn_Frame + 9 |              8              |
                //  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                // 检查报文中的功能码是否受支持
                uint8_t funcCodeAttribute = _GetFunctionCodeAttribute(thisPtr->_Prase_RequestFrame_FunctionCode);
                if (funcCodeAttribute == 0)
                {
                    thisPtr->_LastResult = MODBUS_RTU_RESULT_FUNCTIONCODE_IS_NOT_SUPPORT;
                }
                else
                {
#ifdef USE_COIL
                    thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits = (funcCodeAttribute & MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_16BITS);
#endif
                    // 检查寄存器地址
                    thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr = nullptr;
                    for (index = 0; index < thisPtr->_CoiledRegistersAreasAmount; index++) // 遍历所有分区
                    {
                        if (thisPtr->_Prase_RequestFrame_RegisterAddress >= thisPtr->_CoiledRegistersAreas[index].FirstRegisterAddress &&
                            thisPtr->_Prase_RequestFrame_RegisterAddress <
                                thisPtr->_CoiledRegistersAreas[index].FirstRegisterAddress +
#ifdef USE_COIL
                                ((thisPtr->_CoiledRegistersAreas[index].RegisterType == MODBUS_RTU_REGISTER_TYPE_UINT16) ? (thisPtr->_CoiledRegistersAreas[index].Bytes >> 1) : (thisPtr->_CoiledRegistersAreas[index].Bytes << 3)))
#else
                                thisPtr->_Prase_RequestFrame_RequestAmount)
#endif
                                 // 起始地址命中第 index 个分区
                        {
                            thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr = thisPtr->_CoiledRegistersAreas + index;
                            break;
                        }
                    }
                    if (thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr == nullptr) // 没有命中任何分区
                    {
                        thisPtr->_LastResult = MODBUS_RTU_RESULT_REGISTER_NOT_EXIST;
                    }
                    else
                    {
                        thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write = (funcCodeAttribute & MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_WRITE);
                        thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple = (funcCodeAttribute & MODBUS_RTU_FUNCTIONCODE_ATTRIBUTE_MULTIPLE);
                        int TargetRegOffset = thisPtr->_Prase_RequestFrame_RegisterAddress - thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->FirstRegisterAddress;

                        if (!thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple)
                        {
                            thisPtr->_Prase_RequestFrame_RequestAmount = 1;
                        }
#ifdef USE_COIL
                        // 检查寄存器区的类型是否可以执行操作
                        if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits != (thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->RegisterType == MODBUS_RTU_REGISTER_TYPE_UINT16))
                        {
                            thisPtr->_LastResult = MODBUS_RTU_RESULT_REGISTER_TYPE_IS_INCORRECT;
                        }
                        else
#endif
                        {
                            // 计算读取或写入的数据的长度
                            thisPtr->_Prase_Calculate_TargetRegistersBytes =
#ifdef USE_COIL
                                thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? (thisPtr->_Prase_RequestFrame_RequestAmount << 1) : (thisPtr->_Prase_RequestFrame_RequestAmount + TargetRegOffset - ((TargetRegOffset >> 3) << 3) - 1) / 8 + 1;
#else
                            (thisPtr->_Prase_RequestFrame_RequestAmount << 1);
#endif
                            // 计算目标寄存器的偏移地址
                            thisPtr->_Prase_Calculate_TargetRegistersMemoryAddressOffset =
#ifdef USE_COIL
                                thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? (TargetRegOffset << 1) : (TargetRegOffset >> 3);
#else
                            (TargetRegOffset << 1);
#endif
                            // 检查目标寄存器范围是否超出本机寄存器范围
                            if (thisPtr->_Prase_RequestFrame_RequestAmount == 0 || (thisPtr->_Prase_Calculate_TargetRegistersMemoryAddressOffset + thisPtr->_Prase_Calculate_TargetRegistersBytes) > thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->Bytes)
                            {
                                thisPtr->_LastResult = MODBUS_RTU_RESULT_REGISTER_OUT_OF_RANGE;
                            }
                            else
                            {
                                // 检查 Operation
                                uint8_t registersAttribute = thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write ? MODBUS_RTU_REGISTER_ATTRIBUTE_WRITABLE : MODBUS_RTU_REGISTER_ATTRIBUTE_READABLE;
                                MODBUS_RTU_ResultCode failedResultCode = thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write ? MODBUS_RTU_RESULT_REGISTER_NOT_WRITEABLE : MODBUS_RTU_RESULT_REGISTER_NOT_READABLE;
                                uint16_t rangeStart =
#ifdef USE_COIL
                                    thisPtr->_Prase_Calculate_TargetRegistersMemoryAddressOffset >> (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? 1 : 0);
#else
                                TargetRegOffset;
#endif
                                uint16_t rangeEnd = rangeStart +
#ifdef USE_COIL
                                                    (thisPtr->_Prase_Calculate_TargetRegistersBytes >> (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? 1 : 0));
#else
                                                thisPtr->_Prase_RequestFrame_RequestAmount;
#endif
                                bool wrongAttribute = false;
                                for (index = rangeStart; index < rangeEnd; ++index)
                                {
                                    if ((thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->RegistersAttribute[index] & registersAttribute) == 0)
                                    {
                                        wrongAttribute = true;
                                        break;
                                    }
                                }
                                if (wrongAttribute)
                                {
                                    thisPtr->_LastResult = failedResultCode;
                                }
                                else
                                {
#ifdef USE_COIL
                                    // 计算位偏移
                                    thisPtr->_Prase_Calculate_TargetRegistersBitOffset = thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? 0 : TargetRegOffset % 8;
#endif
                                    // 计算读取或写入时请求帧或返回帧中数据的字节数
                                    uint16_t DataBytesIn_Frame =
                                        thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple ?
#ifdef USE_COIL
                                                                                                 (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? (thisPtr->_Prase_RequestFrame_RequestAmount << 1) : ((thisPtr->_Prase_RequestFrame_RequestAmount - 1) >> 3) + 1)
#else
                                                                                             thisPtr->_Prase_Calculate_TargetRegistersBytes
#endif
                                                                                                 : 2;

                                    // 计算预期的请求帧长度
                                    thisPtr->_Prase_Calculate_RequestFrameBytes = thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write && thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple ? DataBytesIn_Frame + 9 : 8;
                                    // 计算返回帧的长度
                                    thisPtr->_ReturnFrameBytes =
                                        thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write ?
#ifdef USE_COIL
                                                                                              ((thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple & thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits) ? 8 : 9)
                                                                                              : DataBytesIn_Frame + (DataBytesIn_Frame & 1) + (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits ? 5 : 7);
#else
                                    (thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple ? 8 : 9) : DataBytesIn_Frame + 5;
#endif

                                    thisPtr->_LastResult = MODBUS_RTU_RESULT_OK;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (thisPtr->_LastResult != MODBUS_RTU_RESULT_OK)
        {
            thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr = nullptr;
            _GenerateExceptionFrame(thisPtr);
            return false;
        }
        return true;
    }

    /// @brief 执行操作
    /// @param thisPtr 实体
    /// @param dataPtr 接收到的数据
    /// @param length 数据长度
    static bool
#ifdef USE_CPLUSPLUS_CLASS
    ProcessData
#else
MODBUS_RTU_Slave_ProcessData
#endif
        (MODBUS_RTU_Slave *thisPtr, const uint8_t *dataPtr, const size_t length)
    {
        // 检查是否已经检查 Header
        if (thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr == nullptr)
        {
#ifdef USE_CPLUSPLUS_CLASS
            CheckHeader
#else
        MODBUS_RTU_Slave_CheckHeader
#endif
                (thisPtr, dataPtr, length);
        }
        if (thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr != nullptr)
        {
            // 检查数据长度
            if (length < thisPtr->_Prase_Calculate_RequestFrameBytes)
            {
                thisPtr->_LastResult = MODBUS_RTU_RESULT_DATA_LENGTH_IS_INVALID;
            }
            else
            {
                // 检查 CRC
                if ((*(dataPtr + thisPtr->_Prase_Calculate_RequestFrameBytes - 2) | ((uint16_t)*(dataPtr + thisPtr->_Prase_Calculate_RequestFrameBytes - 1) << 8)) != CalculateCRC(dataPtr, thisPtr->_Prase_Calculate_RequestFrameBytes - 2))
                {
                    thisPtr->_LastResult = MODBUS_RTU_RESULT_CRC_WRONG;
                }
                else
                {

                    memset(thisPtr->_ReturnFrame, 0, thisPtr->_ReturnFrameBytes);
                    memcpy(thisPtr->_ReturnFrame, dataPtr, 6); // 向返回帧中复制 设备地址 功能码 寄存器地址 寄存器数 (不是所有返回帧都有寄存器地址和寄存器数, 但是大多数都有)
                    uint8_t *registerPtr = (uint8_t *)thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->Registers + thisPtr->_Prase_Calculate_TargetRegistersMemoryAddressOffset;
                    if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_Write) // 写入操作
                    {

#ifdef USE_WRITE_SEVEIAL_TIMES
                        bool writeRegister = thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->WriteTimes <= 1; // 寄存器区域需要多次写入
                        if (!writeRegister)																			  // 发送相同数据的次数不足, 需要判断数据是否相同
                        {
                            size_t checkLength = thisPtr->_Prase_Calculate_RequestFrameBytes - 4;
                            bool copyData = thisPtr->_DataLength_LastTime != checkLength;
                            if (!copyData) // 上次有数据且两次数据长度是一样的, 有可能两次数据是一样的
                            {
                                copyData = memcmp(thisPtr->_Data_LastTime, dataPtr + 2, thisPtr->_DataLength_LastTime) != 0; // 保存的是 [2 ~ -2)内的内存, 即功能码后面到 CRC 前面 (bubsok功能码和 CRC), 0 时内存是一样的
                                if (!copyData)																				 // 两次数据是一样的
                                {
                                    thisPtr->_Counter_RecvDataIsSame++;
                                }
                            }
                            if (copyData) // 两次数据不一样, 保存这一次的
                            {
                                thisPtr->_Counter_RecvDataIsSame = 1;
                                thisPtr->_DataLength_LastTime = checkLength;
                                memcpy(thisPtr->_Data_LastTime, dataPtr + 2, thisPtr->_DataLength_LastTime);
                            }
                            writeRegister = thisPtr->_Counter_RecvDataIsSame == thisPtr->_Prase_Calculate_TargetCoiledRegistersAreaPtr->WriteTimes;
                        }
                        if (!writeRegister)
                        {
                            thisPtr->_LastResult = MODBUS_RTU_RESULT_WRITE_TIME_NOT_MATCH;
                        }
                        else
                        {
                            thisPtr->_DataLength_LastTime = 0;
#endif

                            uint8_t bytes = 0;
#ifdef USE_COIL
                            if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits) // 写入 16 Bits
                            {
#endif
                                bytes = thisPtr->_Prase_Calculate_TargetRegistersBytes;
                                uint16_t *srcPtr = (uint16_t *)(dataPtr + (thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple ? 7 : 4));
                                uint16_t *dstPtr = (uint16_t *)(registerPtr);
                                uint16_t amount = thisPtr->_Prase_Calculate_TargetRegistersBytes >> 1;
                                for (int i = 0; i < amount; ++i)
                                {
                                    *(dstPtr++) = _ToBigEndian(*(srcPtr++));
                                }
#ifdef USE_COIL
                            }
                            else if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple) // 写入多个 1 Bit
                            {
                                // Description:
                                // 预处理: SRC中可能有些位不需要写入, 要把这部分置零
                                // 处理前 8 - offset 位
                                //     dst[0] [0, offset)     位不变, [offset, 8) 位归零
                                //     dst[0] [offset, 8)     位存入  src[0] (0, 8 - offset) 位
                                // 处理后 offset 位
                                //     dst[1] [0, 8 - offset) 位归零, [8 - offset, 8) 位不变
                                //     dst[1] [0, 8 - offset) 位存入  src[0] (8 - offset, 8) 位
                                uint8_t *srcPtr = thisPtr->_ReturnFrame;
                                uint8_t *dstPtr = registerPtr;
                                bytes = ((thisPtr->_Prase_RequestFrame_RequestAmount - 1) >> 3) + 1;
                                // 准备数据: 将寄存器指定区域置零
                                // Details:
                                //     Step0. 使用 ReturnFrame 作为临时区域
                                //     Step1. 将 ReturnFrame 前 RequestAmount 位设置为 0xFF
                                //     Step2. 根据 TargetRegistersBitOffset 将 ReturnFrame 向左移位, 高位移出的数据要补到下一个字节的低位
                                //     Step3. 寄存器要操作的区域与 ReturnFrame 进行 AND 运算
                                memset(srcPtr, 0xFF, bytes);
                                if (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111)
                                {
                                    srcPtr[thisPtr->_Prase_RequestFrame_RequestAmount >> 3] &= 0xFF >> (8 - (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111));
                                }
                                srcPtr[bytes] = 0; // 下一位也要置零, 因为数据可能会移到这里
                                for (int i = bytes; i > 0; --i)
                                {
                                    srcPtr[i] |= srcPtr[i - 1] >> (8 - thisPtr->_Prase_Calculate_TargetRegistersBitOffset);
                                    srcPtr[i - 1] <<= thisPtr->_Prase_Calculate_TargetRegistersBitOffset;
                                    dstPtr[i] &= ~srcPtr[i];
                                }
                                dstPtr[0] &= ~srcPtr[0];
                                // 赋值
                                // Details: 原理与 "准备数据" 类似,
                                //     Step1 变为: 将源数据前 RequestAmount 位拷贝到 ReturnFrame
                                //     Step3 变为: 寄存器要操作的区域与 ReturnFrame 进行 OR 运算
                                memcpy(thisPtr->_ReturnFrame, dataPtr + 7, bytes + (bytes & 1));
                                srcPtr[bytes + (bytes & 1)] = 0;
                                if (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111)
                                {
                                    srcPtr[thisPtr->_Prase_RequestFrame_RequestAmount >> 3] &= 0xFF >> (8 - (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111));
                                }
                                // 准备数据_移位_寄存器指定位归零
                                srcPtr[bytes] = 0;
                                for (int i = bytes; i > 0; --i)
                                {
                                    srcPtr[i] |= srcPtr[i - 1] >> (8 - thisPtr->_Prase_Calculate_TargetRegistersBitOffset);
                                    srcPtr[i - 1] <<= thisPtr->_Prase_Calculate_TargetRegistersBitOffset;
                                    dstPtr[i] |= srcPtr[i];
                                }
                                dstPtr[0] |= srcPtr[0];
                            }
                            else // 写入 1 个 1 Bit
                            {
                                switch (_ToBigEndian(*(uint16_t *)(dataPtr + 4)))
                                {
                                case 0:
                                {
                                    *registerPtr &= ~(1 << thisPtr->_Prase_Calculate_TargetRegistersBitOffset);
                                    break;
                                }
                                case 0xFF00:
                                {
                                    *registerPtr |= (1 << thisPtr->_Prase_Calculate_TargetRegistersBitOffset);
                                    break;
                                }
                                default:
                                {
                                    thisPtr->_LastResult = MODBUS_RTU_RESULT_WRITE_SINGLE_COIL_DATA_IS_INCORRECT;
                                    return false;
                                }
                                }
                            }
#endif

                            if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_Multiple)
                            {
                                memcpy(thisPtr->_ReturnFrame, dataPtr, 6);
                                thisPtr->_ReturnFrame[6] = bytes;
                                uint16_t crcValue = CalculateCRC(thisPtr->_ReturnFrame, thisPtr->_ReturnFrameBytes - 2);
                                thisPtr->_ReturnFrame[thisPtr->_ReturnFrameBytes - 2] = crcValue & 0xFF;
                                thisPtr->_ReturnFrame[thisPtr->_ReturnFrameBytes - 1] = crcValue >> 8;
                            }
                            else
                            {
                                memcpy(thisPtr->_ReturnFrame, dataPtr, thisPtr->_ReturnFrameBytes);
                            }
#ifdef USE_WRITE_SEVEIAL_TIMES
                        }
#endif
                    }
                    else // 读取操作
                    {
#ifdef USE_COIL
                        if (thisPtr->_Prase_Calculate_FunctionCodeAttribute_16Bits) // 读取 16 Bits, 返回帧 0-2 分别为 00设备地址 01功能码 02字节数
                        {
#endif
                            thisPtr->_ReturnFrame[2] = thisPtr->_Prase_Calculate_TargetRegistersBytes;
                            uint16_t *dstPtr = (uint16_t *)(thisPtr->_ReturnFrame + 3);
                            uint16_t *srcPtr = (uint16_t *)(registerPtr);
                            uint16_t amount = thisPtr->_Prase_Calculate_TargetRegistersBytes >> 1;
                            for (int i = 0; i < amount; ++i)
                            {
                                *(dstPtr++) = _ToBigEndian(*(srcPtr++));
                            }
#ifdef USE_COIL
                        }
                        else // 读取 1 Bit, 返回帧 0-5 分别为 00设备地址 01功能码 0203地址 04字节数, 要移位
                        {
                            memcpy(thisPtr->_ReturnFrame + 2, dataPtr + 2, 2);
                            thisPtr->_ReturnFrame[4] = ((thisPtr->_Prase_RequestFrame_RequestAmount - 1) >> 3) + 1;
                            memcpy(thisPtr->_ReturnFrame + 5, registerPtr, thisPtr->_Prase_Calculate_TargetRegistersBytes);
                            // 移位:
                            // 第 n 个字节右移 Offset 位
                            // 第 n+1 个字节的低 Offset 位拷贝到第 m 个字节的低 Offset 位
                            //     Details: 取 n+1 个字节的低 Offset 位: nTemp ~(0b11111111 << Offset) & nValue
                            //              将 低 Offset 位放到 高 Offset 位上: nTemp <<= (8 - Offset)
                            //              拷贝: nValue |= nTemp;
                            for (uint8_t *ptr = thisPtr->_ReturnFrame + 5; ptr < thisPtr->_ReturnFrame + 5 + thisPtr->_Prase_Calculate_TargetRegistersBytes; ++ptr)
                            {
                                *ptr >>= thisPtr->_Prase_Calculate_TargetRegistersBitOffset;
                                *ptr |= (*(ptr + 1) & ~(0xFF << thisPtr->_Prase_Calculate_TargetRegistersBitOffset)) << (8 - thisPtr->_Prase_Calculate_TargetRegistersBitOffset);
                            }
                            // 访问的寄存器数 / 8 得到返回的字节数, 其中最后一个字节可能包含不访问的数据, 要将这部分置零
                            if (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111)
                            {
                                *(thisPtr->_ReturnFrame + 4 + thisPtr->_Prase_Calculate_TargetRegistersBytes) &= ~(0xFF << (thisPtr->_Prase_RequestFrame_RequestAmount & 0b111));
                            }
                        }
                        uint16_t crcValue = CalculateCRC(thisPtr->_ReturnFrame, thisPtr->_ReturnFrameBytes - 2);
                        thisPtr->_ReturnFrame[thisPtr->_ReturnFrameBytes - 2] = crcValue & 0xFF;
                        thisPtr->_ReturnFrame[thisPtr->_ReturnFrameBytes - 1] = crcValue >> 8;
#endif
#ifdef USE_WRITE_SEVEIAL_TIMES
                        thisPtr->_Counter_RecvDataIsSame = 0;
#endif
                    }
                    thisPtr->_LastResult = MODBUS_RTU_RESULT_OK;
                }
            }
        }
        return thisPtr->_LastResult == MODBUS_RTU_RESULT_OK;
    }

    inline static MODBUS_RTU_ResultCode
#ifdef USE_CPLUSPLUS_CLASS
    GetLastResult
#else
MODBUS_RTU_Slave_GetLastResult
#endif
        (MODBUS_RTU_Slave *thisPtr)
    {
        return thisPtr->_LastResult;
    }
inline static uint16_t
#ifdef USE_CPLUSPLUS_CLASS
    GetRequestFrameLength
#else
    MODBUS_RTU_Slave_GetRequestFrameLength
#endif
        (MODBUS_RTU_Slave *thisPtr)
    {
        return thisPtr->_Prase_Calculate_RequestFrameBytes;
    }
    inline static uint16_t
#ifdef USE_CPLUSPLUS_CLASS
    GetReturnFrameLength
#else
MODBUS_RTU_Slave_GetReturnFrameLength
#endif
        (MODBUS_RTU_Slave *thisPtr)
    {
        return thisPtr->_ReturnFrameBytes;
    }
    inline static const unsigned char *
#ifdef USE_CPLUSPLUS_CLASS
    GetReturnData
#else
MODBUS_RTU_Slave_GetReturnData
#endif
        (MODBUS_RTU_Slave *thisPtr)
    {
        return thisPtr->_ReturnFrame;
    }
    inline static uint8_t
#ifdef USE_CPLUSPLUS_CLASS
    GetDeviceAddress
#else
MODBUS_RTU_Slave_GetDeviceAddress
#endif
        (MODBUS_RTU_Slave *thisPtr)
    {
        return thisPtr->_DeviceAddress;
    }

#ifdef USE_CPLUSPLUS_CLASS
public:
    MODBUS_RTU_Slave(uint8_t deviceAddress, MODBUS_RTU_CoiledRegistersArea *coiledRegisters, size_t coiledRegistersAmount)
    {
        MODBUS_RTU_Slave_Initialize(this, deviceAddress, coiledRegisters, coiledRegistersAmount);
    }
    inline MODBUS_RTU_ResultCode GetLastResult() { return GetLastResult(this); }
    inline size_t GetReturnFrameLength() { return GetReturnFrameLength(this); }
    inline const unsigned char *GetReturnData() { return GetReturnData(this); }
    inline uint8_t GetDeviceAddress() { return GetDeviceAddress(this); }
    inline bool CheckHeader(const uint8_t *dataPtr, const size_t length) { return CheckHeader(this, dataPtr, length); }
    inline bool ProcessData(const uint8_t *dataPtr, const size_t length) { return ProcessData(this, dataPtr, length); }
#endif

#ifdef USE_CPLUSPLUS_CLASS
private:
#endif
#ifdef USE_CPLUSPLUS_CLASS
};
};
#endif

#endif // __MODBUS_RTU_SLAVE_H__

// MODBUS RTU 帧结构
// 0x01 | 读取多线圈:
// 0x02 | 读取多离散输入寄存器:
//      Request:
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|-------------------- 04 05 --------------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress                  RegistersAmount                |   CRC   |
//          Data: |     01            01      |      00 01                            00 04                     |  6C 09  |
//      Response: |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|------ 04 ------|------------- 05 -------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress     BytesCount                 Data             |   CRC   |
//          Data: |     00            01      |      00 01              01                      06              |  ED 89  |
// 0x03 | 读取多保持寄存器:
// 0x04 | 读取多输入寄存器:
//      Request:  |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 05 -----|----- 02 03 -----|-------------------- 04 05 --------------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress                  RegistersAmount                |   CRC   |
//          Data: |     01            03      |      00 01                            00 02                     |  95 CB  |
//      Response: |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 01 -----|------  02 ------|----------------- 03 04 05 06 -----------------|- 07 08 -|
//          Desc: | DeviceAddr   FunctionCode |    BytesCount                          Data                     |   CRC   |
//          Data: |     01            03      |        04                          01 01 02 02                  |  2A AE  |
// 0x05 | 写入单线圈:
// 0x06 | 写入单保持寄存器:
//      Request:  |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 05 -----|----- 02 03 -----|-------------------- 04 05 --------------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress                       Data                      |   CRC   |
//          Data: |     01            05      |      00 01                            FF 00                     |  DD FA  |
//      Response: |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 05 -----|----- 02 03 -----|-------------------- 04 05 --------------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress                       Data                      |   CRC   |
//          Data: |     01            05      |      00 01                            FF 00                     |  DD FA  |
// 0x0F | 写入多线圈:
//      Request:  |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|----- 04 05 -----|---- 06 ----|---- 07  08 ----|- 09 10 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress   RegistersAmount   BytesCount        Data      |   CRC   |
//          Data: |     01            0F      |      00 01              00 02           01           00  10     |  17 45  |
//      Response: |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|----------- 04  05 -----------|------ 06 ------|- 07 08 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress         Registers Amount           BytesCount   |   CRC   |
//          Data: |     01            0F      |      00 01                   00  02                    01       |  CA 63  |
// 0x10 | 写入多寄存器:
//      Request:  |                           |                                                                 |         |
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|----- 04 05 -----|---- 06 ----|- 07 08  09 10 -|- 11 12 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress   RegistersAmount   BytesCount        Data      |   CRC   |
//          Data: |     01            10      |      00 01             00 02            04        01 01  02 02  |  E2 FE  |
//      Response:
//          Byte: |---- 00 ----|----- 01 -----|----- 02 03 -----|-------------------- 04 05 --------------------|- 06 07 -|
//          Desc: | DeviceAddr   FunctionCode | RegisterAddress                  RegistersAmount                |   CRC   |
//          Data: |     01            10      |      00 01                            00 02                     |  10 08  |
// 校验字段低 8 位在前, 高 8 位在后
