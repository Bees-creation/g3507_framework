/**
 * @brief 计时器
 * @date 2026/7/29
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "Device/Timer/timer.h"

void Class_Timer::Init(void) {
    NVIC_Enable_IT(TIMG12_IT);
    TIM_Start_Counter((TIMER_INST*)TIMG12);
}

void Class_Timer::Update(void) {
    time = Timestamp;
}

void Class_Timer::Clear(void) {
    Timestamp = 0;
}

uint32_t Class_Timer::Get(void) {
    return time;
}
