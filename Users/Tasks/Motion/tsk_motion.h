/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_MOTION_H
#define TSK_MOTION_H

#include "Device/Chassis/dvc_chassis.h"

typedef struct Struct_QEI_State {
    float target_angle;
    float now_angle;
    float target_omega;
    float now_omega;
} Struct_QEI_State;

typedef struct Struct_Chassis_State {
    float target_distance;
    float now_distance;
    float target_speed;
    float now_speed;
    float target_omega;
    float now_omega;
} Struct_Chassis_State;

extern Struct_QEI_State QEI_State_Left;
extern Struct_QEI_State QEI_State_Right;

extern Struct_Chassis_State Chassis_State;

/* 方向控制引脚 */
#define MOTOR_LEFT_DIRECTION_PORT GPIO_PORT_A
#define MOTOR_LEFT_DIRECTION_PIN GPIO_PIN_12
#define MOTOR_RIGHT_DIRECTION_PORT GPIO_PORT_B
#define MOTOR_RIGHT_DIRECTION_PIN GPIO_PIN_15
/* 编码器引脚 */
#define MOTOR_LEFT_QEI_PHASE_A_PORT GPIO_PORT_B
#define MOTOR_LEFT_QEI_PHASE_A_PIN GPIO_PIN_23
#define MOTOR_LEFT_QEI_PHASE_B_PORT GPIO_PORT_B
#define MOTOR_LEFT_QEI_PHASE_B_PIN GPIO_PIN_27
#define MOTOR_RIGHT_QEI_PHASE_A_PORT GPIO_PORT_B
#define MOTOR_RIGHT_QEI_PHASE_A_PIN GPIO_PIN_2
#define MOTOR_RIGHT_QEI_PHASE_B_PORT GPIO_PORT_B
#define MOTOR_RIGHT_QEI_PHASE_B_PIN GPIO_PIN_3

/* 底盘参数 */
#define CHASSIS_WHEEL_TRACK (110.0f)
#define CHASSIS_WHEEL_RADIUS (65.0f)
#define CHASSIS_WHEEL_QEI_SCALE (13.0f * 28.0f)
/* PID参数 */
#define CHASSIS_LEFT_PID_OMEGA_KP (500.0f)
#define CHASSIS_LEFT_PID_OMEGA_KI (0.0f)
#define CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX (1500.0f)
#define CHASSIS_LEFT_PID_OMEGA_OUT_MAX (750.0f)
#define CHASSIS_RIGHT_PID_OMEGA_KP (CHASSIS_LEFT_PID_OMEGA_KP)
#define CHASSIS_RIGHT_PID_OMEGA_KI (CHASSIS_LEFT_PID_OMEGA_KI)
#define CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX)
#define CHASSIS_RIGHT_PID_OMEGA_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_OUT_MAX)
/* 差速参数 */
#define DIFF_KP (0.0f)

/**
 * @brief 运动控制初始化
 */
void Motion_Init(void);

/**
 * @brief 运动控制任务
 */
void Motion_Task(void);

#endif /* TSK_MOTION_H */
