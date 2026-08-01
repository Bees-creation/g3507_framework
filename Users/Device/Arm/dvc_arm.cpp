/**
 * @brief 特殊执行机构
 * @date 2026/7/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "Device/Arm/dvc_arm.h"

void Class_Screw_Lift::TIM_Update_PeriodElapsedCallback() {
    Kinematics_Forward_Resolution();
    Kinematics_Inverse_Resolution();
    Stepping_Motor.TIM_Feedback_PeriodElapsedCallback();
    Stepping_Motor.TIM_Calculate_PeriodElapsedCallback();
    Stepping_Motor.TIM_Output_PeriodElapsedCallback();
}

void Class_Screw_Lift::Kinematics_Forward_Resolution(void) {
    float omega = Stepping_Motor.Get_Omega();

    /* 螺纹丝杆的运动学正解算 */
    if (Screw_Direction == Screw_Direction_Left) {
        Now_Velocity = Lead * omega;
    }
    else {
        Now_Velocity = -Lead * omega;
    }
}

void Class_Screw_Lift::Kinematics_Inverse_Resolution(void) {
    float omega;

    if (Control_Mode == Control_Angle) {
        /* 角度控制：P 控制将角度误差映射为角速度 */
        omega = (Target_Angle - Stepping_Motor.Get_Angle()) * Angle_Kp;
    }
    else {
        /* 速度控制：将丝杆线速度转换为电机角速度 */
        omega = Target_Velocity / Lead;
    }

    // 角度限位：禁止超限方向运动，允许反向退回
    float angle = Stepping_Motor.Get_Angle();
    if ((angle <= Angle_Min && omega < 0.0f)
     || (angle >= Angle_Max && omega > 0.0f)) {
        omega = 0.0f;
    }

    Stepping_Motor.Set_Absolute_Target_Omega(omega);
}

/**
 * Class_Balance_Arm 平衡球装置
 *
 * 串级 PID 控制
 *  目标位置 -> 位置环 -> 目标小球速度 -> 速度环 -> 丝杆上升速度
 *       ^                        ^
 *  当前小球位置              当前小球速度
 */

void Class_Balance_Arm::TIM_Update_PeriodElapsedCallback() {
    // 位置环 PID 计算
    Position_PID.Set_Target(Target_Position);
    Position_PID.Set_Now(Now_Position);
    Position_PID.TIM_Calculate_PeriodElapsedCallback();

    // 速度环 PID 计算
    Velocity_PID.Set_Target(Position_PID.Get_Out());
    Velocity_PID.Set_Now(Now_Velocity);
    Velocity_PID.TIM_Calculate_PeriodElapsedCallback();

    // 输出丝杆上升速度
    Up_Velocity = Velocity_PID.Get_Out();

    // 更新丝杆输出状态
    Screw_Lift.Set_Target_Velocity(Up_Velocity);
    Screw_Lift.TIM_Update_PeriodElapsedCallback();
}
