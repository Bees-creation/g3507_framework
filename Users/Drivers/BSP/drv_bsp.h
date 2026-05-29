/**
 * @brief 驱动支持包
 * @date 2026/5/21
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_BSP_H
#define DRV_BSP_H

#include "ti_msp_dl_config.h"

/**
 * @brief 系统状态宏定义
 */
#ifndef STATUS_READY
#define STATUS_READY 0
#endif
#ifndef STATUS_DONE
#define STATUS_DONE 0
#endif
#ifndef STATUS_BUSY
#define STATUS_BUSY 1
#endif
#ifndef STATUS_ERROR
#define STATUS_ERROR 2
#endif
#ifndef STATUS_OOM
#define STATUS_OOM 3
#endif

/**
 * @brief GPIO宏定义
 */
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
 * @brief 中断向量宏定义
 */
/* TIMER */
#define TIMG0_IT TIMG0_INT_IRQn
#define TIMG6_IT TIMG6_INT_IRQn
#define TIMG7_IT TIMG7_INT_IRQn
#define TIMG8_IT TIMG8_INT_IRQn
#define TIMG12_IT TIMG12_INT_IRQn
#define TIMA0_IT TIMA0_INT_IRQn
#define TIMA1_IT TIMA1_INT_IRQn
/* DMA */
#define DMA_IT DMA_INT_IRQn
/* UART */
#define UART0_IT UART0_INT_IRQn
#define UART1_IT UART1_INT_IRQn
#define UART2_IT UART2_INT_IRQn
#define UART3_IT UART3_INT_IRQn
/* CAN */
#define CANFD0_IT CANFD0_INT_IRQn
/* SPI */
#define SPI0_IT SPI0_INT_IRQn
#define SPI1_IT SPI1_INT_IRQn
/* I2C */
#define I2C0_IT I2C0_INT_IRQn
#define I2C1_IT I2C1_INT_IRQn
/* ADC */
#define ADC0_IT ADC0_INT_IRQn
#define ADC1_IT ADC1_INT_IRQn
/* GPIO */
#define GPIOA_IT GPIOA_INT_IRQn
#define GPIOB_IT GPIOB_INT_IRQn

/**
 * @brief 类型定义
 */
typedef IRQn_Type NVIC_IRQ;
typedef GPIO_Regs GPIO_PORT;
typedef uint32_t GPIO_PIN;

/**
 * @brief 使能中断向量
 * 
 * @param IRQn 中断向量名
 */
static inline void NVIC_Enable_IT(NVIC_IRQ IRQn) {
    __NVIC_EnableIRQ(IRQn);
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

#endif /* DRV_BSP_H */
