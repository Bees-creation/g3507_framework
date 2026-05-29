/**
 * @brief 调试信息显示
 * @date 2026/5/24
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_display.h"

// 运动状态数据
Struct_Motion_State MotionState = {0};

// 串口工具
Class_Serialport Serialport_Object;

const char Serialport_Rx_Variable_Assignment_List[][SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH] = {
    "angle",
    "omega",
    "torque",
};

void Display_Init(void) {
    UART_DMA_Init(UART0, UART0_Callback, UART_BUFFER_SIZE, DMA, DMA_CHANNEL_0, DMA_CHANNEL_1);
    Serialport_Object.Init(UART0, 3, (const char**)Serialport_Rx_Variable_Assignment_List, Serialport_Data_Type_JUSTFLOAT, 0x00, 0x00);
}

void Display_Task(void) {
    // 设置数据
    Serialport_Object.Set_Data(3, &MotionState.angle, &MotionState.omega, &MotionState.torque);
    // TIM定时器中断检查串口接收空闲状态，并重启DMA接收
    Serialport_Object.TIM_Read_PeriodElapsedCallback();
    // TIM定时器中断增加数据到发送缓冲区，并开启发送
    Serialport_Object.TIM_Write_PeriodElapsedCallback();
}

void UART0_Callback(uint8_t *Buffer, uint16_t Length) {
    Serialport_Object.UART_RxCpltCallback();

    switch (Serialport_Object.Get_Variable_Index()) {
    case 0:
        MotionState.angle = Serialport_Object.Get_Variable_Value();
        break;
    case 1:
        MotionState.omega = Serialport_Object.Get_Variable_Value();
        break;
    case 2:
        MotionState.torque = Serialport_Object.Get_Variable_Value();
        break;
    default:
        break;
    }

    UART_DMA_Receive(UART0, UART0_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
}
