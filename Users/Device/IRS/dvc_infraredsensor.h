/**
 * @brief 红外传感器
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_INFRAREDSENSOR_H
#define DVC_INFRAREDSENSOR_H

#include "Drivers/GPIO/drv_gpio.h"

enum Enum_IRS_Detect_Type {
    IRS_Detect_Type_Positive = 0,// 1表示白色
    IRS_Detect_Type_Negative,// 1表示黑色
};

/**
 * @brief 八通道红外巡线模块
 */
class Class_8C_IRS {
public:
    void Init(Enum_IRS_Detect_Type __IRS_Detect_Type, GPIO_PORT *__Selector_Port_AD0, GPIO_PIN __Selector_Pin_AD0, GPIO_PORT *__Selector_Port_AD1, GPIO_PIN __Selector_Pin_AD1, GPIO_PORT *__Selector_Port_AD2, GPIO_PIN __Selector_Pin_AD2, GPIO_PORT *__Data_Port, GPIO_PIN __Data_Pin);

    void TIM_Feedback_PeriodElapsedCallback();

    inline uint8_t *Get_Channels(void) {
        return Channels;
    }

protected:
    // 通道值，1表示轨迹
    uint8_t Channels[8];

    Enum_IRS_Detect_Type IRS_Detect_Type;

    // 3线转8线数据选择器引脚
    GPIO_PORT *Selector_Ports[3];
    GPIO_PIN Selector_Pins[3];
    // 输出引脚
    GPIO_PORT *Data_Port;
    GPIO_PIN Data_Pin;
};

#endif /* DVC_INFRAREDSENSOR_H */
