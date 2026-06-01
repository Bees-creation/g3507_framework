/**
 * @brief 编码器
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_ENCODER_H
#define DVC_ENCODER_H

#include "Drivers/BSP/drv_bsp.h"
#include "Algorithm/Math/alg_math.h"

/**
 * @brief 编码器基类
 */
class Class_Encoder {
public:
    /**
     * @brief 编码器初始化
     * 
     * @param __D_T 时间间隔
     * @param __Scale 每圈的刻度
     */
    void Init(const float &__D_T, const float &__Scale);
    
    void TIM_Update_PeriodElapsedCallback();

    inline float Get_Angle(void) {
        return Angle;
    }

    inline float Get_Omega(void) {
        return Omega;
    }

protected:
    // 时间间隔
    float D_T;
    // 每rad的刻度
    float Scale;

    // 刻度值
    uint32_t Count;
    // 角度
    float Angle;
    // 角速度
    float Omega;
};

enum Enum_Software_Encoder_Count_Method {
    Encoder_Count_Method_A_UP_AB = 0,// A相上升沿中断，A相超前于B相为正向
    Encoder_Count_Method_A_UP_BA,// A相上升沿中断，B相超前于A相为正向
    Encoder_Count_Method_A_DOWN_AB,// A相下降沿中断，A相超前于B相为正向
    Encoder_Count_Method_A_DOWN_BA,// A相下降沿中断，B相超前于A相为正向
    Encoder_Count_Method_B_UP_AB,// B相上升沿中断，A相超前于B相为正向
    Encoder_Count_Method_B_UP_BA,// B相上升沿中断，B相超前于A相为正向
    Encoder_Count_Method_B_DOWN_AB,// B相下降沿中断，A相超前于B相为正向
    Encoder_Count_Method_B_DOWN_BA,// B相下降沿中断，B相超前于A相为正向
};

/**
 * @brief 软件正交编码器
 */
class Class_Software_QEI:public Class_Encoder {
public:
    /**
     * @brief 编码器初始化
     * 
     * @param __D_T 时间间隔
     * @param __Scale 每圈的刻度
     * @param Phase_A_Port A相引脚
     * @param Phase_A_Pin A相引脚
     * @param Phase_B_Port B相引脚
     * @param Phase_B_Pin B相引脚
     */
    void Init(const float &__D_T, const float &__Scale, const Enum_Software_Encoder_Count_Method &__Encoder_Count_Method, GPIO_PORT *__Phase_A_Port, GPIO_PIN __Phase_A_Pin, GPIO_PORT *__Phase_B_Port, GPIO_PIN __Phase_B_Pin);

    /**
     * @brief GPIO中断回调函数
     */
    void GPIO_InterruptCallback();

protected:
    Enum_Software_Encoder_Count_Method Encoder_Count_Method;

    GPIO_PORT *Phase_A_Port;
    GPIO_PIN Phase_A_Pin;
    GPIO_PORT *Phase_B_Port;
    GPIO_PIN Phase_B_Pin;
};

#endif /* DVC_ENCODER_H */
