/**
 * @brief DMA驱动
 * @date 2026/5/19
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DRV_DMA_H
#define DRV_DMA_H

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
    DMA_INST *DMA_Handler;
    uint32_t Src_Address;
    uint32_t Dest_Address;
    uint16_t Package_Size;
    uint8_t DMA_Channel;
    uint8_t Busy;
} Struct_DMA_Manage_Object;

#if defined DMA_BASE
#define DMA DMA
#if defined DMA_CH_0_TRIG
#define DMA_CHANNEL_0 DMA_CH_0_TRIG
extern Struct_DMA_Manage_Object DMA_CH0_Manage_Object;
#endif
#if defined DMA_CH_1_TRIG
#define DMA_CHANNEL_1 DMA_CH_1_TRIG
extern Struct_DMA_Manage_Object DMA_CH1_Manage_Object;
#endif
#if defined DMA_CH_2_TRIG
#define DMA_CHANNEL_2 DMA_CH_2_TRIG
extern Struct_DMA_Manage_Object DMA_CH2_Manage_Object;
#endif
#if defined DMA_CH_3_TRIG
#define DMA_CHANNEL_3 DMA_CH_3_TRIG
extern Struct_DMA_Manage_Object DMA_CH3_Manage_Object;
#endif
#if defined DMA_CH_4_TRIG
#define DMA_CHANNEL_4 DMA_CH_4_TRIG
extern Struct_DMA_Manage_Object DMA_CH4_Manage_Object;
#endif
#if defined DMA_CH_5_TRIG
#define DMA_CHANNEL_5 DMA_CH_5_TRIG
extern Struct_DMA_Manage_Object DMA_CH5_Manage_Object;
#endif
#if defined DMA_CH_6_TRIG
#define DMA_CHANNEL_6 DMA_CH_6_TRIG
extern Struct_DMA_Manage_Object DMA_CH6_Manage_Object;
#endif
#if defined DMA_CH_7_TRIG
#define DMA_CHANNEL_7 DMA_CH_7_TRIG
extern Struct_DMA_Manage_Object DMA_CH7_Manage_Object;
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

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
    DMA_INST *DMAx,
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
