/**
 * @brief 电机
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_motor.h"

void Class_Brush_Motor_Drv8701e::Init(TIMER_INST *TIMx, TIMER_CHANNEL __Channel, const Enum_Motor_Control_Method &__Control_Method, const Enum_Motor_Control_Algorithm &__Control_Algorithm, GPIO_PORT *__Direction_Port, GPIO_PIN __Direction_Pin, float __D_T, float __Filter) {
    TIM = TIMx;
    Channel = __Channel;
    Control_Method = __Control_Method;
    Control_Algorithm = __Control_Algorithm;
    Direction_Port = __Direction_Port;
    Direction_Pin = __Direction_Pin;

    D_T = __D_T;
    Filter = __Filter;

    Start_Motor();
}

void Class_Brush_Motor_Drv8701e::TIM_Calculate_PeriodElapsedCallback() {
    switch (Control_Algorithm) {
    case Motor_Control_Algorithm_PID:
        if (Control_Method == Motor_Control_Method_Angle) {
            Angle_Loop.Set_Now(Now_Angle);
            Angle_Loop.Set_Target(Absolute_Target_Angle);
            Angle_Loop.TIM_Calculate_PeriodElapsedCallback();
            Absolute_Target_Omega = Angle_Loop.Get_Out();
        }
        if (Control_Method == Motor_Control_Method_Omega) {
            Omega_Loop.Set_Now(Now_Omega);
            Omega_Loop.Set_Target(Absolute_Target_Omega);
            Omega_Loop.TIM_Calculate_PeriodElapsedCallback();
            Absolute_Target_Torque = Omega_Loop.Get_Out();
        }
        // 禁用力矩环
        Out = Absolute_Target_Torque;
        break;
    default:
        Out = 0.0f;
        break;
    }
}

void Class_Brush_Motor_Drv8701e::TIM_Output_PeriodElapsedCallback() {
    if (Out > 0) {
        GPIO_Set_Pins(Direction_Port, Direction_Pin, STATUS_DISABLE);
    }
    else {
        GPIO_Set_Pins(Direction_Port, Direction_Pin, STATUS_ENABLE);
    }
    // TIM设置输出比较值
    TIM_Set_Compare(TIM, Math_Abs(Out), Channel);
}

void Class_Brush_Motor_Drv8701e::TIM_Feedback_PeriodElapsedCallback() {
    QEI.TIM_Update_PeriodElapsedCallback();
    Now_Omega = Filter_First_Order(QEI.Get_Omega(), Now_Omega, Filter);
    Now_Angle += Now_Omega * D_T;
}

void Class_Stepping_Motor_D36A::Init(TIMER_INST *TIMx, TIMER_CHANNEL __Channel, const Enum_Stepping_Motor_Control_Method &__Control_Method, GPIO_PORT *__Direction_Port, GPIO_PIN __Direction_Pin, float __D_T, uint32_t __Frequency, float __Min, float __Max, uint32_t __Scale, uint8_t __Division) {
    TIM = TIMx;
    Channel = __Channel;
    Control_Method = __Control_Method;
    Direction_Port = __Direction_Port;
    Direction_Pin = __Direction_Pin;

    D_T = __D_T;

    Frequency = __Frequency;
    Min = __Min;
    Max = __Max;

    Scale = __Scale;
    Division = __Division;
    Step = (float)(Scale * Division) / (2 * PI);

    Start_Motor();
}

void Class_Stepping_Motor_D36A::TIM_Calculate_PeriodElapsedCallback() {
    switch (Control_Method) {
    case Stepping_Motor_Control_Method_Angle:
        Absolute_Target_Omega = Absolute_Target_Angle - Now_Angle;
        break;
    case Stepping_Motor_Control_Method_Omega:
        break;
    default:
        break;
    }
}

void Class_Stepping_Motor_D36A::TIM_Output_PeriodElapsedCallback() {
    // 判断方向
    if (Absolute_Target_Omega > 0) {
        GPIO_Set_Pins(Direction_Port, Direction_Pin, STATUS_ENABLE);
    }
    else {
        GPIO_Set_Pins(Direction_Port, Direction_Pin, STATUS_DISABLE);
    }

    // 速度绝对值
    float Omega = Math_Abs(Absolute_Target_Omega);
    // 到达目标角度时停止
    if (Omega < (1.0f / Step)) {
        DL_Timer_setCaptureCompareValue(TIM, 0, Channel);
        Now_Omega = 0.0f;
        return;
    }
    // 速度限幅
    Math_Constrain(&Omega, Min, Max);
    // 计算周期
    uint32_t period = (Frequency / (Omega * Step));

    DL_Timer_setLoadValue(TIM, period);
    DL_Timer_setCaptureCompareValue(TIM, period / 2, Channel);

    Now_Omega = Omega;
}

void Class_Stepping_Motor_D36A::TIM_Feedback_PeriodElapsedCallback() {
    Now_Angle += Now_Omega * D_T;
}
