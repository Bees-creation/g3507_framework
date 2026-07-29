/**
 * @brief TIM驱动
 * @date 2026/7/29
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "Drivers/TIM/drv_tim.h"

uint32_t Timestamp;

void TIM_IRQHandler(TIMER_INST *TIMx) {
#if defined TIMG12
    if (TIMx == TIMG12) {
        switch (DL_TimerG_getPendingInterrupt(TIMx)) {
            case DL_TIMER_IIDX_ZERO:
                Timestamp++;
                break;
            default:
                break;
        }
    }
#endif
}

#if defined TIMG12
void TIMG12_IRQHandler(void) {
    TIM_IRQHandler(TIMG12);
}
#endif
