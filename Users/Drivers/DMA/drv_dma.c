/**
 * @brief DMA驱动
 * @date 2026/5/19
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "drv_dma.h"

#if defined DMA
#if defined DMA_CHANNEL_0
Struct_DMA_Manage_Object DMA_CH0_Manage_Object;
#endif
#if defined DMA_CHANNEL_1
Struct_DMA_Manage_Object DMA_CH1_Manage_Object;
#endif
#if defined DMA_CHANNEL_2
Struct_DMA_Manage_Object DMA_CH2_Manage_Object;
#endif
#if defined DMA_CHANNEL_3
Struct_DMA_Manage_Object DMA_CH3_Manage_Object;
#endif
#if defined DMA_CHANNEL_4
Struct_DMA_Manage_Object DMA_CH4_Manage_Object;
#endif
#if defined DMA_CHANNEL_5
Struct_DMA_Manage_Object DMA_CH5_Manage_Object;
#endif
#if defined DMA_CHANNEL_6
Struct_DMA_Manage_Object DMA_CH6_Manage_Object;
#endif
#if defined DMA_CHANNEL_7
Struct_DMA_Manage_Object DMA_CH7_Manage_Object;
#endif
#endif

Struct_DMA_Manage_Object* DMA_Init(
    DMA_INST *DMAx,
    uint8_t DMA_CH_CHAN_ID,
    uint32_t Src_Address,
    uint32_t Dest_Address,
    uint16_t Package_Size) {
#if defined DMA
    if (DMAx == DMA) {
#if defined DMA_CHANNEL_0
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_0) {
            DMA_CH0_Manage_Object.DMA_Handler = DMA;
            DMA_CH0_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH0_Manage_Object.Src_Address = Src_Address;
            DMA_CH0_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH0_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH0_Manage_Object);
            return &DMA_CH0_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_1
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_1) {
            DMA_CH1_Manage_Object.DMA_Handler = DMA;
            DMA_CH1_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH1_Manage_Object.Src_Address = Src_Address;
            DMA_CH1_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH1_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH1_Manage_Object);
            return &DMA_CH1_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_2
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_2) {
            DMA_CH2_Manage_Object.DMA_Handler = DMA;
            DMA_CH2_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH2_Manage_Object.Src_Address = Src_Address;
            DMA_CH2_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH2_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH2_Manage_Object);
            return &DMA_CH2_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_3
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_3) {
            DMA_CH3_Manage_Object.DMA_Handler = DMA;
            DMA_CH3_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH3_Manage_Object.Src_Address = Src_Address;
            DMA_CH3_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH3_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH3_Manage_Object);
            return &DMA_CH3_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_4
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_4) {
            DMA_CH4_Manage_Object.DMA_Handler = DMA;
            DMA_CH4_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH4_Manage_Object.Src_Address = Src_Address;
            DMA_CH4_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH4_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH4_Manage_Object);
            return &DMA_CH4_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_5
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_5) {
            DMA_CH5_Manage_Object.DMA_Handler = DMA;
            DMA_CH5_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH5_Manage_Object.Src_Address = Src_Address;
            DMA_CH5_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH5_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH5_Manage_Object);
            return &DMA_CH5_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_6
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_6) {
            DMA_CH6_Manage_Object.DMA_Handler = DMA;
            DMA_CH6_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH6_Manage_Object.Src_Address = Src_Address;
            DMA_CH6_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH6_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH6_Manage_Object);
            return &DMA_CH6_Manage_Object;
        }
#endif
#if defined DMA_CHANNEL_7
        if (DMA_CH_CHAN_ID == DMA_CHANNEL_7) {
            DMA_CH7_Manage_Object.DMA_Handler = DMA;
            DMA_CH7_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH7_Manage_Object.Src_Address = Src_Address;
            DMA_CH7_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH7_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH7_Manage_Object);
            return &DMA_CH7_Manage_Object;
        }
#endif
    }
#endif
    return NULL;
}

void DMA_Config(Struct_DMA_Manage_Object *DMA_Manage_Object) {
    DL_DMA_disableChannel(
        DMA_Manage_Object->DMA_Handler,
        DMA_Manage_Object->DMA_Channel);
    DL_DMA_setSrcAddr(
        DMA_Manage_Object->DMA_Handler,
        DMA_Manage_Object->DMA_Channel,
        DMA_Manage_Object->Src_Address);
    DL_DMA_setDestAddr(
        DMA_Manage_Object->DMA_Handler,
        DMA_Manage_Object->DMA_Channel,
        DMA_Manage_Object->Dest_Address);
    DL_DMA_setTransferSize(
        DMA_Manage_Object->DMA_Handler,
        DMA_Manage_Object->DMA_Channel,
        DMA_Manage_Object->Package_Size);

    DMA_Manage_Object->Busy = STATUS_READY;
}

uint8_t DMA_Send_Data(Struct_DMA_Manage_Object *DMA_Manage_Object, uint8_t *pData, uint16_t Size) {
    if (DMA_Manage_Object->Busy == STATUS_READY) {
        DMA_Manage_Object->Src_Address = (uint32_t)pData;
        DMA_Manage_Object->Package_Size = Size;
        DL_DMA_disableChannel(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel);
        DL_DMA_setSrcAddr(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel,
            DMA_Manage_Object->Src_Address);
        DL_DMA_setTransferSize(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel,
            DMA_Manage_Object->Package_Size);
        DL_DMA_enableChannel(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel);
    }
    else {
        return STATUS_BUSY;
    }

    DMA_Manage_Object->Busy = STATUS_BUSY;
    return STATUS_DONE;
}

uint8_t DMA_Receive_Data(Struct_DMA_Manage_Object *DMA_Manage_Object, uint8_t *pData, uint16_t Size) {
    if (DMA_Manage_Object->Busy == STATUS_READY) {
        DMA_Manage_Object->Dest_Address = (uint32_t)pData;
        DMA_Manage_Object->Package_Size = Size;
        DL_DMA_disableChannel(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel);
        DL_DMA_setDestAddr(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel,
            DMA_Manage_Object->Dest_Address);
        DL_DMA_setTransferSize(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel,
            DMA_Manage_Object->Package_Size);
        DL_DMA_enableChannel(
            DMA_Manage_Object->DMA_Handler,
            DMA_Manage_Object->DMA_Channel);
    }
    else {
        return STATUS_BUSY;
    }

    DMA_Manage_Object->Busy = STATUS_BUSY;
    return STATUS_DONE;
}
