/**
 * @brief 电机
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_MOTOR_H
#define DVC_MOTOR_H

#include "Drivers/GPIO/drv_gpio.h"
#include "Algorithm/PID/alg_pid.h"
#include "Algorithm/Filter/alg_filter.h"
#include "Device/Encoder/dvc_encoder.h"

enum Enum_Motor_Control_Method {
    Motor_Control_Method_Angle = 0,// 三环角度环控制
    Motor_Control_Method_Omega,// 双环速度环控制
    Motor_Control_Method_Torque,// 单环力矩环控制
};

enum Enum_Motor_Control_Algorithm {
    Motor_Control_Algorithm_PID = 0,// PID控制算法
};

enum Enum_Stepping_Motor_Control_Method {
    Stepping_Motor_Control_Method_Angle = 0,// 角度控制
    Stepping_Motor_Control_Method_Omega,// 速度控制
};

/**
 * @brief 电机基类
 * 
 * @note 从电机转轴方向看进去，旋转方向符合右手螺旋定则，即顺时针旋转为正向
 */
class Class_Motor {
public:
    Class_PID Angle_Loop;
    Class_PID Omega_Loop;
    Class_PID Torque_Loop;

    /**
     * @brief 进行一次速度计算
     */
    virtual void TIM_Calculate_PeriodElapsedCallback() = 0;

    /**
     * @brief 输出电机状态
     */
    virtual void TIM_Output_PeriodElapsedCallback() = 0;

    /**
     * @brief 更新电机状态
     */
    virtual void TIM_Feedback_PeriodElapsedCallback() = 0;

    /**
     * @brief 设定相对目标角度
     * 
     * @param __Relative_Target_Angle 相对目标角度
     */
    inline void Set_Relative_Target_Angle(const float &__Relative_Target_Angle) {
        Absolute_Target_Angle += __Relative_Target_Angle;
    }

    /**
     * @brief 设定绝对目标角度
     * 
     * @param __Absolute_Target_Angle 绝对目标角度
     */
    inline void Set_Absolute_Target_Angle(const float &__Absolute_Target_Angle) {
        Absolute_Target_Angle = __Absolute_Target_Angle;
    }

    /**
     * @brief 设定绝对目标角速度
     * 
     * @param __Absolute_Target_Omega 绝对目标角速度
     */
    inline void Set_Absolute_Target_Omega(const float &__Absolute_Target_Omega) {
        Absolute_Target_Omega = __Absolute_Target_Omega;
    }

    /**
     * @brief 设定绝对目标力矩
     * 
     * @param __Absolute_Target_Torque 绝对目标力矩
     */
    inline void Set_Absolute_Target_Torque(const float &__Absolute_Target_Torque) {
        Absolute_Target_Torque = __Absolute_Target_Torque;
    }

    /**
     * @brief 获取角度
     * 
     * @retval 角度
     */
    inline float Get_Angle(void) {
        return Now_Angle;
    }

    /**
     * @brief 获取角速度
     * 
     * @retval 角速度
     */
    inline float Get_Omega(void) {
        return Now_Omega;
    }

protected:
    // 控制方法
    Enum_Motor_Control_Method Control_Method = Motor_Control_Method_Omega;
    // 控制算法
    Enum_Motor_Control_Algorithm Control_Algorithm = Motor_Control_Algorithm_PID;

    // 更新周期
    float D_T;

    // 当前角度
    float Now_Angle = 0.0f;
    // 当前角速度
    float Now_Omega = 0.0f;
    // 当前力矩
    float Now_Torque = 0.0f;
    // 绝对目标角度
    float Absolute_Target_Angle = 0.0f;
    // 绝对目标角速度
    float Absolute_Target_Omega = 0.0f;
    // 绝对目标力矩
    float Absolute_Target_Torque = 0.0f;

    // 输出值
    float Out = 0.0f;
};

/**
 * @brief 使用drv8701e驱动芯片的有刷电机
 */
class Class_Brush_Motor_Drv8701e : public Class_Motor {
public:
    Class_Software_QEI QEI;

    /**
     * @brief 初始化函数
     * 
     * @param TIMx 绑定的定时器
     * @param __Channel 绑定的定时器通道
     * @param __Control_Method 控制方法
     * @param __Control_Algorithm 控制算法
     * @param __Direction_Port 方向引脚
     * @param __Direction_Pin 方向引脚
     * @param __D_T 更新周期
     * @param __Filter 滤波系数
     */
    void Init(TIMER_INST *TIMx, TIMER_CHANNEL __Channel, const Enum_Motor_Control_Method &__Control_Method, const Enum_Motor_Control_Algorithm &__Control_Algorithm, GPIO_PORT *__Direction_Port, GPIO_PIN __Direction_Pin, float __D_T, float __Filter = 0.5f);

    /**
     * @brief 启动电机
     */
    inline void Start_Motor(void) {
        TIM_Start_Counter(TIM);
    }

    /**
     * @brief 停用电机
     */
    inline void Stop_Motor(void) {
        TIM_Stop_Counter(TIM);
    }

