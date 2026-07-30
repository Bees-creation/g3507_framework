/**
 * @brief IIC驱动
 * @date 2026/7/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_I2C_H
#define DRV_I2C_H

#include "Drivers/DMA/drv_dma.h"

#define I2C_FIFO_DEPTH 8

/**
 * @brief I2C回调函数类型
 */
typedef void (*I2C_Callback)(uint8_t *Buffer, uint16_t Length);

/**
 * @brief I2C通信处理结构体
 * @param DMA_Tx_Manage_Object DMA传输处理结构体
 * @param DMA_Rx_Manage_Object DMA接收处理结构体
 * @param I2C_Handler I2C句柄
 * @param Tx_Buffer 传输数组指针
 * @param Rx_Buffer 接收数组指针
 * @param Rx_Length 当前接收的数据长度，以字节为单位
 * @param Callback_Function 接收回调函数
 */
typedef struct Struct_I2C_Manage_Object {
    Struct_DMA_Manage_Object *DMA_Tx_Manage_Object;
    Struct_DMA_Manage_Object *DMA_Rx_Manage_Object;
    I2C_Regs *I2C_Handler;
    uint8_t *Tx_Buffer;
    uint8_t *Rx_Buffer;
    uint16_t Rx_Length;
    I2C_Callback Callback_Function;
} Struct_I2C_Manage_Object;

#if defined I2C0_BASE
#define I2C0 I2C0
extern Struct_I2C_Manage_Object I2C0_Manage_Object;
#endif
#if defined I2C1_BASE
#define I2C1 I2C1
extern Struct_I2C_Manage_Object I2C1_Manage_Object;
#endif
#if defined I2C2_BASE
#define I2C2 I2C2
extern Struct_I2C_Manage_Object I2C2_Manage_Object;
#endif
#if defined I2C3_BASE
#define I2C3 I2C3
extern Struct_I2C_Manage_Object I2C3_Manage_Object;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief I2C初始化
 *
 * @param I2Cx I2C编号
 */
void I2C_DMA_Init(
    I2C_INST *I2Cx, DMA_INST *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID, I2C_Callback Callback_Function);

/**
 * @brief I2C发送
 * 
 * @param I2Cx I2C编号
 * @param Addr 从机地址
 * @param pData 发送缓冲区的数据指针
 * @param Length 长度
 * @return 执行状态
 */
uint8_t I2C_Send_Data(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length);

/**
 * @brief I2C接收
 * 
 * @param I2Cx I2C编号
 * @param Addr 从机地址
 * @param pData 接收缓冲区的数据指针
 * @param Length 长度
 * @return 执行状态
 */
uint8_t I2C_Receive_Data(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length);

/**
 * @brief I2C中断处理函数
 * 
 * @param I2Cx I2C编号
 */
__WEAK void I2C_IRQHandler(I2C_INST *I2Cx);

#ifdef __cplusplus
}
#endif

#endif /* DRV_IIC_H */
