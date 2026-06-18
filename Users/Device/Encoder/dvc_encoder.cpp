/**
 * @brief 编码器
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_encoder.h"

void Class_Encoder::Init(const float &__D_T, const float &__Scale) {
    D_T = __D_T;
    Scale = __Scale;
}

void Class_Encoder::TIM_Update_PeriodElapsedCallback() {
    Angle = Count / Scale * (2 * PI);
    Omega = Angle / D_T;
    Count = 0;
}

void Class_Software_QEI::Init(const float &__D_T, const float &__Scale, const Enum_Software_Encoder_Count_Method &__Encoder_Count_Method, GPIO_PORT *__Phase_A_Port, GPIO_PIN __Phase_A_Pin, GPIO_PORT *__Phase_B_Port, GPIO_PIN __Phase_B_Pin) {
    Class_Encoder::Init(__D_T, __Scale);

    Encoder_Count_Method = __Encoder_Count_Method;

    Phase_A_Port = __Phase_A_Port;
    Phase_A_Pin = __Phase_A_Pin;
    Phase_B_Port = __Phase_B_Port;
    Phase_B_Pin = __Phase_B_Pin;

    if (__Phase_A_Port == GPIO_PORT_A) {
        NVIC_Enable_IT(GPIOA_INT_IRQn);
    }
    else {
        NVIC_Enable_IT(GPIOB_INT_IRQn);
    }
    if (__Phase_B_Port == GPIO_PORT_A) {
        NVIC_Enable_IT(GPIOA_INT_IRQn);
    }
    else {
        NVIC_Enable_IT(GPIOB_INT_IRQn);
    }
}

void Class_Software_QEI::GPIO_InterruptCallback() {
    switch (Encoder_Count_Method) {
    case Encoder_Count_Method_A_UP_AB:
    case Encoder_Count_Method_A_DOWN_BA:
        if (GPIO_Read_Pins(Phase_B_Port, Phase_B_Pin)) {
            Count--;
        }
        else {
            Count++;
        }
        break;
    case Encoder_Count_Method_A_UP_BA:
    case Encoder_Count_Method_A_DOWN_AB:
        if (GPIO_Read_Pins(Phase_B_Port, Phase_B_Pin)) {
            Count++;
        }
        else {
            Count--;
        }
        break;
    case Encoder_Count_Method_B_UP_AB:
    case Encoder_Count_Method_B_DOWN_BA:
        if (GPIO_Read_Pins(Phase_A_Port, Phase_A_Pin)) {
            Count++;
        }
        else {
            Count--;
        }
        break;
    case Encoder_Count_Method_B_UP_BA:
    case Encoder_Count_Method_B_DOWN_AB:
        if (GPIO_Read_Pins(Phase_A_Port, Phase_A_Pin)) {
            Count--;
        }
        else {
            Count++;
        }
        break;
    default:
        break;
    }
}
