/**
 * @brief 驱动支持包
 * @date 2026/5/21
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_BSP_H
#define DRV_BSP_H

#include "ti_msp_dl_config.h"

#define SYS_FREQ (CPUCLK_FREQ)
#define SYS_US (SYS_FREQ / 1000000)

/**
 * @brief 系统状态宏定义
 * 
 * @def STATUS_READY 就绪
 * @def STATUS_DONE 完成
 * @def STATUS_BUSY 忙碌
 * @def STATUS_ERROR 错误
 * @def STATUS_OOM 内存不足
 * @def STATUS_DISABLE 使能
 * @def STATUS_ENABLE 失能
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
#ifndef STATUS_DISABLE
#define STATUS_DISABLE 0
#endif 
#ifndef STATUS_ENABLE
#define STATUS_ENABLE 1
#endif 

/**
 * @brief 中断向量宏定义
 * 
 * @typedef NVIC_IRQ
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
 * @brief 定时器宏定义
 * 
 * @typedef TIMER_INST
 */
#if defined TIMG0_BASE
#define TIMG0 TIMG0_BASE
#endif
#if defined TIMG6_BASE
#define TIMG6 TIMG6_BASE
#endif
#if defined TIMG7_BASE
#define TIMG7 TIMG7_BASE
#endif
#if defined TIMG8_BASE
#define TIMG8 TIMG8_BASE
#endif
#if defined TIMG12_BASE
#define TIMG12 TIMG12_BASE
#endif
#if defined TIMA0_BASE
#define TIMA0 TIMA0_BASE
#endif
#if defined TIMA1_BASE
#define TIMA1 TIMA1_BASE
#endif

/**
 * @brief 定时器输入输出通道
 * 
 * @typedef TIMER_CHANNEL
 */
#define TIMER_CHANNEL_0 DL_TIMER_CC_0_INDEX
#define TIMER_CHANNEL_1 DL_TIMER_CC_1_INDEX
#define TIMER_CHANNEL_2 DL_TIMER_CC_2_INDEX
#define TIMER_CHANNEL_3 DL_TIMER_CC_3_INDEX
#define TIMER_CHANNEL_4 DL_TIMER_CC_4_INDEX
#define TIMER_CHANNEL_5 DL_TIMER_CC_5_INDEX

/**
 * @brief 类型定义
 */
typedef IRQn_Type NVIC_IRQ;
typedef GPIO_Regs GPIO_PORT;
typedef uint32_t GPIO_PIN;
typedef GPTIMER_Regs TIMER_INST;
typedef DL_TIMER_CC_INDEX TIMER_CHANNEL;

/**
 * @brief 延时函数
 * 
 * @param us 微秒
 */
static inline void Sys_Delay(uint32_t us) {
    delay_cycles(us * SYS_US);
}

/**
 * @brief 使能中断向量
 * 
 * @param IRQn 中断向量名
 */
static inline void NVIC_Enable_IT(NVIC_IRQ IRQn) {
    __NVIC_EnableIRQ(IRQn);
}

/**
 * @brief TIM启动定时器
 * 
 * @param TIMx 定时器
 */
static inline void TIM_Start_Counter(TIMER_INST *TIMx) {
    DL_Timer_startCounter(TIMx);
}

/**
 * @brief TIM停用定时器
 * 
 * @param TIMx 定时器
 */
static inline void TIM_Stop_Counter(TIMER_INST *TIMx) {
    DL_Timer_stopCounter(TIMx);
}

/**
 * @brief TIM设置比较值
 * 
 * @param TIMx 定时器
 * @param value 值
 * @param Channel 定时器通道
 */
static inline void TIM_Set_Compare(TIMER_INST *TIMx, uint32_t value, TIMER_CHANNEL Channel) {
    DL_Timer_setCaptureCompareValue(TIMx, value, Channel);
}

#endif /* DRV_BSP_H */
