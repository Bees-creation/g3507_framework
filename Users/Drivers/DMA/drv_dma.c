/**
 * @brief DMA驱动
 * @date 2026/5/19
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "drv_dma.h"

#if defined DMA_BASE
#if defined DMA_CH_0_TRIG
Struct_DMA_Manage_Object DMA_CH0_Manage_Object;
#endif
#if defined DMA_CH_1_TRIG
Struct_DMA_Manage_Object DMA_CH1_Manage_Object;
#endif
#if defined DMA_CH_2_TRIG
Struct_DMA_Manage_Object DMA_CH2_Manage_Object;
#endif
#if defined DMA_CH_3_TRIG
Struct_DMA_Manage_Object DMA_CH3_Manage_Object;
#endif
#if defined DMA_CH_4_TRIG
Struct_DMA_Manage_Object DMA_CH4_Manage_Object;
#endif
#if defined DMA_CH_5_TRIG
Struct_DMA_Manage_Object DMA_CH5_Manage_Object;
#endif
#if defined DMA_CH_6_TRIG
Struct_DMA_Manage_Object DMA_CH6_Manage_Object;
#endif
#if defined DMA_CH_7_TRIG
Struct_DMA_Manage_Object DMA_CH7_Manage_Object;
#endif
#endif

Struct_DMA_Manage_Object* DMA_Init(
    DMA_Regs *DMAx,
    uint8_t DMA_CH_CHAN_ID,
    uint32_t Src_Address,
    uint32_t Dest_Address,
    uint16_t Package_Size) {
#if defined DMA_BASE
    if (DMAx == DMA) {
#if defined DMA_CH_0_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_0_TRIG) {
            DMA_CH0_Manage_Object.DMA_Handler = DMA;
            DMA_CH0_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH0_Manage_Object.Src_Address = Src_Address;
            DMA_CH0_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH0_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH0_Manage_Object);
            return &DMA_CH0_Manage_Object;
        }
#endif
#if defined DMA_CH_1_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_1_TRIG) {
            DMA_CH1_Manage_Object.DMA_Handler = DMA;
            DMA_CH1_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH1_Manage_Object.Src_Address = Src_Address;
            DMA_CH1_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH1_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH1_Manage_Object);
            return &DMA_CH1_Manage_Object;
        }
#endif
#if defined DMA_CH_2_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_2_TRIG) {
            DMA_CH2_Manage_Object.DMA_Handler = DMA;
            DMA_CH2_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH2_Manage_Object.Src_Address = Src_Address;
            DMA_CH2_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH2_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH2_Manage_Object);
            return &DMA_CH2_Manage_Object;
        }
#endif
#if defined DMA_CH_3_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_3_TRIG) {
            DMA_CH3_Manage_Object.DMA_Handler = DMA;
            DMA_CH3_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH3_Manage_Object.Src_Address = Src_Address;
            DMA_CH3_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH3_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH3_Manage_Object);
            return &DMA_CH3_Manage_Object;
        }
#endif
#if defined DMA_CH_4_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_4_TRIG) {
            DMA_CH4_Manage_Object.DMA_Handler = DMA;
            DMA_CH4_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH4_Manage_Object.Src_Address = Src_Address;
            DMA_CH4_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH4_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH4_Manage_Object);
            return &DMA_CH4_Manage_Object;
        }
#endif
#if defined DMA_CH_5_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_5_TRIG) {
            DMA_CH5_Manage_Object.DMA_Handler = DMA;
            DMA_CH5_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH5_Manage_Object.Src_Address = Src_Address;
            DMA_CH5_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH5_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH5_Manage_Object);
            return &DMA_CH5_Manage_Object;
        }
#endif
#if defined DMA_CH_6_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_6_TRIG) {
            DMA_CH6_Manage_Object.DMA_Handler = DMA;
            DMA_CH6_Manage_Object.DMA_Channel = DMA_CH_CHAN_ID;
            DMA_CH6_Manage_Object.Src_Address = Src_Address;
            DMA_CH6_Manage_Object.Dest_Address = Dest_Address;
            DMA_CH6_Manage_Object.Package_Size = Package_Size;
            DMA_Config(&DMA_CH6_Manage_Object);
            return &DMA_CH6_Manage_Object;
        }
#endif
#if defined DMA_CH_7_TRIG
        if (DMA_CH_CHAN_ID == DMA_CH_7_TRIG) {
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
