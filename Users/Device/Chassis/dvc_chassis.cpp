/**
 * @brief 底盘
 * @date 2026/6/9
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_chassis.h"

void Class_Differential_Chassis::TIM_Update_PeriodElapsedCallback() {
    Kinematics_Forward_Resolution();
    Kinematics_Inverse_Resolution();
    Left_Motor.TIM_Feedback_PeriodElapsedCallback();
    Right_Motor.TIM_Feedback_PeriodElapsedCallback();
    Left_Motor.TIM_Calculate_PeriodElapsedCallback();
    Right_Motor.TIM_Calculate_PeriodElapsedCallback();
    Left_Motor.TIM_Output_PeriodElapsedCallback();
    Right_Motor.TIM_Output_PeriodElapsedCallback();
}

void Class_Differential_Chassis::Kinematics_Forward_Resolution(void) {
    float left = Left_Motor.Get_Omega();
    float right = Right_Motor.Get_Omega();

    /* 差速底盘的运动学正解算 */
    Now_Velocity_X = 0;
    Now_Velocity_Y = (left - right) / 2.0f * Wheel_Radius;
    Now_Omega = (left + right) * Wheel_Radius / Wheel_Track;
}

void Class_Differential_Chassis::Kinematics_Inverse_Resolution(void) {
    /* 差速底盘的运动学逆解算 */
    float left = Target_Velocity_Y / Wheel_Radius + Target_Omega * Wheel_Track / Wheel_Radius / 2.0f;
    float right = -Target_Velocity_Y / Wheel_Radius + Target_Omega * Wheel_Track / Wheel_Radius / 2.0f;
    
    Left_Motor.Set_Absolute_Target_Omega(left);
    Right_Motor.Set_Absolute_Target_Omega(right);
}
