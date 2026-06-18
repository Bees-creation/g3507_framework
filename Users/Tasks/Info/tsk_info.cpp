/**
 * @brief 调试信息显示
 * @date 2026/5/24
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_info.h"

/* 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Sensor/tsk_sensor.h"
#include "Tasks/Motion/tsk_motion.h"
/* 在此处引用任务函数头文件 --  end  -- */

// 串口工具
Class_Serialport Serialport_Object;

const char Serialport_Rx_Variable_Assignment_List[][SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH] = {
    "target_distance",
    "target_speed",
    "target_omega",
};

void Info_Init(void) {
    UART_DMA_Init(UART1, Serialport_Callback, UART_BUFFER_SIZE, DMA, DMA_CHANNEL_0, DMA_CHANNEL_1);
    Serialport_Object.Init(UART1, 3, (const char**)Serialport_Rx_Variable_Assignment_List, Serialport_Data_Type_JUSTFLOAT, 0x00, 0x00);
}

void Info_Task(void) {
    // 设置数据
    // Serialport_Object.Set_Data(4, &Motor_State_Left.now_angle, &Motor_State_Left.now_omega, &Motor_State_Right.now_angle, &Motor_State_Right.now_omega);
    // Serialport_Object.Set_Data(2, &Chassis_State.now_speed, &Chassis_State.now_omega);
    // TIM定时器中断检查串口接收空闲状态，并重启DMA接收
    Serialport_Object.TIM_Read_PeriodElapsedCallback();
    // TIM定时器中断增加数据到发送缓冲区，并开启发送
    Serialport_Object.TIM_Write_PeriodElapsedCallback();
}

void Serialport_Callback(uint8_t *Buffer, uint16_t Length) {
    Serialport_Object.UART_RxCpltCallback();

    switch (Serialport_Object.Get_Variable_Index()) {
    case 0:
        Chassis_State.target_distance = Serialport_Object.Get_Variable_Value();
        break;
    case 1:
        Chassis_State.target_speed = Serialport_Object.Get_Variable_Value();
        break;
    case 2:
        Chassis_State.target_omega = Serialport_Object.Get_Variable_Value();
        break;
    default:
        break;
    }
}
