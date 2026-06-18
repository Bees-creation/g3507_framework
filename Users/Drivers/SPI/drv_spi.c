/**
 * @brief SPI驱动
 * @date 2026/6/12
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "drv_spi.h"

#if defined SPI0
Struct_SPI_Manage_Object SPI0_Manage_Object = {0};
#endif
#if defined SPI1
Struct_SPI_Manage_Object SPI1_Manage_Object = {0};
#endif
#if defined SPI2
Struct_SPI_Manage_Object SPI2_Manage_Object = {0};
#endif
#if defined SPI3
Struct_SPI_Manage_Object SPI3_Manage_Object = {0};
#endif

void SPI_DMA_Init(SPI_INST *SPIx, DMA_INST *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID, GPIO_PORT *CS_Port, GPIO_PIN CS_Pin, uint8_t CS_Act, SPI_Callback Callback_Function) {
#if defined SPI0
    if (SPIx == SPI0) {
        SPI0_Manage_Object.SPI_Handler = SPIx;
        SPI0_Manage_Object.CS_Port = CS_Port;
        SPI0_Manage_Object.CS_Pin = CS_Pin;
        SPI0_Manage_Object.CS_Act = CS_Act;
        SPI0_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            SPI0_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&SPIx->RXDATA, (uint32_t)&SPI0_Manage_Object.Rx_Buffer, 0);
        }
        else {
            SPI0_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            SPI0_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&SPI0_Manage_Object.Tx_Buffer, (uint32_t)&SPIx->TXDATA, 0);
        }
        else {
            SPI0_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(SPI0_IT);
    }
#endif
#if defined SPI1
    if (SPIx == SPI1) {
        SPI1_Manage_Object.SPI_Handler = SPIx;
        SPI1_Manage_Object.CS_Port = CS_Port;
        SPI1_Manage_Object.CS_Pin = CS_Pin;
        SPI1_Manage_Object.CS_Act = CS_Act;
        SPI1_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            SPI1_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&SPIx->RXDATA, (uint32_t)&SPI1_Manage_Object.Rx_Buffer, 0);
        }
        else {
            SPI1_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            SPI1_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&SPI1_Manage_Object.Tx_Buffer, (uint32_t)&SPIx->TXDATA, 0);
        }
        else {
            SPI1_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(SPI1_IT);
    }
#endif
#if defined SPI2
    if (SPIx == SPI2) {
        SPI2_Manage_Object.SPI_Handler = SPIx;
        SPI2_Manage_Object.CS_Port = CS_Port;
        SPI2_Manage_Object.CS_Pin = CS_Pin;
        SPI2_Manage_Object.CS_Act = CS_Act;
        SPI2_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            SPI2_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&SPIx->RXDATA, (uint32_t)&SPI2_Manage_Object.Rx_Buffer, 0);
        }
        else {
            SPI2_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            SPI2_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&SPI2_Manage_Object.Tx_Buffer, (uint32_t)&SPIx->TXDATA, 0);
        }
        else {
            SPI2_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(SPI2_IT);
    }
#endif
#if defined SPI3
    if (SPIx == SPI3) {
        SPI3_Manage_Object.SPI_Handler = SPIx;
        SPI3_Manage_Object.CS_Port = CS_Port;
        SPI3_Manage_Object.CS_Pin = CS_Pin;
        SPI3_Manage_Object.CS_Act = CS_Act;
        SPI3_Manage_Object.Callback_Function = Callback_Function;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            SPI3_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&SPIx->RXDATA, (uint32_t)&SPI3_Manage_Object.Rx_Buffer, 0);
        }
        else {
            SPI3_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            SPI3_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&SPI3_Manage_Object.Tx_Buffer, (uint32_t)&SPIx->TXDATA, 0);
        }
        else {
            SPI3_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(SPI3_IT);
    }
#endif
}

void SPI_CS_Set(SPI_INST *SPIx, uint8_t status) {
#if defined SPI0
    if (SPIx == SPI0) {
        GPIO_Set_Pins(SPI0_Manage_Object.CS_Port, SPI0_Manage_Object.CS_Pin, status == STATUS_ENABLE ? SPI0_Manage_Object.CS_Act : !SPI0_Manage_Object.CS_Act);
    }
#endif
#if defined SPI1
    if (SPIx == SPI1) {
        GPIO_Set_Pins(SPI1_Manage_Object.CS_Port, SPI1_Manage_Object.CS_Pin, status == STATUS_ENABLE ? SPI1_Manage_Object.CS_Act : !SPI1_Manage_Object.CS_Act);
    }
#endif
#if defined SPI2
    if (SPIx == SPI2) {
        GPIO_Set_Pins(SPI2_Manage_Object.CS_Port, SPI2_Manage_Object.CS_Pin, status == STATUS_ENABLE ? SPI2_Manage_Object.CS_Act : !SPI2_Manage_Object.CS_Act);
    }
#endif
#if defined SPI3
    if (SPIx == SPI3) {
        GPIO_Set_Pins(SPI3_Manage_Object.CS_Port, SPI3_Manage_Object.CS_Pin, status == STATUS_ENABLE ? SPI3_Manage_Object.CS_Act : !SPI3_Manage_Object.CS_Act);
    }
#endif
}

uint8_t _SPI_Exchange_Blocking(SPI_INST *SPIx, uint8_t *TxData, uint8_t *RxData, uint16_t Length, uint16_t Timeout) {
    SPI_CS_Set(SPIx, STATUS_ENABLE);
    uint16_t pTx = 0, pRx = 0;
    while ((pTx < Length) && (pRx < Length)) {
        int time = 0;
        if ((pTx < Length) && (TxData != NULL)) {
            if (DL_SPI_transmitDataCheck8(SPIx, TxData[pTx])) {
                time = 0;
                pTx++;
            }
        }
        if ((pRx < Length) && (RxData != NULL)) {
            if (DL_SPI_receiveDataCheck8(SPIx, &RxData[pRx])) {
                time = 0;
                pRx++;
            }
        }
        while (DL_SPI_isBusy(SPIx)) {
            Sys_Delay(10);
            time += 10;
            if (time > Timeout) {
                SPI_CS_Set(SPIx, STATUS_DISABLE);
                return STATUS_ERROR;
            }
        }
    }
    SPI_CS_Set(SPIx, STATUS_DISABLE);
    return STATUS_DONE;
}

uint8_t SPI_Exchange_Data(SPI_INST *SPIx, uint8_t *TxData, uint8_t *RxData, uint16_t Length) {
    if (Length == 0U) {
        return STATUS_ERROR;
    }
    SPI_CS_Set(SPIx, STATUS_ENABLE);
    if (DL_SPI_isBusy(SPIx) == 0) {
#if defined SPI0
        if (SPIx == SPI0) {
            if (SPI0_Manage_Object.DMA_Tx_Manage_Object) {
                SPI0_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                if (RxData) {
                    SPI0_Manage_Object.Rx_Buffer = RxData;
                    SPI0_Manage_Object.Rx_Length = Length;
                    DMA_Receive_Data(SPI0_Manage_Object.DMA_Rx_Manage_Object, RxData, Length);
                }
                else {
                    SPI0_Manage_Object.Rx_Length = 0;
                }
                return DMA_Send_Data(SPI0_Manage_Object.DMA_Tx_Manage_Object, TxData, Length);
            }
        }
#endif
#if defined SPI1
        if (SPIx == SPI1) {
            if (SPI1_Manage_Object.DMA_Tx_Manage_Object) {
                SPI1_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                if (RxData) {
                    SPI1_Manage_Object.Rx_Buffer = RxData;
                    SPI1_Manage_Object.Rx_Length = Length;
                    DMA_Receive_Data(SPI1_Manage_Object.DMA_Rx_Manage_Object, RxData, Length);
                }
                else {
                    SPI1_Manage_Object.Rx_Length = 0;
                }
                return DMA_Send_Data(SPI1_Manage_Object.DMA_Tx_Manage_Object, TxData, Length);
            }
        }
#endif
#if defined SPI2
        if (SPIx == SPI2) {
            if (SPI2_Manage_Object.DMA_Tx_Manage_Object) {
                SPI2_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                if (RxData) {
                    SPI2_Manage_Object.Rx_Buffer = RxData;
                    SPI2_Manage_Object.Rx_Length = Length;
                    DMA_Receive_Data(SPI2_Manage_Object.DMA_Rx_Manage_Object, RxData, Length);
                }
                else {
                    SPI2_Manage_Object.Rx_Length = 0;
                }
                return DMA_Send_Data(SPI2_Manage_Object.DMA_Tx_Manage_Object, TxData, Length);
            }
        }
#endif
#if defined SPI3
        if (SPIx == SPI3) {
            if (SPI3_Manage_Object.DMA_Tx_Manage_Object) {
                SPI3_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                if (RxData) {
                    SPI3_Manage_Object.Rx_Buffer = RxData;
                    SPI3_Manage_Object.Rx_Length = Length;
                    DMA_Receive_Data(SPI3_Manage_Object.DMA_Rx_Manage_Object, RxData, Length);
                }
                else {
                    SPI3_Manage_Object.Rx_Length = 0;
                }
                return DMA_Send_Data(SPI3_Manage_Object.DMA_Tx_Manage_Object, TxData, Length);
            }
        }
#endif
    }
    else {
        return STATUS_BUSY;
    }
    return _SPI_Exchange_Blocking(SPIx, TxData, RxData, Length, 20000);
}

__WEAK void SPI_IRQHandler(SPI_INST *SPIx) {
#if defined SPI0
    if (SPIx == SPI0) {
        switch (DL_SPI_getPendingInterrupt(SPI0)) {
            case DL_SPI_IIDX_DMA_DONE_TX:
                SPI0_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                break;
            case DL_SPI_IIDX_TX_EMPTY:
                if (SPI0_Manage_Object.Rx_Length) {
                    break;
                }
            case DL_SPI_IIDX_DMA_DONE_RX: {
                uint8_t timeout = 20;
                SPI0_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
                SPI0_Manage_Object.Callback_Function(SPI0_Manage_Object.Rx_Buffer, SPI0_Manage_Object.Rx_Length);
                while (DL_SPI_isBusy(SPIx) != 0 && --timeout) {
                    Sys_Delay(1);
                }
                SPI_CS_Set(SPIx, STATUS_DISABLE);
                break;
            }
            default:
                break;
        }
    }
#endif
#if defined SPI1
    if (SPIx == SPI1) {
        switch (DL_SPI_getPendingInterrupt(SPI1)) {
            case DL_SPI_IIDX_DMA_DONE_TX:
                SPI1_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                break;
            case DL_SPI_IIDX_TX_EMPTY:
                if (SPI1_Manage_Object.Rx_Length) {
                    break;
                }
            case DL_SPI_IIDX_DMA_DONE_RX: {
                uint32_t timeout = 20;
                SPI1_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
                SPI1_Manage_Object.Callback_Function(SPI1_Manage_Object.Rx_Buffer, SPI1_Manage_Object.Rx_Length);
                while (DL_SPI_isBusy(SPIx) != 0 && --timeout) {
                    Sys_Delay(1);
                }
                SPI_CS_Set(SPIx, STATUS_DISABLE);
                break;
            }
            default:
                break;
        }
    }
#endif
#if defined SPI2
    if (SPIx == SPI2) {
        switch (DL_SPI_getPendingInterrupt(SPI2)) {
            case DL_SPI_IIDX_DMA_DONE_TX:
                SPI2_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                break;
            case DL_SPI_IIDX_TX_EMPTY:
                if (SPI2_Manage_Object.Rx_Length) {
                    break;
                }
            case DL_SPI_IIDX_DMA_DONE_RX: {
                uint32_t timeout = 20;
                SPI2_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
                SPI2_Manage_Object.Callback_Function(SPI2_Manage_Object.Rx_Buffer, SPI2_Manage_Object.Rx_Length);
                while (DL_SPI_isBusy(SPIx) != 0 && --timeout) {
                    Sys_Delay(1);
                }
                SPI_CS_Set(SPIx, STATUS_DISABLE);
                break;
            }
            default:
                break;
        }
    }
#endif
#if defined SPI3
    if (SPIx == SPI3) {
        switch (DL_SPI_getPendingInterrupt(SPI3)) {
            case DL_SPI_IIDX_DMA_DONE_TX:
                SPI3_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                break;
            case DL_SPI_IIDX_TX_EMPTY:
                if (SPI3_Manage_Object.Rx_Length) {
                    break;
                }
            case DL_SPI_IIDX_DMA_DONE_RX: {
                uint32_t timeout = 1020;
                SPI3_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
                SPI3_Manage_Object.Callback_Function(SPI3_Manage_Object.Rx_Buffer, SPI3_Manage_Object.Rx_Length);
                while (DL_SPI_isBusy(SPIx) != 0 && --timeout) {
                    Sys_Delay(1);
                }
                SPI_CS_Set(SPIx, STATUS_DISABLE);
                break;
            }
            default:
                break;
        }
    }
#endif
}

#if defined SPI0
void SPI0_IRQHandler() {
    SPI_IRQHandler(SPI0);
}
#endif
#if defined SPI1
void SPI1_IRQHandler() {
    SPI_IRQHandler(SPI1);
}
#endif
#if defined SPI2
void SPI2_IRQHandler() {
    SPI_IRQHandler(SPI2);
}
#endif
#if defined SPI3
void SPI3_IRQHandler() {
    SPI_IRQHandler(SPI3);
}
#endif
