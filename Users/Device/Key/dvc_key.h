/**
 * @brief 按键
 * @date 2026/6/16
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_KEY_H
#define DVC_KEY_H

#include "Drivers/GPIO/drv_gpio.h"

constexpr uint8_t Key_Debounce_Threshold = 2;
constexpr uint16_t Key_Long_Threshold = 50;

/**
 * @brief 按键状态
 */
enum Enum_Key_State {
    Key_State_RELEASED = 0,
    Key_State_PRESSED_DEBOUNCE,
    Key_State_PRESSED_SHORT,
    Key_State_PRESSED_LONG,
    Key_State_RELEASED_DEBOUNCE,
};

class Class_Key {
public:
    void Init(GPIO_PORT *port, GPIO_PIN pin, void (*Short_Func)(void), void (*Long_Func)(void), uint8_t polor = STATUS_DISABLE);

    void TIM_Detect_PeriodElapsedCallback();

protected:
    // 绑定的GPIO
    GPIO_PORT *Key_Port;
    GPIO_PIN Key_Pin;
    // 按键极性，表示按键按下时的电平状态
    uint8_t Key_Polor;
    // 按键动作
    void (*Key_Short_Function)(void) = NULL;
    void (*Key_Long_Function)(void) = NULL;

    // 按键状态
    Enum_Key_State Key_State = Key_State_RELEASED;
    // 计数器
    uint16_t Key_Counter = 0;
    // 长按标志
    uint8_t Key_Long_Pressed = 0;

    // 检测函数
    void Detect(void);
};

#endif /* DVC_KEY_H */
