/**
 * @brief 串口驱动
 * @date 2026/5/16
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "drv_uart.h"

#if defined UART0
Struct_UART_Manage_Object UART0_Manage_Object = {0};
#endif
#if defined UART1
Struct_UART_Manage_Object UART1_Manage_Object = {0};
#endif
#if defined UART2
Struct_UART_Manage_Object UART2_Manage_Object = {0};
#endif
#if defined UART3
Struct_UART_Manage_Object UART3_Manage_Object = {0};
#endif
#if defined UART4
Struct_UART_Manage_Object UART4_Manage_Object = {0};
#endif
#if defined UART5
Struct_UART_Manage_Object UART5_Manage_Object = {0};
#endif
#if defined UART6
Struct_UART_Manage_Object UART6_Manage_Object = {0};
#endif
#if defined UART7
Struct_UART_Manage_Object UART7_Manage_Object = {0};
#endif

void UART_DMA_Init(
    UART_Regs *UARTx, UART_Callback Callback_Function, uint16_t Rx_Buffer_Length,
    DMA_Regs *DMAx, int8_t DMA_Rx_CH_CHAN_ID, int8_t DMA_Tx_CH_CHAN_ID) {
#if defined UART0
    if (UARTx == UART0) {
        UART0_Manage_Object.UART_Handler = UARTx;
        UART0_Manage_Object.Callback_Function = Callback_Function;
        UART0_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART0_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART0_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART0_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART0_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART0_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART0_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART0_IT);
    }
#endif
#if defined UART1
    if (UARTx == UART1) {
        UART1_Manage_Object.UART_Handler = UARTx;
        UART1_Manage_Object.Callback_Function = Callback_Function;
        UART1_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART1_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART1_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART1_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART1_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART1_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART1_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART1_IT);
    }
#endif
#if defined UART2
    if (UARTx == UART2) {
        UART2_Manage_Object.UART_Handler = UARTx;
        UART2_Manage_Object.Callback_Function = Callback_Function;
        UART2_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART2_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART2_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART2_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART2_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART2_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART2_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART2_IT);
    }
#endif
#if defined UART3
    if (UARTx == UART3) {
        UART3_Manage_Object.UART_Handler = UARTx;
        UART3_Manage_Object.Callback_Function = Callback_Function;
        UART3_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART3_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART3_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART3_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART3_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART3_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART3_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART3_IT);
    }
#endif
#if defined UART4
    if (UARTx == UART4) {
        UART4_Manage_Object.UART_Handler = UARTx;
        UART4_Manage_Object.Callback_Function = Callback_Function;
        UART4_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART4_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART4_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART4_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART4_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART4_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART4_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART4_IT);
    }
#endif
#if defined UART5
    if (UARTx == UART5) {
        UART5_Manage_Object.UART_Handler = UARTx;
        UART5_Manage_Object.Callback_Function = Callback_Function;
        UART5_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART5_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART5_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART5_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART5_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART5_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART5_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART5_IT);
    }
#endif
#if defined UART6
    if (UARTx == UART6) {
        UART6_Manage_Object.UART_Handler = UARTx;
        UART6_Manage_Object.Callback_Function = Callback_Function;
        UART6_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Rx_CH_CHAN_ID != -1) {
            UART6_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART6_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART6_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART6_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART6_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART6_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART6_IT);
    }
#endif
#if defined UART7
    if (UARTx == UART7) {
        UART7_Manage_Object.UART_Handler = UARTx;
        UART7_Manage_Object.Callback_Function = Callback_Function;
        UART7_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART7_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART7_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        } else {
            UART7_Manage_Object.DMA_Rx_Manage_Object = NULL;
        }
        if (DMA_Tx_CH_CHAN_ID != -1) {
            UART7_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART7_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        } else {
            UART7_Manage_Object.DMA_Tx_Manage_Object = NULL;
        }
        NVIC_Enable_IT(UART7_IT);
    }
#endif
}

uint8_t _UART_Send_Blocking(UART_Regs *UARTx, uint8_t *pData, uint16_t Length, uint16_t Timeout) {
    int time = 0;
    for (int i = 0; i < Length; i++) {
        time = 0;
        while (!DL_UART_transmitDataCheck(UARTx, pData[i])) {
            Sys_Delay(10);
            time+=10;
            if (time > Timeout) {
                return STATUS_ERROR;
            }
        }
    }
    return STATUS_DONE;
}

uint8_t UART_Send_Data(UART_Regs *UARTx, uint8_t *pData, uint16_t Length) {
    if ((pData == NULL) || (Length == 0U)) {
        return STATUS_ERROR;
    }
    if ((UARTx->STAT & (STAT_TXFF | STAT_BUSY)) == 0) {
#if defined UART0
        if (UARTx == UART0) {
            if (UART0_Manage_Object.DMA_Tx_Manage_Object) {
                UART0_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART0_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART1
        if (UARTx == UART1) {
            if (UART1_Manage_Object.DMA_Tx_Manage_Object) {
                UART1_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART1_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART2
        if (UARTx == UART2) {
            if (UART2_Manage_Object.DMA_Tx_Manage_Object) {
                UART2_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART2_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART3
        if (UARTx == UART3) {
            if (UART3_Manage_Object.DMA_Tx_Manage_Object) {
                UART3_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART3_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART4
        if (UARTx == UART4) {
            if (UART4_Manage_Object.DMA_Tx_Manage_Object) {
                UART4_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART4_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART5
        if (UARTx == UART5) {
            if (UART5_Manage_Object.DMA_Tx_Manage_Object) {
                UART5_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART5_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART6
        if (UARTx == UART6) {
            if (UART6_Manage_Object.DMA_Tx_Manage_Object) {
                UART6_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART6_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
#if defined UART7
        if (UARTx == UART7) {
            if (UART7_Manage_Object.DMA_Tx_Manage_Object) {
                UART7_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
                return DMA_Send_Data(UART7_Manage_Object.DMA_Tx_Manage_Object, pData, Length);
            }
        }
#endif
    }
    else {
        return STATUS_BUSY;
    }
    return _UART_Send_Blocking(UARTx, pData, Length, 20000);
}

uint8_t _UART_Receive_Blocking(UART_Regs *UARTx, uint8_t *pData, uint16_t Length, uint16_t Timeout) {
    int time = 0;
    for (int i = 0; i < Length; i++) {
        time = 0;
        while (!DL_UART_receiveDataCheck(UARTx, &pData[i])) {
            Sys_Delay(10);
            time+=10;
            if (time > Timeout) {
                return STATUS_ERROR;
            }
        }
    }
    return STATUS_DONE;
}

uint8_t UART_Receive_Data(UART_Regs *UARTx, uint8_t *pData, uint16_t Length) {
    if ((pData == NULL) || (Length == 0U)) {
        return STATUS_ERROR;
    }
#if defined UART0
    if (UARTx == UART0) {
        if (UART0_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART0_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART1
    if (UARTx == UART1) {
        if (UART1_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART1_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART2
    if (UARTx == UART2) {
        if (UART2_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART2_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART3
    if (UARTx == UART3) {
        if (UART3_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART3_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART4
    if (UARTx == UART4) {
        if (UART4_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART4_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART5
    if (UARTx == UART5) {
        if (UART5_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART5_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART6
    if (UARTx == UART6) {
        if (UART6_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART6_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
#if defined UART7
    if (UARTx == UART7) {
        if (UART7_Manage_Object.DMA_Rx_Manage_Object) {
            return DMA_Receive_Data(UART7_Manage_Object.DMA_Rx_Manage_Object, pData, Length);
        }
    }
#endif
    return _UART_Receive_Blocking(UARTx, pData, Length, 20000);
}

__WEAK void UART_IRQHandler(UART_Regs *UARTx) {
#if defined UART0
    if (UARTx == UART0) {
        switch (DL_UART_Main_getPendingInterrupt(UART0)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART0_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART0_Manage_Object.Callback_Function(UART0_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART1
    if (UARTx == UART1) {
        switch (DL_UART_Main_getPendingInterrupt(UART1)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART1_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART1_Manage_Object.Callback_Function(UART1_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART2
    if (UARTx == UART2) {
        switch (DL_UART_Main_getPendingInterrupt(UART2)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART2_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART2_Manage_Object.Callback_Function(UART2_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART3
    if (UARTx == UART3) {
        switch (DL_UART_Main_getPendingInterrupt(UART3)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART3_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART3_Manage_Object.Callback_Function(UART3_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART4
    if (UARTx == UART4) {
        switch (DL_UART_Main_getPendingInterrupt(UART4)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART4_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART4_Manage_Object.Callback_Function(UART4_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART5
    if (UARTx == UART5) {
        switch (DL_UART_Main_getPendingInterrupt(UART5)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART5_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART5_Manage_Object.Callback_Function(UART5_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART6
    if (UARTx == UART6) {
        switch (DL_UART_Main_getPendingInterrupt(UART6)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART6_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART6_Manage_Object.Callback_Function(UART6_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
#if defined UART7
    if (UARTx == UART7) {
        switch (DL_UART_Main_getPendingInterrupt(UART7)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART7_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
            case DL_UART_IIDX_RX:
                UART7_Manage_Object.Callback_Function(UART7_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }
#endif
}

#if defined UART0
void UART0_IRQHandler() {
    UART_IRQHandler(UART0);
}
#endif
#if defined UART1
void UART1_IRQHandler() {
    UART_IRQHandler(UART1);
}
#endif
#if defined UART2
void UART2_IRQHandler() {
    UART_IRQHandler(UART2);
}
#endif
#if defined UART3
void UART3_IRQHandler() {
    UART_IRQHandler(UART3);
}
#endif
#if defined UART4
void UART4_IRQHandler() {
    UART_IRQHandler(UART4);
}
#endif
#if defined UART5
void UART5_IRQHandler() {
    UART_IRQHandler(UART5);
}
#endif
#if defined UART6
void UART6_IRQHandler() {
    UART_IRQHandler(UART6);
}
#endif
#if defined UART7
void UART7_IRQHandler() {
    UART_IRQHandler(UART7);
}
#endif
