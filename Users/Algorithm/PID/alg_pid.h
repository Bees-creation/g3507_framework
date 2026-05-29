/**
 * @brief PID算法
 * @date 2026/5/25
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright USTC-RoboWalker (c) 2023
 */

#ifndef ALG_PID_H
#define ALG_PID_H

#include "ti_msp_dl_config.h"

#include "Algorithm/Math/alg_math.h"

class Class_PID {
public:
    /**
     * @brief PID初始化
     * 
     * @param PID参数
     */
    void Init(const float &__K_P, const float &__K_I, const float &__K_D, const float &__K_F = 0.0f, const float &__I_Out_Max = 0.0f, const float &__Out_Max = 0.0f, const float &__D_T = 0.001f, const float &__Dead_Zone = 0.0f, const float &__I_Variable_Speed_A = 0.0f, const float &__I_Variable_Speed_B = 0.0f, const float &__I_Separate_Threshold = 0.0f);

    /**
     * @brief 获取误差积分值
     * 
     * @retval 误差积分值
     */
    inline float Get_Integral_Error() const;

    /**
     * @brief 获取输出值
     * 
     * @retval 输出值
     */
    inline float Get_Out() const;

    /**
     * @brief 设定比例系数
     * 
     * @param __K_P 比例系数
     */
    inline void Set_K_P(const float &__K_P);

    /**
     * @brief 设定积分系数
     * 
     * @param __K_I 积分系数
     */
    inline void Set_K_I(const float &__K_I);

    /**
     * @brief 设定微分系数
     * 
     * @param __K_D 微分系数
     */
    inline void Set_K_D(const float &__K_D);

    /**
     * @brief 设定前馈系数
     * 
     * @param __K_F 前馈系数
     */
    inline void Set_K_F(const float &__K_F);

    /**
     * @brief 设定积分限幅
     * 
     * @param __I_Out_Max 积分限幅
     */
    inline void Set_I_Out_Max(const float &__I_Out_Max);


    /**
     * @brief 设定输出限幅
     * 
     * @param __Out_Max 输出限幅
     */
    inline void Set_Out_Max(const float &__Out_Max);

    /**
     * @brief 设定变速积分全速阈值
     * 
     * @param __I_Variable_Speed_A 变速积分全速阈值
     */
    inline void Set_I_Variable_Speed_A(const float &__I_Variable_Speed_A);

    /**
     * @brief 设定变速积分启动阈值
     * 
     * @param __I_Variable_Speed_B 变速积分启动阈值
     */
    inline void Set_I_Variable_Speed_B(const float &__I_Variable_Speed_B);

    /**
     * @brief 设定积分分离阈值
     * 
     * @param __I_Separate_Threshold 积分分离阈值
     */
    inline void Set_I_Separate_Threshold(const float &__I_Separate_Threshold);

    /**
     * @brief 设定目标值
     * 
     * @param __Target 目标值
     */
    inline void Set_Target(const float &__Target);

    /**
     * @brief 设定当前值
     * 
     * @param __Now 当前值
     */
    inline void Set_Now(const float &__Now);

    /**
     * @brief 设定误差积分值
     * 
     * @param __Integral_Error 误差积分值
     */
    inline void Set_Integral_Error(const float &__Integral_Error);

    /**
     * @brief 进行一次PID计算，并将结果输出到Out，以D_T作为时间间隔
     */
    void TIM_Calculate_PeriodElapsedCallback();

protected:
    /* 初始化相关常量 */

    // PID计时器周期，以s为单位
    float D_T;
    // 死区，Error在其绝对值内不输出
    float Dead_Zone;

    /* 内部变量 */

    // 上一次的当前值
    float Pre_Now = 0.0f;
    // 上一次的目标值
    float Pre_Target = 0.0f;
    // 上一次的输出值
    float Pre_Out = 0.0f;
    // 上一次的误差值
    float Pre_Error = 0.0f;

    /* 读变量 */

    // 输出值
    float Out = 0.0f;

    /* 写变量 */

    // 比例系数
    float K_P = 0.0f;
    // 积分系数
    float K_I = 0.0f;
    // 微分系数
    float K_D = 0.0f;
    // 前馈系数
    float K_F = 0.0f;

    // 积分限幅，0为不限制
    float I_Out_Max = 0;
    // 输出限幅，0为不限制
    float Out_Max = 0;

    // 变速积分全速阈值，0为不限制
    float I_Variable_Speed_A = 0.0f;
    // 变速积分启动阈值，0为不限制
    float I_Variable_Speed_B = 0.0f;
    // 积分分离阈值，需为正数，0为不限制
    float I_Separate_Threshold = 0.0f;

    // 目标值
    float Target = 0.0f;
    // 当前值
    float Now = 0.0f;

    /* 读写变量 */

    // 积分值
    float Integral_Error = 0.0f;
};

#endif /* ALG_PID_H */

/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/