/**
 * @brief 串口调试信息
 * @date 2026/5/19
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_SERIALPORT_H
#define DVC_SERIALPORT_H

#include "Drivers/UART/drv_uart.h"

#include <string.h>
#include <stdarg.h>

/**
 * @brief 串口工具单条指令长度
 * 
 * @note 接收指令字典的类型为char* [SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH]
 */
#define SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH (50)

/**
 * @brief 串口工具传输数据类型
 */
enum Enum_Serialport_Data_Type {
    // 原始字节流
    Serialport_Data_Type_UINT8 = 0,
    Serialport_Data_Type_UINT16,
    Serialport_Data_Type_UINT32,
    Serialport_Data_Type_INT8,
    Serialport_Data_Type_INT16,
    Serialport_Data_Type_INT32,
    Serialport_Data_Type_FLOAT,
    Serialport_Data_Type_DOUBLE,
    // 特殊帧格式
    Serialport_Data_Type_JUSTFLOAT = 10,
};

/**
 * @brief 串口工具，要求32位地址格式，最多支持12个通道
 */
class Class_Serialport {
public:
    /**
     * @brief 串口工具初始化
     * 
     * @param UARTx 绑定的UART
     * @param __Serialport_Rx_Variable_Assignment_Num 接收指令字典的数量
     * @param __Serialport_Rx_Variable_Assignment_List 接收指令字典列表指针
     * @param __Serialport_Tx_Data_Type 串口发送数据类型
     * @param __Frame_Header 帧头标识符，0x00为无帧头
     * @param __Frame_Trailer 帧尾标识符，0x00为无帧尾
     */
    void Init(UART_Regs *UARTx, uint8_t __Serialport_Rx_Variable_Assignment_Num = 0, const char **__Serialport_Rx_Variable_Assignment_List = NULL, Enum_Serialport_Data_Type __Serialport_Tx_Data_Type = Serialport_Data_Type_FLOAT, uint8_t __Frame_Header = 0x00, uint8_t __Frame_Trailer = 0x00);

    /**
     * @brief 获取当前接收的指令在指令字典中的编号
     * 
     * @retval 当前接收的指令在指令字典中的编号
     */
    int8_t Get_Variable_Index();

    /**
     * @brief 获取当前接收的指令在指令字典中的值
     * 
     * @retval 当前接收的指令在指令字典中的值
     */
    double Get_Variable_Value();

    /**
     * @brief 添加被发送的数据到成员变量Data[]
     * 
     * @param Number 添加的数据数量
     * @param ... 每个数据的指针，最多12个
     */
    void Set_Data(uint8_t Number, ...);

    /**
     * @brief UART通信接收回调函数
     */
    void UART_RxCpltCallback(void);

    /**
     * @brief TIM定时器中断增加数据到发送缓冲区，并开启发送
     */
    void TIM_Write_PeriodElapsedCallback();

    /**
     * @brief TIM定时器中断检查串口接收空闲状态，并重启DMA接收
     */
    void TIM_Read_PeriodElapsedCallback();

protected:
    /* 初始化成员变量 */

    // 绑定的UART
    Struct_UART_Manage_Object *UART_Manage_Object;
    // 接收指令字典的数量
    uint8_t UART_Rx_Variable_Num;
    // 接收指令字典列表指针
    const char **UART_Rx_Variable_List;
    // 串口发送数据类型
    Enum_Serialport_Data_Type UART_Tx_Data_Type;
    // 帧头标识符
    uint8_t Frame_Header;
    // 帧尾标识符
    uint8_t Frame_Trailer;

    /* 内部变量 */

    // 需要绘图的各个变量数据地址
    const void *Data[12];
    // 当前发送的数据长度，等价于新数据偏移量
    uint8_t Data_Number = 0;
    // 当前接收的指令在指令字典中的编号
    int8_t Variable_Index = 0;
    // 当前接收的指令在指令字典中的值
    float Variable_Value = 0.0f;
    // 发送数组字节长度
    uint16_t Frame_Size;

    /* 内部函数 */

    /**
     * @brief 判断指令变量名
     * 
     * @retval 指令数值位置的指针，也就是"variable=value#"中v的坐标
     */
    uint8_t Judge_Variable_Name();

    /**
     * @brief 判断指令变量数值
     */ 
    void Judge_Variable_Value(int flag);

    /**
     * @brief 串口绘图数据输出到UART发送缓冲区
     */
    void Output();

    /**
     * @brief 串口发送
     */
    void Send();

    /**
     * @brief 串口接收
     */
    void Receive();
};

#endif /* DVC_SERIALPORT_H */
