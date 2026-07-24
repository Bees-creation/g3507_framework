/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_MOTION_H
#define TSK_MOTION_H

#include "Device/Chassis/dvc_chassis.h"

/**
 * @brief 电机速度调试数据
 * 
 * @param target_angle 目标角度
 * @param now_angle 当前角度
 * @param target_omega 目标角速度
 * @param now_omega 当前角速度
 */
typedef struct Struct_Motor_State {
    float target_angle;
    float now_angle;
    float target_omega;
    float now_omega;
} Struct_Motor_State;

/**
 * @brief 底盘速度调试数据
 * 
 * @param target_distance 目标前进距离
 * @param now_distance 当前前进距离
 * @param target_speed 目标前进速度
 * @param now_speed 当前前进速度
 * @param target_omega 目标旋转速度
 * @param now_omega 当前旋转速度
 */
typedef struct Struct_Chassis_State {
    float target_distance;
    float now_distance;
    float target_speed;
    float now_speed;
    float target_omega;
    float now_omega;
} Struct_Chassis_State;

/**
 * @brief 转向记录器
 * 
 * @param Turns 转向数
 * @param Rounds 圈数
 */
typedef struct Struct_Trace_State {
    uint8_t Turns;
    uint8_t Rounds;

    /**
     * @brief 清空计数器
     */
    void Clear(void) {
        Turns = 0;
        Rounds = 0;
    }

    /**
     * @brief 记录转向
     * 
     * @param rounds 目标圈数
     * @retval 是否完成目标圈数
     */
    bool Turn(uint8_t rounds) {
        Turns++;
        if (Turns >= 4) {
            Rounds++;
        }
        if (Rounds >= rounds) {
            Clear();
            return STATUS_DONE;
        }
        return STATUS_BUSY;
    }
} Struct_Trace_State;

/**
 * @brief 上位机视觉数据
 * 
 * @param flag 上位机 flag 值
 * @param x 上位机 x 值
 * @param y 上位机 y 值
 */
typedef struct Struct_Visual_State {
    uint8_t flag;
    float x;
    float y;
} Struct_Visual_State;

extern Struct_Motor_State Motor_State_Left;
extern Struct_Motor_State Motor_State_Right;

extern Struct_Chassis_State Chassis_State;

extern Struct_Trace_State Trace_State;
extern Struct_Visual_State Visual_State;

extern Class_Differential_Chassis chassis;

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
/* PID参数 */
#define CHASSIS_LEFT_PID_OMEGA_KP (100.0f)
#define CHASSIS_LEFT_PID_OMEGA_KI (40.0f)
#define CHASSIS_LEFT_PID_OMEGA_KD (0.0f)
#define CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX (500.0f)
#define CHASSIS_LEFT_PID_OMEGA_OUT_MAX (750.0f)
#define CHASSIS_RIGHT_PID_OMEGA_KP (CHASSIS_LEFT_PID_OMEGA_KP)
#define CHASSIS_RIGHT_PID_OMEGA_KI (CHASSIS_LEFT_PID_OMEGA_KI)
#define CHASSIS_RIGHT_PID_OMEGA_KD (CHASSIS_LEFT_PID_OMEGA_KD)
#define CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX)
#define CHASSIS_RIGHT_PID_OMEGA_OUT_MAX (CHASSIS_LEFT_PID_OMEGA_OUT_MAX)
/* 差速参数 */
#define DIFF_KP (0.1f)
#define TURN_KP (0.0f)
/* 时间片 */
#define DELTA_TIME (0.01f)
/* 滤波系数 */
#define FILTER (0.75f)

/**
 * @brief 默认巡迹控制
 * 
 * @param speed 前进速度
 * @retval STATUS_BUSY 未完成行驶
 *         STATUS_DONE 已完成行驶
 */
uint8_t Motion_Trace(float speed, uint8_t rounds);

/**
 * @brief 运动停止
 */
void Motion_Stop(void);

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
