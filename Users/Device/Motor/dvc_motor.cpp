/**
 * @brief 电机
 * @date 2026/5/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_motor.h"

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
