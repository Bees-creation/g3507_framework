/**
 * @brief I2C驱动
 * @date 2026/7/30
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "Drivers/I2C/drv_i2c.h"

#if defined I2C0_BASE
#define I2C0 I2C0
Struct_I2C_Manage_Object I2C0_Manage_Object;
#endif
#if defined I2C1_BASE
#define I2C1 I2C1
Struct_I2C_Manage_Object I2C1_Manage_Object;
#endif
#if defined I2C2_BASE
#define I2C2 I2C2
Struct_I2C_Manage_Object I2C2_Manage_Object;
#endif
#if defined I2C3_BASE
#define I2C3 I2C3
Struct_I2C_Manage_Object I2C3_Manage_Object;
#endif

void I2C_DMA_Init(
    I2C_INST *I2Cx, DMA_INST *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID, I2C_Callback Callback_Function) {
#if defined I2C0
    if (I2Cx == I2C0) {
        I2C0_Manage_Object.I2C_Handler = I2Cx;
        I2C0_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            I2C0_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&I2Cx->MASTER.MRXDATA, (uint32_t)&I2C0_Manage_Object.Rx_Buffer, 0);
        }
        else {
            I2C0_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            I2C0_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&I2C0_Manage_Object.Tx_Buffer, (uint32_t)&I2Cx->MASTER.MTXDATA, 0);
        }
        else {
            I2C0_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(I2C0_IT);
    }
#endif
#if defined I2C1
    if (I2Cx == I2C1) {
        I2C1_Manage_Object.I2C_Handler = I2Cx;
        I2C1_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            I2C1_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&I2Cx->MASTER.MRXDATA, (uint32_t)&I2C1_Manage_Object.Rx_Buffer, 0);
        }
        else {
            I2C1_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            I2C1_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&I2C1_Manage_Object.Tx_Buffer, (uint32_t)&I2Cx->MASTER.MTXDATA, 0);
        }
        else {
            I2C1_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(I2C1_IT);
    }
#endif
#if defined I2C2
    if (I2Cx == I2C2) {
        I2C2_Manage_Object.I2C_Handler = I2Cx;
        I2C2_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            I2C2_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&I2Cx->MASTER.MRXDATA, (uint32_t)&I2C2_Manage_Object.Rx_Buffer, 0);
        }
        else {
            I2C2_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            I2C2_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&I2C2_Manage_Object.Tx_Buffer, (uint32_t)&I2Cx->MASTER.MTXDATA, 0);
        }
        else {
            I2C2_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(I2C2_IT);
    }
#endif
#if defined I2C3
    if (I2Cx == I2C3) {
        I2C3_Manage_Object.I2C_Handler = I2Cx;
        I2C3_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            I2C3_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&I2Cx->MASTER.MRXDATA, (uint32_t)&I2C3_Manage_Object.Rx_Buffer, 0);
        }
        else {
            I2C3_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            I2C3_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&I2C3_Manage_Object.Tx_Buffer, (uint32_t)&I2Cx->MASTER.MTXDATA, 0);
        }
        else {
            I2C3_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(I2C3_IT);
    }
#endif
}

uint8_t _I2C_Send_Blocking(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length, uint16_t Timeout) {
    int time = 0;
    // I2C自动启止时序
    DL_I2C_startControllerTransfer(I2Cx, Addr, DL_I2C_CONTROLLER_DIRECTION_TX, Length);
    for (int i = 0; i < Length; ) {
        // 超时检测
        time = 0;
        while (DL_I2C_isControllerTXFIFOFull(I2Cx)) {
            Sys_Delay(10);
            time += 10;
            if (time > Timeout) {
                return STATUS_ERROR;
            }
        }
        // FIFO填充
        if ((Length - i) > I2C_FIFO_DEPTH) {
            uint8_t bytes = DL_I2C_fillControllerTXFIFO(I2Cx, &pData[i], I2C_FIFO_DEPTH);
            i += bytes;
        }
        else {
            uint8_t bytes = DL_I2C_fillControllerTXFIFO(I2Cx, &pData[i], (Length - i));
            i += bytes;
        }
    }
    // 等待所有数据发送完毕
    time = 0;
    while (!(DL_I2C_getControllerStatus(I2Cx) & DL_I2C_CONTROLLER_STATUS_IDLE)) {
        Sys_Delay(10);
        time += 10;
        if (time > Timeout) {
            return STATUS_ERROR;
        }
    }
    return STATUS_DONE;
}

uint8_t _I2C_Receive_Blocking(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length, uint16_t Timeout) {
    int time = 0;
    // I2C自动启止时序
    DL_I2C_startControllerTransfer(I2Cx, Addr, DL_I2C_CONTROLLER_DIRECTION_RX, Length);
    for (int i = 0; i < Length; ) {
        // 超时检测
        time = 0;
        while (DL_I2C_isControllerRXFIFOEmpty(I2Cx)) {
            Sys_Delay(10);
            time += 10;
            if (time > Timeout) {
                return STATUS_ERROR;
            }
        }
        // FIFO读取
        while (!DL_I2C_isControllerRXFIFOEmpty(I2Cx) && (i < Length)) {
            pData[i++] = DL_I2C_receiveControllerData(I2Cx);
        }
    }
    // 等待所有数据接收完毕
    time = 0;
    while (!(DL_I2C_getControllerStatus(I2Cx) & DL_I2C_CONTROLLER_STATUS_IDLE)) {
        Sys_Delay(10);
        time += 10;
        if (time > Timeout) {
            return STATUS_ERROR;
        }
    }
    return STATUS_DONE;
}

uint8_t I2C_Send_Data(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length) {
    if ((pData == NULL) || (Length == 0U)) {
        return STATUS_ERROR;
    }
    if (DL_I2C_getControllerStatus(I2Cx) & DL_I2C_CONTROLLER_STATUS_IDLE) {
        uint8_t status = STATUS_BUSY;
#if defined I2C0
        if (I2Cx == I2C0) {
            if (I2C0_Manage_Object.DMA_Tx_Manage_Object) {
                I2C0_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                status = DMA_Send_Data(I2C0_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined I2C1
        if (I2Cx == I2C1) {
            if (I2C1_Manage_Object.DMA_Tx_Manage_Object) {
                I2C1_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                status = DMA_Send_Data(I2C1_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined I2C2
        if (I2Cx == I2C2) {
            if (I2C2_Manage_Object.DMA_Tx_Manage_Object) {
                I2C2_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                status = DMA_Send_Data(I2C2_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined I2C3
        if (I2Cx == I2C3) {
            if (I2C3_Manage_Object.DMA_Tx_Manage_Object) {
                I2C3_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                status = DMA_Send_Data(I2C3_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
        if (status == STATUS_DONE) {
            DL_I2C_startControllerTransfer(I2Cx, Addr, DL_I2C_CONTROLLER_DIRECTION_TX, Length);
            return STATUS_DONE;
        }
    }
    else {
        return STATUS_BUSY;
    }
    return _I2C_Send_Blocking(I2Cx, Addr, pData, Length, 20000);
}

uint8_t I2C_Receive_Data(I2C_INST *I2Cx, uint8_t Addr, uint8_t *pData, uint16_t Length) {
    if ((pData == NULL) || (Length == 0U)) {
        return STATUS_ERROR;
    }
    if (DL_I2C_getControllerStatus(I2Cx) & DL_I2C_CONTROLLER_STATUS_IDLE) {
        uint8_t status = STATUS_BUSY;
#if defined I2C0
    if (I2Cx == I2C0) {
        if (I2C0_Manage_Object.DMA_Rx_Manage_Object) {
            status = DMA_Receive_Data(I2C0_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined I2C1
    if (I2Cx == I2C1) {
        if (I2C1_Manage_Object.DMA_Rx_Manage_Object) {
            status = DMA_Receive_Data(I2C1_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined I2C2
    if (I2Cx == I2C2) {
        if (I2C2_Manage_Object.DMA_Rx_Manage_Object) {
            status = DMA_Receive_Data(I2C2_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined I2C3
    if (I2Cx == I2C3) {
        if (I2C3_Manage_Object.DMA_Rx_Manage_Object) {
            status = DMA_Receive_Data(I2C3_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
        if (status == STATUS_DONE) {
            DL_I2C_startControllerTransfer(I2Cx, Addr, DL_I2C_CONTROLLER_DIRECTION_RX, Length);
            return STATUS_DONE;
        }
    }
    else {
        return STATUS_BUSY;
    }
    return _I2C_Receive_Blocking(I2Cx, Addr, pData, Length, 20000);
}

__WEAK void I2C_IRQHandler(I2C_INST *I2Cx) {
#if defined I2C0
    if (I2Cx == I2C0) {
        switch (DL_I2C_getPendingInterrupt(I2C0)) {
            case DL_I2C_IIDX_TARGET_EVENT2_DMA_DONE:
                I2C0_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_I2C_IIDX_TARGET_RX_DONE:
                I2C0_Manage_Object.Callback_Function(I2C0_Manage_Object.Rx_Buffer, I2C0_Manage_Object.Rx_Length);
                break;
            default:
                break;
        }
    }
#endif
#if defined I2C1
    if (I2Cx == I2C1) {
        switch (DL_I2C_getPendingInterrupt(I2C1)) {
            case DL_I2C_IIDX_TARGET_EVENT2_DMA_DONE:
                I2C1_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_I2C_IIDX_TARGET_RX_DONE:
                I2C1_Manage_Object.Callback_Function(I2C1_Manage_Object.Rx_Buffer, I2C1_Manage_Object.Rx_Length);
                break;
            default:
                break;
        }
    }
#endif
#if defined I2C2
    if (I2Cx == I2C2) {
        switch (DL_I2C_getPendingInterrupt(I2C2)) {
            case DL_I2C_IIDX_TARGET_EVENT2_DMA_DONE:
                I2C2_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_I2C_IIDX_TARGET_RX_DONE:
                I2C2_Manage_Object.Callback_Function(I2C2_Manage_Object.Rx_Buffer, I2C2_Manage_Object.Rx_Buffer);
                break;
            default:
                break;
        }
    }
#endif
#if defined I2C3
    if (I2Cx == I2C3) {
        switch (DL_I2C_getPendingInterrupt(I2C3)) {
            case DL_I2C_IIDX_TARGET_EVENT2_DMA_DONE:
                I2C3_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_I2C_IIDX_TARGET_RX_DONE:
                I2C3_Manage_Object.Callback_Function(I2C3_Manage_Object.Rx_Buffer, I2C3_Manage_Object.Rx_Buffer);
                break;
            default:
                break;
        }
    }
#endif
}

#if defined I2C0
void I2C0_IRQHandler() {
    I2C_IRQHandler(I2C0);
}
#endif
#if defined I2C1
void I2C1_IRQHandler() {
    I2C_IRQHandler(I2C1);
}
#endif
#if defined I2C2
void I2C2_IRQHandler() {
    I2C_IRQHandler(I2C2);
}
#endif
#if defined I2C3
void I2C3_IRQHandler() {
    I2C_IRQHandler(I2C3);
}
#endif
