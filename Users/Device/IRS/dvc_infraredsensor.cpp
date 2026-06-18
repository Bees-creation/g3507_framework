/**
 * @brief 红外传感器
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_infraredsensor.h"

void Class_8C_IRS::Init(Enum_IRS_Detect_Type __IRS_Detect_Type, GPIO_PORT *__Selector_Port_AD0, GPIO_PIN __Selector_Pin_AD0, GPIO_PORT *__Selector_Port_AD1, GPIO_PIN __Selector_Pin_AD1, GPIO_PORT *__Selector_Port_AD2, GPIO_PIN __Selector_Pin_AD2, GPIO_PORT *__Data_Port, GPIO_PIN __Data_Pin) {
    IRS_Detect_Type = __IRS_Detect_Type;
    Selector_Ports[0] = __Selector_Port_AD0;
    Selector_Pins[0] = __Selector_Pin_AD0;
    Selector_Ports[1] = __Selector_Port_AD1;
    Selector_Pins[1] = __Selector_Pin_AD1;
    Selector_Ports[2] = __Selector_Port_AD2;
    Selector_Pins[2] = __Selector_Pin_AD2;
    Data_Port = __Data_Port;
    Data_Pin = __Data_Pin;
}

void Class_8C_IRS::TIM_Feedback_PeriodElapsedCallback() {
    for (int i = 0; i < 8; i++) {
        GPIO_Set_Pins(Selector_Ports[0], Selector_Pins[0], !!(i & 0x01));
        GPIO_Set_Pins(Selector_Ports[1], Selector_Pins[1], !!(i & 0x02));
        GPIO_Set_Pins(Selector_Ports[2], Selector_Pins[2], !!(i & 0x04));

        Sys_Delay(50);
        switch (IRS_Detect_Type) {
        case IRS_Detect_Type_Positive:
            Channels[i] = !GPIO_Read_Pins(Data_Port, Data_Pin);
            break;
        case IRS_Detect_Type_Negative:
            Channels[i] = GPIO_Read_Pins(Data_Port, Data_Pin);
            break;
        default:
            break;
        }
    }
}
