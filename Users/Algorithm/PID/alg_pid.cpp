/**
 * @brief PID算法
 * @date 2026/5/25
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright USTC-RoboWalker (c) 2023
 */

#include "alg_pid.h"

void Class_PID::Init(const float &__K_P, const float &__K_I, const float &__K_D, const float &__K_F, const float &__I_Out_Max, const float &__Out_Max, const float &__D_T, const float &__Dead_Zone, const float &__I_Variable_Speed_A, const float &__I_Variable_Speed_B, const float &__I_Separate_Threshold) {
    K_P = __K_P;
    K_I = __K_I;
    K_D = __K_D;
    K_F = __K_F;
    I_Out_Max = __I_Out_Max;
    Out_Max = __Out_Max;
    D_T = __D_T;
    Dead_Zone = __Dead_Zone;
    I_Variable_Speed_A = __I_Variable_Speed_A;
    I_Variable_Speed_B = __I_Variable_Speed_B;
    I_Separate_Threshold = __I_Separate_Threshold;
}

void Class_PID::TIM_Calculate_PeriodElapsedCallback() {
    // P输出
    float p_out = 0.0f;
    // I输出
    float i_out = 0.0f;
    // D输出
    float d_out = 0.0f;
    // F输出
    float f_out = 0.0f;
    // 误差
    float error;
    // 绝对值误差
    float abs_error;
    // 线性变速积分
    float speed_ratio;

    error = Target - Now;
    abs_error = Math_Abs(error);

    // 判断死区
    if (abs_error < Dead_Zone) {
        Target = Now;
        error = 0.0f;
        abs_error = 0.0f;
    }
    else if (error > 0.0f && abs_error > Dead_Zone) {
        error -= Dead_Zone;
    }
    else if (error < 0.0f && abs_error > Dead_Zone) {
        error += Dead_Zone;
    }

    // 计算p项

    p_out = K_P * error;

    // 计算i项

    if (I_Variable_Speed_A == 0.0f && I_Variable_Speed_B == 0.0f) {
        // 非变速积分
        speed_ratio = 1.0f;
    }
    else {
        // 变速积分
        if (abs_error <= I_Variable_Speed_A) {
            speed_ratio = 1.0f;
        }
        else if (I_Variable_Speed_A < abs_error && abs_error < I_Variable_Speed_B) {
            speed_ratio = (I_Variable_Speed_B - abs_error) / (I_Variable_Speed_B - I_Variable_Speed_A);
        }
        else if (abs_error >= I_Variable_Speed_B) {
            speed_ratio = 0.0f;
        }
    }
    // 积分限幅
    if (I_Out_Max != 0.0f && K_I != 0.0f) {
        Math_Constrain(&Integral_Error, -I_Out_Max / K_I, I_Out_Max / K_I);
    }
    if (I_Separate_Threshold == 0.0f) {
        // 没有积分分离
        Integral_Error += speed_ratio * D_T * error;
        i_out = K_I * Integral_Error;
    }
    else {
        // 有积分分离
        if (abs_error < I_Separate_Threshold) {
            // 不在积分分离区间上
            Integral_Error += speed_ratio * D_T * error;
            i_out = K_I * Integral_Error;
        }
        else {
            // 在积分分离区间上
            Integral_Error = 0.0f;
            i_out = 0.0f;
        }
    }

    // 计算d项

    d_out = K_D * (error - Pre_Error) / D_T;

    // 计算前馈

    f_out = K_F * (Target - Pre_Target);

    // 计算输出

    Out = p_out + i_out + d_out + f_out;

    // 输出限幅
    if (Out_Max != 0.0f) {
        Math_Constrain(&Out, -Out_Max, Out_Max);
    }

    // 善后工作
    Pre_Now = Now;
    Pre_Target = Target;
    Pre_Out = Out;
    Pre_Error = error;
}

/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/