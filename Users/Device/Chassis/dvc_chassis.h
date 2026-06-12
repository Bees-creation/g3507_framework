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
     * @brief 设定目标逆时针旋转速度
     * 
     * @param __Target_Omega 目标逆时针旋转速度
     */
    inline void Set_Target_Omega(float __Target_Omega) {
        Target_Omega = __Target_Omega;
    }

    /**
     * @brief 获取当前右行速度
     * 
     * @retval Now_Velocity_X 当前右行速度
     */
    inline float Get_Now_Velocity_X(void) {
        return Now_Velocity_X;
    }

    /**
     * @brief 获取当前前进速度
     * 
     * @retval Now_Velocity_Y 当前前进速度
     */
    inline float Get_Now_Velocity_Y(void) {
        return Now_Velocity_Y;
    }

    /**
     * @brief 获取当前逆时针旋转速度
     * 
     * @retval Now_Omega 当前逆时针旋转速度
     */
    inline float Get_Now_Omega(void) {
        return Now_Omega;
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
class Class_Differential_Chassis:public Class_Chassis {
public:
    Class_Motor &Left_Motor;
    Class_Motor &Right_Motor;

    Class_Differential_Chassis(Class_Motor &__Left_Motor, Class_Motor &__Right_Motor, float __Wheel_Track, float __Wheel_Radius)
    : Left_Motor(__Left_Motor), Right_Motor(__Right_Motor), Wheel_Track(__Wheel_Track), Wheel_Radius(__Wheel_Radius) {
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

#endif /* DVC_CHASSIS_H */
