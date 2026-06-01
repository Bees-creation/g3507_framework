/**
 * @brief 视觉任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_visual.h"

Class_8C_IRS IRS;

float Channels[8];

void Visual_Init(void) {
    IRS.Init(IRS_PORT_AD0, IRS_PIN_AD0, IRS_PORT_AD1, IRS_PIN_AD1, IRS_PORT_AD2, IRS_PIN_AD2, IRS_PORT_OUT, IRS_PIN_OUT);
}

void Visual_Task(void) {
    IRS.TIM_Feedback_PeriodElapsedCallback();
    for (int i = 0; i < 8; i++) {
        Channels[i] = IRS.Get_Channels()[i];
    }
}
