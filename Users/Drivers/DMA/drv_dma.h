/**
 * @brief DMA驱动
 * @date 2026/5/19
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_DMA_H
#define DRV_DMA_H

#include "ti_msp_dl_config.h"

#include "Drivers/BSP/drv_bsp.h"

/**
 * @brief DMA传输处理结构体
 * @param DMA_Handler DMA句柄
 * @param Src_Address 源地址
 * @param Dest_Address 目标地址
 * @param Package_Size 数据包长度，以字节为单位
 * @param DMA_Channel DMA通道
 * @param Busy 空闲状态，0为空闲，1为忙碌
 */
typedef struct Struct_DMA_Manage_Object {
    DMA_Regs *DMA_Handler;
    uint32_t Src_Address;
    uint32_t Dest_Address;
    uint16_t Package_Size;
    uint8_t DMA_Channel;
    uint8_t Busy;
} Struct_DMA_Manage_Object;

#ifdef __cplusplus
extern "C" {
#endif

extern Struct_DMA_Manage_Object DMA_CH0_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH1_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH2_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH3_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH4_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH5_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH6_Manage_Object;
extern Struct_DMA_Manage_Object DMA_CH7_Manage_Object;

/**
 * @brief DMA初始化
 *
 * @param DMAx DMA编号
 * @param DMA_CH_CHAN_ID DMA通道ID
 * @param Src_Address 源地址
 * @param Dest_Address 目标地址
 * @param Package_Size 数据包长度，以字节为单位
 * 
 * @retval DMA传输处理结构体指针
 */
Struct_DMA_Manage_Object* DMA_Init(
    DMA_Regs *DMAx,
    uint8_t DMA_CH_CHAN_ID,
    uint32_t Src_Address,
    uint32_t Dest_Address,
    uint16_t Package_Size);

/**
 * @brief DMA传输配置
 * 
 * @param DMA_Manage_Object DMA传输处理结构体
 */
void DMA_Config(Struct_DMA_Manage_Object *DMA_Manage_Object);

/**
 * @brief DMA发送
 * 
 * @param DMA_Manage_Object DMA传输处理结构体
 */
uint8_t DMA_Send_Data(Struct_DMA_Manage_Object *DMA_Manage_Object, uint8_t *pData, uint16_t Size);

/**
 * @brief DMA接收
 * 
 * @param DMA_Manage_Object DMA传输处理结构体
 */
uint8_t DMA_Receive_Data(Struct_DMA_Manage_Object *DMA_Manage_Object, uint8_t *pData, uint16_t Size);

#ifdef __cplusplus
}
#endif

#endif /* DRV_DMA_H */
