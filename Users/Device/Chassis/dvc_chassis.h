/**
 * @brief 底盘
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_CHASSIS_H
#define DVC_CHASSIS_H

#include "Device/Motor/dvc_motor.h"

/**
 * @brief 底盘基类
 * 
 * @note 规定东北天坐标系，旋转遵循右手定则，单位rad、mm、s
 */
class Class_Chassis {
public:
    /**
     * @brief 进行一次运动学解算，更新底盘状态
     */
    virtual void TIM_Update_PeriodElapsedCallback() = 0;

    /**
     * @brief 设定目标右行速度
     * 
     * @param __Target_Velocity_X 目标右行速度
     */
    inline void Set_Target_Velocity_X(float __Target_Velocity_X) {
        Target_Velocity_X = __Target_Velocity_X;
    }

    /**
     * @brief 设定目标前进速度
     * 
     * @param __Target_Velocity_Y 目标前进速度
     */
    inline void Set_Target_Velocity_Y(float __Target_Velocity_Y) {
        Target_Velocity_Y = __Target_Velocity_Y;
    }

    /**
     * @brief 设定逆时针旋转速度
     * 
     * @param __Target_Omega 逆时针旋转速度
     */
    inline void Set_Target_Omega(float __Target_Omega) {
        Target_Omega = __Target_Omega;
    }

protected:
    // 读变量
    float Now_Velocity_X = 0.0f;
    float Now_Velocity_Y = 0.0f;
    float Now_Omega = 0.0f;

    // 写变量
    float Target_Velocity_X = 0.0f;
    float Target_Velocity_Y = 0.0f;
    float Target_Omega = 0.0f;

    /* 内部函数 */
    virtual void Kinematics_Forward_Resolution(void) = 0;
    virtual void Kinematics_Inverse_Resolution(void) = 0;
};

/**
 * @brief 差速底盘
 * 
 * @tparam Motor 电机类
 */
template <class Motor>
class Class_Differential_Chassis:public Class_Chassis {
    // Motor必须是由Class_Motor基类派生得到的类型
    static_assert(std::is_base_of<Class_Motor, Motor>::value, "Motor must derive from Class_Motor");
public:
    Motor Left_Motor;
    Motor Right_Motor;

    Class_Differential_Chassis(float __Wheel_Track, float __Wheel_Radius)
    : Wheel_Track(__Wheel_Track), Wheel_Radius(__Wheel_Radius) {
    }

    virtual void TIM_Update_PeriodElapsedCallback() override;

protected:
    virtual void Kinematics_Forward_Resolution(void) override;
    virtual void Kinematics_Inverse_Resolution(void) override;

    // 轮距
    float Wheel_Track;
    // 轮半径
    float Wheel_Radius;
};

template <class Motor>
void Class_Differential_Chassis<Motor>::TIM_Update_PeriodElapsedCallback() {
    Kinematics_Forward_Resolution();
    Kinematics_Inverse_Resolution();
    Left_Motor.TIM_Feedback_PeriodElapsedCallback();
    Right_Motor.TIM_Feedback_PeriodElapsedCallback();
    Left_Motor.TIM_Calculate_PeriodElapsedCallback();
    Right_Motor.TIM_Calculate_PeriodElapsedCallback();
    Left_Motor.TIM_Output_PeriodElapsedCallback();
    Right_Motor.TIM_Output_PeriodElapsedCallback();
}

template <class Motor>
void Class_Differential_Chassis<Motor>::Kinematics_Forward_Resolution(void) {
    float left = Left_Motor.Get_Omega();
    float right = Right_Motor.Get_Omega();

    /* 差速底盘的运动学正解算 */
    Now_Velocity_X = 0;
    Now_Velocity_Y = (left - right) / 2.0f * Wheel_Radius;
    Now_Omega = (left + right) * Wheel_Radius / Wheel_Track;
}

template <class Motor>
void Class_Differential_Chassis<Motor>::Kinematics_Inverse_Resolution(void) {
    /* 差速底盘的运动学逆解算 */
    float left = Target_Velocity_Y / Wheel_Radius + Target_Omega * Wheel_Track / Wheel_Radius / 2.0f;
    float right = -Target_Velocity_Y / Wheel_Radius + Target_Omega * Wheel_Track / Wheel_Radius / 2.0f;
    
    Left_Motor.Set_Absolute_Target_Omega(left);
    Right_Motor.Set_Absolute_Target_Omega(right);
}

#endif /* DVC_CHASSIS_H */
