/**
 * @brief 串口驱动
 * @date 2026/5/16
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_UART_H
#define DRV_UART_H

#include "ti_msp_dl_config.h"

#include "Drivers/DMA/drv_dma.h"

#define UART_BUFFER_SIZE 128

/* UART寄存器位定义 */
#define STAT_TXFF (0x0001U << 7)
#define STAT_RXFF (0x0001U << 3)
#define STAT_BUSY (0x0001U << 0)

/**
 * @brief UART回调函数类型
 */
typedef void (*UART_Callback)(uint8_t *Buffer, uint16_t Length);

/**
 * @brief UART通信处理结构体
 * @param DMA_Tx_Manage_Object DMA传输处理结构体
 * @param DMA_Rx_Manage_Object DMA接收处理结构体
 * @param UART_Handler 串口句柄
 * @param Tx_Buffer 传输缓冲区
 * @param Rx_Buffer 接收缓冲区
 * @param Rx_Buffer_Length 接收缓冲区长度，以字节为单位
 * @param Callback_Function 接收回调函数
 */
typedef struct Struct_UART_Manage_Object {
    Struct_DMA_Manage_Object *DMA_Tx_Manage_Object;
    Struct_DMA_Manage_Object *DMA_Rx_Manage_Object;
    UART_Regs *UART_Handler;
    uint8_t Tx_Buffer[UART_BUFFER_SIZE];
    uint8_t Rx_Buffer[UART_BUFFER_SIZE];
    uint16_t Rx_Buffer_Length;
    UART_Callback Callback_Function;
} Struct_UART_Manage_Object;

#if defined UART0_BASE
#define UART0 UART0
extern Struct_UART_Manage_Object UART0_Manage_Object;
#endif
#if defined UART1_BASE
#define UART1 UART1
extern Struct_UART_Manage_Object UART1_Manage_Object;
#endif
#if defined UART2_BASE
#define UART2 UART2
extern Struct_UART_Manage_Object UART2_Manage_Object;
#endif
#if defined UART3_BASE
#define UART3 UART3
extern Struct_UART_Manage_Object UART3_Manage_Object;
#endif
#if defined UART4_BASE
#define UART4 UART4
extern Struct_UART_Manage_Object UART4_Manage_Object;
#endif
#if defined UART5_BASE
#define UART5 UART5
extern Struct_UART_Manage_Object UART5_Manage_Object;
#endif
#if defined UART6_BASE
#define UART6 UART6
extern Struct_UART_Manage_Object UART6_Manage_Object;
#endif
#if defined UART7_BASE
#define UART7 UART7
extern Struct_UART_Manage_Object UART7_Manage_Object;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief UART初始化
 *
 * @param UARTx UART编号
 * @param Callback_Function 处理回调函数
 * @param Rx_Buffer_Length 接收缓冲区长度，以字节为单位
 * @param DMAx DMA编号
 * @param DMA_Tx_CH_CHAN_ID DMA发送通道ID，-1表示不使用
 * @param DMA_Rx_CH_CHAN_ID DMA接收通道ID，-1表示不使用
 */
void UART_DMA_Init(
    UART_Regs *UARTx, UART_Callback Callback_Function, uint16_t Rx_Buffer_Length, DMA_Regs *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID);

/**
 * @brief UART发送
 * 
 * @param UARTx UART编号
 * @param Data 发送缓冲区的数据指针
 * @param Length 长度
 * @return 执行状态
 */
uint8_t UART_Send_Data(UART_Regs *UARTx, uint8_t *Data, uint16_t Length);

/**
 * @brief UART接收
 * 
 * @param UARTx UART编号
 * @param Data 接收缓冲区的数据指针
 * @param Length 长度
 * @return 执行状态
 */
uint8_t UART_Receive_Data(UART_Regs *UARTx, uint8_t *pData, uint16_t Length);

/**
 * @brief UART中断处理函数
 * 
 * @param UARTx UART编号
 */
__WEAK void UART_IRQHandler(UART_Regs *UARTx);

#ifdef __cplusplus
}
#endif

#endif /* DRV_UART_H */