    virtual void TIM_Calculate_PeriodElapsedCallback() override;

    virtual void TIM_Output_PeriodElapsedCallback() override;

    virtual void TIM_Feedback_PeriodElapsedCallback() override;

protected:
    // 绑定的定时器
    TIMER_INST *TIM = nullptr;
    // 绑定的定时器通道
    TIMER_CHANNEL Channel;
    // 方向控制引脚
    GPIO_PORT *Direction_Port;
    GPIO_PIN Direction_Pin;
    // 一次滤波系数
    float Filter = 0.5f;
};

/**
 * @brief 步进电机基类
 */
class Class_Stepping_Motor {
public:
    /**
     * @brief 进行一次速度计算
     */
    virtual void TIM_Calculate_PeriodElapsedCallback() = 0;

    /**
     * @brief 输出电机状态
     */
    virtual void TIM_Output_PeriodElapsedCallback() = 0;

    /**
     * @brief 更新电机状态
     */
    virtual void TIM_Feedback_PeriodElapsedCallback() = 0;

    /**
     * @brief 设定相对目标角度
     * 
     * @param __Relative_Target_Angle 相对目标角度
     */
    inline void Set_Relative_Target_Angle(const float &__Relative_Target_Angle) {
        Absolute_Target_Angle += __Relative_Target_Angle;
    }

    /**
     * @brief 设定绝对目标角度
     * 
     * @param __Absolute_Target_Angle 绝对目标角度
     */
    inline void Set_Absolute_Target_Angle(const float &__Absolute_Target_Angle) {
        Absolute_Target_Angle = __Absolute_Target_Angle;
    }

    /**
     * @brief 设定绝对目标角速度
     * 
     * @param __Absolute_Target_Omega 绝对目标角速度
     */
    inline void Set_Absolute_Target_Omega(const float &__Absolute_Target_Omega) {
        Absolute_Target_Omega = __Absolute_Target_Omega;
    }

    /**
     * @brief 获取角度
     * 
     * @retval 角度
     */
    inline float Get_Angle(void) {
        return Now_Angle;
    }

    /**
     * @brief 获取角速度
     * 
     * @retval 角速度
     */
    inline float Get_Omega(void) {
        return Now_Omega;
    }

protected:
    // 控制方法
    Enum_Stepping_Motor_Control_Method Control_Method = Stepping_Motor_Control_Method_Omega;

    // 更新周期
    float D_T;

    // 当前角度
    float Now_Angle = 0.0f;
    // 当前角速度
    float Now_Omega = 0.0f;
    // 绝对目标角度
    float Absolute_Target_Angle = 0.0f;
    // 绝对目标角速度
    float Absolute_Target_Omega = 0.0f;

    // 时钟频率
    uint32_t Frequency = (1000000);
    // 步进频率
    float Out = 0.0f;
    // 步进限幅
    float Min = (0.04f * PI);
    float Max = (8.0f * PI);

    // 每圈步数
    uint32_t Scale = 200;
    // 细分倍数
    uint8_t Division = 16;
    // 每rad步长
    float Step;
};

/**
 * @brief 使用D36A驱动芯片的步进电机
 * 
 * @note 只有位置控制和速度控制
 */
class Class_Stepping_Motor_D36A : public Class_Stepping_Motor {
public:
    /**
     * @brief 初始化函数
     * 
     * @param TIMx 绑定的定时器
     * @param __Channel 绑定的定时器通道
     * @param __Control_Method 控制方法
     * @param __Direction_Port 方向引脚
     * @param __Direction_Pin 方向引脚
     * @param __D_T 更新周期
     * @param __Frequency 时钟频率
     * @param __Min 步进限幅
     * @param __Max 步进限幅
     * @param __Scale 每圈步数
     * @param __Division 细分倍数
     */
    void Init(TIMER_INST *TIMx, TIMER_CHANNEL __Channel, const Enum_Stepping_Motor_Control_Method &__Control_Method, GPIO_PORT *__Direction_Port, GPIO_PIN __Direction_Pin, float __D_T, uint32_t __Frequency, float __Min, float __Max, uint32_t __Scale, uint8_t __Division);

    /**
     * @brief 启动电机
     */
    inline void Start_Motor(void) {
        TIM_Start_Counter(TIM);
    }

    /**
     * @brief 停止电机
     */
    inline void Stop_Motor(void) {
        TIM_Stop_Counter(TIM);
    }

    virtual void TIM_Calculate_PeriodElapsedCallback() override;

    virtual void TIM_Output_PeriodElapsedCallback() override;

    virtual void TIM_Feedback_PeriodElapsedCallback() override;

protected:
    // 绑定的定时器
    TIMER_INST *TIM = nullptr;
    // 绑定的定时器通道
    TIMER_CHANNEL Channel;
    // 方向控制引脚
    GPIO_PORT *Direction_Port;
    GPIO_PIN Direction_Pin;
};

#endif /* DVC_MOTOR_H */
