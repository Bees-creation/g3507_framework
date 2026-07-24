/**
 * @brief 传感器任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_sensor.h"

Class_8C_IRS IRS;

Class_IMU_Mspm0g3507 IMU(UART2_Manage_Object);

uint8_t Channels[8];

float Yaw;
float GyroZ;

void Sensor_Init(void) {
    // 巡线模块初始化
    IRS.Init(IRS_Detect_Type_Negative, IRS_PORT_AD0, IRS_PIN_AD0, IRS_PORT_AD1, IRS_PIN_AD1, IRS_PORT_AD2, IRS_PIN_AD2, IRS_PORT_OUT, IRS_PIN_OUT);

    // IMU模块初始化
    UART_DMA_Init(UART2, IMU_Callback, UART_BUFFER_SIZE, NULL, -1, -1);
    IMU.Init();
}

void Sensor_Task(void) {
    // 巡线模块任务
    IRS.TIM_Feedback_PeriodElapsedCallback();
    for (int i = 0; i < 8; i++) {
        Channels[i] = IRS.Get_Channels()[i];
    }

    // IMU模块任务
    Yaw = IMU.Get_Yaw();
    GyroZ = IMU.Get_GyroZ();
}

void IMU_Callback(uint8_t *Buffer, uint16_t Length) {
    IMU.UART_Callback();
}
