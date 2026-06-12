/**
 * @brief GPIO接口
 * @date 2026/6/11
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_GPIO_H
#define DRV_GPIO_H

#include "Drivers/BSP/drv_bsp.h"

/**
 * @brief GPIO宏定义
 * 
 * @typedef GPIO_PORT
 * @typedef GPIO_PIN
 */
#ifdef GPIOA_BASE
#define GPIO_PORT_A GPIOA
#endif
#ifdef GPIOB_BASE
#define GPIO_PORT_B GPIOB
#endif
#define GPIO_PIN_0 DL_GPIO_PIN_0
#define GPIO_PIN_1 DL_GPIO_PIN_1
#define GPIO_PIN_2 DL_GPIO_PIN_2
#define GPIO_PIN_3 DL_GPIO_PIN_3
#define GPIO_PIN_4 DL_GPIO_PIN_4
#define GPIO_PIN_5 DL_GPIO_PIN_5
#define GPIO_PIN_6 DL_GPIO_PIN_6
#define GPIO_PIN_7 DL_GPIO_PIN_7
#define GPIO_PIN_8 DL_GPIO_PIN_8
#define GPIO_PIN_9 DL_GPIO_PIN_9
#define GPIO_PIN_10 DL_GPIO_PIN_10
#define GPIO_PIN_11 DL_GPIO_PIN_11
#define GPIO_PIN_12 DL_GPIO_PIN_12
#define GPIO_PIN_13 DL_GPIO_PIN_13
#define GPIO_PIN_14 DL_GPIO_PIN_14
#define GPIO_PIN_15 DL_GPIO_PIN_15
#define GPIO_PIN_16 DL_GPIO_PIN_16
#define GPIO_PIN_17 DL_GPIO_PIN_17
#define GPIO_PIN_18 DL_GPIO_PIN_18
#define GPIO_PIN_19 DL_GPIO_PIN_19
#define GPIO_PIN_20 DL_GPIO_PIN_20
#define GPIO_PIN_21 DL_GPIO_PIN_21
#define GPIO_PIN_22 DL_GPIO_PIN_22
#define GPIO_PIN_23 DL_GPIO_PIN_23
#define GPIO_PIN_24 DL_GPIO_PIN_24
#define GPIO_PIN_25 DL_GPIO_PIN_25
#define GPIO_PIN_26 DL_GPIO_PIN_26
#define GPIO_PIN_27 DL_GPIO_PIN_27
#define GPIO_PIN_28 DL_GPIO_PIN_28
#define GPIO_PIN_29 DL_GPIO_PIN_29
#define GPIO_PIN_30 DL_GPIO_PIN_30
#define GPIO_PIN_31 DL_GPIO_PIN_31

/**
 * @brief GPIO设置电平
 * 
 * @param gpio GPIO端口
 * @param pins GPIO引脚
 * @param status GPIO状态
 */
static inline void GPIO_Set_Pins(GPIO_PORT *gpio, GPIO_PIN pins, uint8_t status) {
    if (status == STATUS_DISABLE) {
        DL_GPIO_clearPins(gpio, pins);
    }
    else {
        DL_GPIO_setPins(gpio, pins);
    }
}

/**
 * @brief GPIO翻转电平
 * 
 * @param gpio GPIO端口
 * @param pins GPIO引脚
 */
static inline void GPIO_Toggle_Pins(GPIO_PORT *gpio, GPIO_PIN pins) {
    DL_GPIO_togglePins(gpio, pins);
}

/**
 * @brief GPIO读取电平
 * 
 * @param gpio GPIO端口
 * @param pins GPIO引脚
 * @retval 是否有引脚为高电平
 */
static inline uint8_t GPIO_Read_Pins(GPIO_PORT *gpio, GPIO_PIN pins) {
    return (!!DL_GPIO_readPins(gpio, pins));
}

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GPIO中断服务函数组，由用户重写
 */
__WEAK void GPIOB_PIN2_IRQHandler(void);
__WEAK void GPIOB_PIN23_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* DRV_GPIO_H */
