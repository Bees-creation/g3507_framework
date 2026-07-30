/**
 * @brief 红外传感器
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_INFRAREDSENSOR_H
#define DVC_INFRAREDSENSOR_H

#include "Drivers/GPIO/drv_gpio.h"
#include "Drivers/I2C/drv_i2c.h"

enum Enum_IRS_Detect_Type {
    IRS_Detect_Type_Positive = 0,// 1表示白色
    IRS_Detect_Type_Negative,// 1表示黑色
};

/**
 * @brief 八通道红外巡线模块
 */
class Class_8C_IRS {
public:
    void Init(Enum_IRS_Detect_Type __IRS_Detect_Type, GPIO_PORT *__Selector_Port_AD0, GPIO_PIN __Selector_Pin_AD0, GPIO_PORT *__Selector_Port_AD1, GPIO_PIN __Selector_Pin_AD1, GPIO_PORT *__Selector_Port_AD2, GPIO_PIN __Selector_Pin_AD2, GPIO_PORT *__Data_Port, GPIO_PIN __Data_Pin);

    void TIM_Feedback_PeriodElapsedCallback();

    inline uint8_t *Get_Channels(void) {
        return Channels;
    }

protected:
    // 通道值，1表示轨迹
    uint8_t Channels[8];

    Enum_IRS_Detect_Type IRS_Detect_Type;

    // 3线转8线数据选择器引脚
    GPIO_PORT *Selector_Ports[3];
    GPIO_PIN Selector_Pins[3];
    // 输出引脚
    GPIO_PORT *Data_Port;
    GPIO_PIN Data_Pin;
};

/* 灰度传感器宏定义列表 */
// 设备地址
#define GW_GRAY_ADDR_DEF 0x4C // 默认 I2C 从机地址

// Ping 测试
#define GW_GRAY_PING 0xAA // Ping 命令寄存器
#define GW_GRAY_PING_OK 0x66 // Ping 成功应答值

// 操作模式
#define GW_GRAY_DIGITAL_MODE 0xDD // 数字模式

// 模拟模式
#define GW_GRAY_ANALOG_BASE 0xB0 // 模拟模式基址
#define GW_GRAY_ANALOG_MODE GW_GRAY_ANALOG_BASE // 0xB0
#define GW_GRAY_ANALOG(n) (GW_GRAY_ANALOG_BASE + (n)) // 单通道模拟读取

// 归一化
#define GW_GRAY_ANALOG_NORMALIZE 0xCF // 归一化使能寄存器

// 校准参数
#define GW_GRAY_CALIBRATION_BLACK 0xD0 // 黑色滞回比较参数
#define GW_GRAY_CALIBRATION_WHITE 0xD1 // 白色滞回比较参数

// 通道使能
#define GW_GRAY_ANALOG_CHANNEL_ENABLE 0xCE // 通道使能寄存器
#define GW_GRAY_ANALOG_CH_EN(n) (0x01 << ((n) - 1)) // 通道 n 使能位掩码
#define GW_GRAY_ANALOG_CH_EN_ALL 0xFF // 全部通道使能

// 错误与维护
#define GW_GRAY_ERROR 0xDE // 读取错误信息
#define GW_GRAY_REBOOT 0xC0 // 软件重启
#define GW_GRAY_FIRMWARE 0xC1 // 读取固件版本号

// 地址修改
#define GW_GRAY_CHANGE_ADDR 0xAD // 设置新的 I2C 设备地址

// 广播重置
#define GW_GRAY_BROADCAST_RESET "\xB8\xD0\xCE\xAA\xBF\xC6\xBC\xBC" // 广播重置魔术字

// 位操作工具
#define GW_GRAY_GET_BIT(val, n) (((val) >> ((n) - 1)) & 0x01)// 获取传感器数据中第 n 位

// 将传感器 8 位数据展开到通道数组
inline void GW_Gray_Split_Channels(uint8_t sensor_value, uint8_t *channels) {
    for (uint8_t i = 0; i < 8; i++) {
        channels[i] = (sensor_value >> i) & 0x01;
    }
}

/**
 * @brief 使用I2C的红外巡线模块
 */
class Class_I2C_IRS {
public:
    void Init(I2C_INST *I2Cx, Enum_IRS_Detect_Type __IRS_Detect_Type);

    void TIM_Feedback_PeriodElapsedCallback();

    // I2C 接收回调函数
    void I2C_Callback(uint8_t *Buffer, uint16_t Length);

    // 传感器基本操作
    uint8_t Ping(void);
    uint8_t Read_Digital(uint8_t *data);
    uint8_t Read_Analog(uint8_t *buffer);
    uint8_t Read_Single_Analog(uint8_t channel, uint8_t *data);
    uint8_t Read_Normalize(uint8_t *buffer);

    // 传感器配置
    void Set_Calibration_Black(uint8_t threshold);
    void Set_Calibration_White(uint8_t threshold);
    void Set_Channel_Enable(uint8_t mask);
    void Set_Address(uint8_t addr);

    // 传感器维护
    uint8_t Get_Error(uint8_t *data);
    uint8_t Get_Firmware(uint8_t *data);
    void Reboot(void);
    void Broadcast_Reset(void);

    inline uint8_t *Get_Digital_Channels(void) {
        return Digital_Channels;
    }
    inline uint8_t *Get_Analog_Channels(void) {
        return Analog_Channels;
    }

protected:
    // I2C通信实例
    I2C_INST *I2C;
    // I2C设备地址
    uint8_t I2C_Address;

    // 数字通道值，1表示轨迹
    uint8_t Digital_Channels[8];
    // 模拟通道值
    uint8_t Analog_Channels[8];

    Enum_IRS_Detect_Type IRS_Detect_Type;

    // DMA模式下等待读取的寄存器地址，0表示空闲
    uint8_t Pending_Register;

    // I2C 读写
    uint8_t I2C_Write_Register(uint8_t reg, uint8_t *data, uint8_t len);
    uint8_t I2C_Read_Register(uint8_t reg, uint8_t *data, uint8_t len);
};

#endif /* DVC_INFRAREDSENSOR_H */
