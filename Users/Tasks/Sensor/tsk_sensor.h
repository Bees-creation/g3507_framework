/**
 * @brief 传感器任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_SENSOR_H
#define TSK_SENSOR_H

#include "Algorithm/Math/alg_math.h"
#include "Device/IRS/dvc_infraredsensor.h"
#include "Device/IMU/dvc_imu.h"

// 数字通道值，1表示轨迹
extern uint8_t Digital_Channels[8];
// 模拟通道值
extern uint8_t Analog_Channels[8];

// 偏航角，与底盘坐标系反向，即逆时针为正方向
extern Angle_t Yaw;
// 偏航加速度
extern float GyroZ;

// 上次绝对角度
extern Angle_t Previous_Yaw;
// 当前相对角度
extern Rotation_t Current_Rotation;
// 目标相对角度
extern Rotation_t Target_Rotation;

void Rotation_Init(void);

void Rotation_Update(void);

void Rotation_Clear(void);

void Sensor_Init(void);

void Sensor_Task(void);

void IRS_Callback(uint8_t *Buffer, uint16_t Length);

void IMU_Callback(uint8_t *Buffer, uint16_t Length);

#endif /* TSK_SENSOR_H */
