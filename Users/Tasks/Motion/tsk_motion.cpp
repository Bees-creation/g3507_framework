/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_motion.h"

Class_Differential_Chassis<Class_Brush_Motor_Drv8701e> chassis(CHASSIS_WHEEL_TRACK, CHASSIS_WHEEL_RADIUS);

void Motion_Init(void) {
    // PID初始化
    chassis.Left_Motor.Omega_Loop.Init(CHASSIS_LEFT_PID_OMEGA_KP, CHASSIS_LEFT_PID_OMEGA_KI, 0.0f, 0.0f, CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX, CHASSIS_LEFT_PID_OMEGA_OUT_MAX);
    chassis.Right_Motor.Omega_Loop.Init(CHASSIS_RIGHT_PID_OMEGA_KP, CHASSIS_RIGHT_PID_OMEGA_KI, 0.0f, 0.0f, CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX, CHASSIS_RIGHT_PID_OMEGA_OUT_MAX);
    // 编码器初始化
    chassis.Left_Motor.QEI.Init(0.01, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_AB, MOTOR_LEFT_QEI_PHASE_A_PORT, MOTOR_LEFT_QEI_PHASE_A_PIN, MOTOR_LEFT_QEI_PHASE_B_PORT, MOTOR_LEFT_QEI_PHASE_B_PIN);
    chassis.Right_Motor.QEI.Init(0.01, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_AB, MOTOR_RIGHT_QEI_PHASE_A_PORT, MOTOR_RIGHT_QEI_PHASE_A_PIN, MOTOR_RIGHT_QEI_PHASE_B_PORT, MOTOR_RIGHT_QEI_PHASE_B_PIN);
    // 电机初始化
    chassis.Left_Motor.Init((TIMER_INST*)TIMA0, TIMER_CHANNEL_0, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_LEFT_DIRECTION_PORT, MOTOR_LEFT_DIRECTION_PIN, MOTOR_LEFT_ENABLE_PORT, MOTOR_LEFT_ENABLE_PIN);
    chassis.Right_Motor.Init((TIMER_INST*)TIMA0, TIMER_CHANNEL_1, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_RIGHT_DIRECTION_PORT, MOTOR_RIGHT_DIRECTION_PIN, MOTOR_RIGHT_ENABLE_PORT, MOTOR_RIGHT_ENABLE_PIN);
}

void Motion_Task(void) {
    chassis.Set_Target_Velocity_Y(10);
    chassis.TIM_Update_PeriodElapsedCallback();
}

void GPIOA_PIN14_IRQHandler (void) {
    chassis.Left_Motor.QEI.GPIO_InterruptCallback();
}

void GPIOA_PIN16_IRQHandler (void) {
    chassis.Right_Motor.QEI.GPIO_InterruptCallback();
}
