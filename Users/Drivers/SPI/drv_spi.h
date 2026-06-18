/**
 * @brief SPI驱动
 * @date 2026/6/12
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_SPI_H
#define DRV_SPI_H

#include "Drivers/DMA/drv_dma.h"
#include "Drivers/GPIO/drv_gpio.h"

/**
 * @brief SPI回调函数类型
 */
typedef void (*SPI_Callback)(uint8_t *Buffer, uint16_t Length);

/**
 * @brief SPI通信处理结构体
 * @param DMA_Tx_Manage_Object DMA传输处理结构体
 * @param DMA_Rx_Manage_Object DMA接收处理结构体
 * @param SPI_Handler SPI句柄
 * @param Tx_Buffer 传输数组指针
 * @param Rx_Buffer 接收数组指针
 * @param CS_Port 片选GPIO端口
 * @param CS_Pin 片选GPIO引脚
 * @param CS_Act 片选信号有效状态，0表示低电平有效，1表示高电平有效
 * @param Rx_Length 当前接收的数据长度，以字节为单位
 * @param Callback_Function 接收回调函数
 */
typedef struct Struct_SPI_Manage_Object {
    Struct_DMA_Manage_Object *DMA_Tx_Manage_Object;
    Struct_DMA_Manage_Object *DMA_Rx_Manage_Object;
    SPI_Regs *SPI_Handler;
    uint8_t *Tx_Buffer;
    uint8_t *Rx_Buffer;
    GPIO_PORT *CS_Port;
    GPIO_PIN CS_Pin;
    uint8_t CS_Act;
    uint16_t Rx_Length;
    SPI_Callback Callback_Function;
} Struct_SPI_Manage_Object;

#if defined SPI0_BASE
#define SPI0 SPI0
extern Struct_SPI_Manage_Object SPI0_Manage_Object;
#endif
#if defined SPI1_BASE
#define SPI1 SPI1
extern Struct_SPI_Manage_Object SPI1_Manage_Object;
#endif
#if defined SPI2_BASE
#define SPI2 SPI2
extern Struct_SPI_Manage_Object SPI2_Manage_Object;
#endif
#if defined SPI3_BASE
#define SPI3 SPI3
extern Struct_SPI_Manage_Object SPI3_Manage_Object;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI初始化
 *
 * @param SPIx SPI编号
 * @param DMAx DMA编号
 * @param DMA_Tx_CH_CHAN_ID DMA发送通道ID，-1表示不使用
 * @param DMA_Rx_CH_CHAN_ID DMA接收通道ID，-1表示不使用
 * @param CS_Port 片选GPIO端口
 * @param CS_Pin 片选GPIO引脚
 * @param CS_Act 片选信号有效状态，0表示低电平有效，1表示高电平有效
 * @param Callback_Function 接收回调函数
 */
void SPI_DMA_Init(
    SPI_INST *SPIx, DMA_INST *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID, GPIO_PORT *CS_Port, GPIO_PIN CS_Pin, uint8_t CS_Act, SPI_Callback Callback_Function);

/**
 * @brief SPI片选信号
 *
 * @param SPIx SPI编号
 * @param status 片选信号状态
 */
void SPI_CS_Set(SPI_INST *SPIx, uint8_t status);

/**
 * @brief SPI交换数据
 * 
 * @param SPIx SPI编号
 * @param TxData 发送数据指针
 * @param RxData 接收数据指针
 * @param Length 长度
 * @return 执行状态
 */
uint8_t SPI_Exchange_Data(SPI_INST *SPIx, uint8_t *TxData, uint8_t *RxData, uint16_t Length);

/**
 * @brief SPI中断处理函数
 * 
 * @param SPIx SPI编号
 */
__WEAK void SPI_IRQHandler(SPI_INST *SPIx);

#ifdef __cplusplus
}
#endif

#endif /* DRV_SPI_H */
