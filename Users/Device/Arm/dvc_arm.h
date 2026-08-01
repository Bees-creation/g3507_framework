/**
 * @brief 特殊执行机构
 * @date 2026/7/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_ARM_H
#define DVC_ARM_H

#include "Device/Motor/dvc_motor.h"
#include "Algorithm/PID/alg_pid.h"

/**
 * @brief 螺纹杆进动方向
 *
 * @param Screw_Direction_Left 顺时针旋转为抬升
 * @param Screw_Direction_Right 逆时针旋转为抬升
 */
enum Enum_Screw_Direction {
    Screw_Direction_Left = 0,
    Screw_Direction_Right,
};

/**
 * @brief 丝杆控制模式
 *
 * @param Control_Velocity 速度控制：直接设定丝杆上升速度
 * @param Control_Angle 角度控制：设定目标角度，内部 P 控制跟踪
 */
enum Enum_Screw_Control_Mode {
    Control_Velocity = 0,
    Control_Angle,
};

/**
 * @brief 螺纹丝杆抬升机构
 *
 * @note 单轴运动方向，旋转遵循手性定则
 */
class Class_Screw_Lift {
public:
    Class_Stepping_Motor& Stepping_Motor;

    Class_Screw_Lift(Class_Stepping_Motor &__Stepping_Motor, float __Lead)
    : Stepping_Motor(__Stepping_Motor), Lead(__Lead) {
    }

    /**
     * @brief 进行一次运动学解算，更新电机输出
     */
    virtual void TIM_Update_PeriodElapsedCallback();

    /**
     * @brief 设定控制模式
     *
     * @param __Mode 速度控制或角度控制
     */
    inline void Set_Control_Mode(Enum_Screw_Control_Mode __Mode) {
        Control_Mode = __Mode;
    }

    /**
     * @brief 设定目标上升速度（速度控制模式）
     *
     * @param __Target_Velocity 目标上升速度
     */
    inline void Set_Target_Velocity(float __Target_Velocity) {
        Target_Velocity = __Target_Velocity;
    }

    /**
     * @brief 设定目标角度（角度控制模式）
     *
     * @param __Target_Angle 目标电机角度
     */
    inline void Set_Target_Angle(float __Target_Angle) {
        Target_Angle = Math_Constrain(__Target_Angle, Angle_Min, Angle_Max);
    }

    /**
     * @brief 设定角度环 P 增益
     *
     * @param __Angle_Kp 角度误差到角速度的比例系数
     */
    inline void Set_Angle_Kp(float __Angle_Kp) {
        Angle_Kp = __Angle_Kp;
    }

    /**
     * @brief 设定电机角度限位
     *
     * @param __Min 最小角度 (rad)
     * @param __Max 最大角度 (rad)
     */
    inline void Set_Angle_Limit(float __Min, float __Max) {
        Angle_Min = __Min;
        Angle_Max = __Max;
    }

    /**
     * @brief 获取当前上升速度
     *
     * @retval Now_Velocity 当前上升速度
     */
    inline float Get_Now_Velocity(void) {
        return Now_Velocity;
    }

protected:
    Enum_Screw_Direction Screw_Direction = Screw_Direction_Left;

    // 控制模式
    Enum_Screw_Control_Mode Control_Mode = Control_Velocity;

    // 读变量
    float Target_Velocity = 0.0f;
    float Now_Velocity = 0.0f;

    // 导程
    float Lead;

    // 角度控制
    float Target_Angle = 0.0f;
    float Angle_Kp = 5.0f;

    // 电机角度限位
    float Angle_Min = -10.0f;
    float Angle_Max = 10.0f;

    /* 内部函数 */
    virtual void Kinematics_Forward_Resolution(void);
    virtual void Kinematics_Inverse_Resolution(void);
};

/**
 * @brief 平衡球装置
 *
 * 串级 PID 控制
 *  目标位置 -> [位置环 PID] -> 目标速度 -> [速度环 PID] -> 丝杆速度 -> 步进电机
 *                  ^                            ^
 *             当前小球位置                  当前小球速度
 */
class Class_Balance_Arm {
public:
    Class_Screw_Lift& Screw_Lift;

    // 串级 PID 控制器
    Class_PID Position_PID; // 位置环 -> 目标小球速度
    Class_PID Velocity_PID; // 速度环 -> 丝杆上升速度

    Class_Balance_Arm(Class_Screw_Lift &__Screw_Lift)
    : Screw_Lift(__Screw_Lift) {
    }

    /**
     * @brief 设定小球目标位置
     *
     * @param __Target_Position 目标位置
     */
    inline void Set_Target_Position(float __Target_Position) {
        Target_Position = __Target_Position;
    }

    /**
     * @brief 从视觉系统更新小球状态
     *
     * @param __Now_Position 当前小球位置
     * @param __Now_Velocity 当前小球速度
     */
    inline void Set_Now_State(float __Now_Position, float __Now_Velocity) {
        Now_Position = __Now_Position;
        Now_Velocity = __Now_Velocity;
    }

    /**
     * @brief 获取当前目标位置
     *
     * @retval Target_Position 目标位置
     */
    inline float Get_Target_Position(void) {
        return Target_Position;
    }

    /**
     * @brief 获取当前小球位置
     *
     * @retval Now_Position 当前小球位置
     */
    inline float Get_Now_Position(void) {
        return Now_Position;
    }

    /**
     * @brief 获取丝杆上升速度
     *
     * @retval Up_Velocity 丝杆上升速度
     */
    inline float Get_Up_Velocity(void) {
        return Up_Velocity;
    }

    /**
     * @brief 进行一次控制周期更新
     *
     * @note 应在定时器中断中按固定周期调用
     */
    virtual void TIM_Update_PeriodElapsedCallback();

protected:
    // 平衡球状态
    float Target_Position = 0.0f;
    float Now_Position = 0.0f;
    float Now_Velocity = 0.0f;

    // 丝杆速度
    float Up_Velocity = 0.0f;
};

#endif /* DVC_ARM_H */
