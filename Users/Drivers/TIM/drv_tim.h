/**
 * @brief TIM驱动
 * @date 2026/7/29
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_TIM_H
#define DRV_TIM_H

#include "Drivers/BSP/drv_bsp.h"

extern uint32_t Timestamp;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief TIM中断处理函数
 * 
 * @param TIMx TIM编号
 */
__WEAK void TIM_IRQHandler(TIMER_INST *TIMx);

#ifdef __cplusplus
}
#endif

#endif /* DRV_TIM_H */
