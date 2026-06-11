/**
 * @brief 传感器任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_SENSOR_H
#define TSK_SENSOR_H

#include "Device/IRS/dvc_infraredsensor.h"
#include "Device/IMU/dvc_imu.h"

// 通道值，1表示轨迹
extern float Channels[8];

extern float Yaw;
extern float GyroZ;

#define IRS_PORT_AD0 GPIO_PORT_A
#define IRS_PIN_AD0 GPIO_PIN_25
#define IRS_PORT_AD1 GPIO_PORT_A
#define IRS_PIN_AD1 GPIO_PIN_24
#define IRS_PORT_AD2 GPIO_PORT_A
#define IRS_PIN_AD2 GPIO_PIN_26
#define IRS_PORT_OUT GPIO_PORT_A
#define IRS_PIN_OUT GPIO_PIN_27

void Sensor_Init(void);

void Sensor_Task(void);

void IMU_Callback(uint8_t *Buffer, uint16_t Length);

#endif /* TSK_SENSOR_H */
