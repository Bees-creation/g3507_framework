/**
 * @brief 传感器任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_sensor.h"

Class_I2C_IRS IRS;

Class_IMU_Mspm0g3507 IMU(UART2_Manage_Object);

uint8_t Digital_Channels[8];
uint8_t Analog_Channels[8];

Angle_t Yaw;
float GyroZ;

Angle_t Previous_Yaw;
Rotation_t Current_Rotation;
Rotation_t Target_Rotation;

void Rotation_Init(void) {
    Previous_Yaw = Yaw;
    Target_Rotation = (float)Yaw + (-360.0f);
}

void Rotation_Update(void) {
    Current_Rotation = ((float)Current_Rotation + (float)(Yaw - Previous_Yaw));
    Previous_Yaw = Yaw;
}

void Rotation_Clear(void) {
    Current_Rotation = 0.0f;
}

void Sensor_Init(void) {
    // 巡线模块初始化
    I2C_DMA_Init(I2C0, NULL, -1, -1, IRS_Callback);
    IRS.Init(I2C0, IRS_Detect_Type_Positive);

    // IMU模块初始化
    UART_DMA_Init(UART2, IMU_Callback, UART_BUFFER_SIZE, NULL, -1, -1);
    IMU.Init();
}

void Sensor_Task(void) {
    // 巡线模块任务
    IRS.TIM_Feedback_PeriodElapsedCallback();
    for (int i = 0; i < 8; i++) {
        Digital_Channels[i] = IRS.Get_Digital_Channels()[i];
    }
    for (int i = 0; i < 8; i++) {
        Analog_Channels[i] = IRS.Get_Analog_Channels()[i];
    }

    // IMU模块任务
    Yaw = -IMU.Get_Yaw();
    GyroZ = -IMU.Get_GyroZ();
}

void IRS_Callback(uint8_t *Buffer, uint16_t Length) {

}

void IMU_Callback(uint8_t *Buffer, uint16_t Length) {
    IMU.UART_Callback();
}
