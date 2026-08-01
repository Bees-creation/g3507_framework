/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_MOTION_H
#define TSK_MOTION_H

#include "Device/Chassis/dvc_chassis.h"
#include "Device/Arm/dvc_arm.h"

/**
 * @brief 上位机视觉数据
 * 
 * @param x 上位机 x 值
 */
typedef struct Struct_Visual_State {
    float x;
    float v;
} Struct_Visual_State;

extern Struct_Visual_State Visual_State;

extern Class_Differential_Chassis Chassis;

extern Class_Balance_Arm Balance_Arm;

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
#define CHASSIS_WHEEL_TRACK (209.0f) // 小型板是 (114.0f)
#define CHASSIS_WHEEL_RADIUS (33.0f)
#define CHASSIS_WHEEL_QEI_SCALE (13.0f * 28.0f)
/* 底盘 PID 参数 */
#define CHASSIS_LEFT_PID_OMEGA_KP (120.0f)
#define CHASSIS_LEFT_PID_OMEGA_KI (10.0f)
#define CHASSIS_LEFT_PID_OMEGA_KD (0.0f)
#define CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX (500.0f)
#define CHASSIS_LEFT_PID_OMEGA_OUT_MAX (750.0f)
#define CHASSIS_RIGHT_PID_OMEGA_KP (CHASSIS_LEFT_PID_OMEGA_KP)
#define CHASSIS_RIGHT_PID_OMEGA_KI (CHASSIS_LEFT_PID_OMEGA_KI)
#define CHASSIS_RIGHT_PID_OMEGA_KD (CHASSIS_LEFT_PID_OMEGA_KD)
#define CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX)
#define CHASSIS_RIGHT_PID_OMEGA_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_OUT_MAX)
/* 差速参数 */
#define DIFF_KP (0.15f)
#define TURN_KP (0.0f)
/* 时间片 */
#define DELTA_TIME (0.01f)
/* 滤波系数 */
#define FILTER (0.75f)

/* 步进电机参数 */
#define STEPPING_MOTOR_DIRECTION_PORT (GPIO_PORT_A)
#define STEPPING_MOTOR_DIRECTION_PIN (GPIO_PIN_15)
#define STEPPING_MOTOR_CLOCK_FREQ (1000000)
#define STEPPING_MOTOR_MIN_OMEGA (0.04f * PI)
#define STEPPING_MOTOR_MAX_OMEGA (0.4f * PI)
#define STEPPING_MOTOR_SCALE (200)
#define STEPPING_MOTOR_DIVISION (16)

/* 螺纹丝杆参数 */
#define SCREW_LEAD 1.0f
/* 丝杆角度限位 (rad) */
#define SCREW_ANGLE_MIN (-0.02f * PI)
#define SCREW_ANGLE_MAX (0.02f * PI)
/* 丝杆角度控制 */
#define SCREW_CONTROL_MODE Control_Velocity  // Control_Velocity 或 Control_Angle
#define SCREW_ANGLE_KP       (10.0f)         // 角度环 P 增益，内环带宽需远大于外环

/* 平衡球装置 PID 参数 */
// 位置环（位置误差 → 小球目标速度）
#define BALANCE_POSITION_PID_KP (0.2f)
#define BALANCE_POSITION_PID_KI (0.0f)
#define BALANCE_POSITION_PID_KD (0.01f)        // 速度阻尼
#define BALANCE_POSITION_PID_DEAD_ZONE (5.0f)  // 位置死区 (mm)
#define BALANCE_POSITION_PID_I_OUT_MAX (0.0f)
#define BALANCE_POSITION_PID_OUT_MAX (50.0f)
// 速度环（速度误差 → 丝杆速度）
#define BALANCE_VELOCITY_PID_KP (0.1f)
#define BALANCE_VELOCITY_PID_KI (0.0f)
#define BALANCE_VELOCITY_PID_KD (0.0f)
#define BALANCE_VELOCITY_PID_DEAD_ZONE (0.0f)
#define BALANCE_VELOCITY_PID_I_OUT_MAX (0.0f)
#define BALANCE_VELOCITY_PID_OUT_MAX (0.4f * PI)

/**
 * @brief 巡迹初始化
 */
void Motion_Init(void);

/**
 * @brief 巡迹控制
 * 
 * @param speed 前进速度
 * @retval STATUS_BUSY 未完成行驶
 *         STATUS_DONE 已完成行驶
 */
uint8_t Motion_Trace(float speed);

/**
 * @brief 运动停止
 */
void Motion_Stop(void);

/**
 * @brief 设定目标位置
 * @param target 目标位置
 */
void Visual_Set_Target(float target);

/**
 * @brief 视觉跟踪
 * @retval STATUS_BUSY 未完成跟踪
 *         STATUS_DONE 已完成跟踪
 */
uint8_t Visual_Trace(void);

/**
 * @brief 运动控制初始化
 */
void Motion_Init(void);

/**
 * @brief 运动控制任务
 */
void Motion_Task(void);

#endif /* TSK_MOTION_H */
