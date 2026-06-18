/**
 * @brief 按键
 * @date 2026/6/16
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_key.h"

void Class_Key::Init(GPIO_PORT *port, GPIO_PIN pin, void (*Short_Func)(void), void (*Long_Func)(void), uint8_t polor) {
    Key_Port = port;
    Key_Pin = pin;
    Key_Polor = polor;
    Key_Short_Function = Short_Func;
    Key_Long_Function = Long_Func;
}

void Class_Key::TIM_Detect_PeriodElapsedCallback() {
    Detect();
}

void Class_Key::Detect(void) {
    uint8_t currentPinLevel = GPIO_Read_Pins(Key_Port, Key_Pin);

    switch(Key_State) {
        case Key_State_RELEASED:
            if (currentPinLevel == Key_Polor) { // 检测到按下
                Key_State = Key_State_PRESSED_DEBOUNCE;
                Key_Counter = 0; // 重置计数器
            }
            break;

        case Key_State_PRESSED_DEBOUNCE:
            if (currentPinLevel == Key_Polor) {
                Key_Counter++; // 累加计数
                if (Key_Counter >= Key_Debounce_Threshold) { // 连续采样都为按下，确认按下
                    Key_State = Key_State_PRESSED_SHORT;
                }
            } else {
                Key_State = Key_State_RELEASED; // 抖动，回到释放态
                Key_Counter = 0;
            }
            break;

        case Key_State_PRESSED_SHORT:
            if (currentPinLevel == Key_Polor) { // 检测到按下
                Key_Counter++;
                if (Key_Counter >= Key_Long_Threshold) { // 连续采样都为按下，确认长按
                    Key_State = Key_State_PRESSED_LONG;
                    Key_Counter = 0;
                }
            } else {
                Key_State = Key_State_RELEASED_DEBOUNCE;
                Key_Counter = 0;
            }
            break;

        case Key_State_PRESSED_LONG:
            if (currentPinLevel != Key_Polor) { // 检测到释放
                Key_Long_Pressed = 1;
                Key_State = Key_State_RELEASED_DEBOUNCE;
                Key_Counter = 0;
            }
            break;

        case Key_State_RELEASED_DEBOUNCE:
            if (currentPinLevel != Key_Polor) {
                Key_Counter++;
                if (Key_Counter >= Key_Debounce_Threshold) { // 确认释放
                    Key_State = Key_State_RELEASED;
                    if (!Key_Long_Pressed && Key_Short_Function != NULL) {
                        Key_Short_Function();
                    }
                    else if (Key_Long_Pressed && Key_Long_Function != NULL) {
                        Key_Long_Pressed = 0;
                        Key_Long_Function();
                    }
                }
            } else {// 抖动，回到按下态
                if (Key_Long_Pressed) {
                    Key_State = Key_State_PRESSED_LONG;
                } else {
                    Key_State = Key_State_PRESSED_SHORT;
                }
                Key_Counter = 0;
            }
            break;
    }
}
