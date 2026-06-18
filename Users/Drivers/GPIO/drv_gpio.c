/**
 * @brief GPIO接口
 * @date 2026/6/11
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "drv_gpio.h"

/**
 * @brief GPIOA中断服务函数
 */
static inline void GPIOA_IRQHandler(void) {

}

/**
 * @brief GPIOB中断服务函数
 */
static inline void GPIOB_IRQHandler(void) {
    if (DL_GPIO_getEnabledInterruptStatus(GPIO_PORT_B, GPIO_PIN_2) & GPIO_PIN_2) {
        GPIOB_PIN2_IRQHandler();
        DL_GPIO_clearInterruptStatus(GPIO_PORT_B, GPIO_PIN_2);
    }
    if (DL_GPIO_getEnabledInterruptStatus(GPIO_PORT_B, GPIO_PIN_23) & GPIO_PIN_23) {
        GPIOB_PIN23_IRQHandler();
        DL_GPIO_clearInterruptStatus(GPIO_PORT_B, GPIO_PIN_23);
    }
}

/**
 * @brief 系统级GPIO中断函数
 */
void GROUP1_IRQHandler(void) {
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) {
        case DL_INTERRUPT_GROUP1_IIDX_GPIOA:
            GPIOA_IRQHandler();
            break;
        case DL_INTERRUPT_GROUP1_IIDX_GPIOB:
            GPIOB_IRQHandler();
            break;
        default:
            break;
    }
}
