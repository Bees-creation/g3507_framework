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
    DMA_Regs *DMAx, uint8_t DMA_Rx_CH_CHAN_ID, uint8_t DMA_Tx_CH_CHAN_ID) {
#if defined UART0
    if (UARTx == UART0) {
        UART0_Manage_Object.UART_Handler = UARTx;
        UART0_Manage_Object.Callback_Function = Callback_Function;
        UART0_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART0_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART0_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART0_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART0_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART0_IT);
    }
#endif
#if defined UART1
    if (UARTx == UART1) {
        UART1_Manage_Object.UART_Handler = UARTx;
        UART1_Manage_Object.Callback_Function = Callback_Function;
        UART1_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART1_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART1_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART1_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART1_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART1_IT);
    }
#endif
#if defined UART2
    if (UARTx == UART2) {
        UART2_Manage_Object.UART_Handler = UARTx;
        UART2_Manage_Object.Callback_Function = Callback_Function;
        UART2_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART2_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART2_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART2_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART2_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART2_IT);
    }
#endif
#if defined UART3
    if (UARTx == UART3) {
        UART3_Manage_Object.UART_Handler = UARTx;
        UART3_Manage_Object.Callback_Function = Callback_Function;
        UART3_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART3_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART3_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART3_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART3_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART3_IT);
    }
#endif
#if defined UART4
    if (UARTx == UART4) {
        UART4_Manage_Object.UART_Handler = UARTx;
        UART4_Manage_Object.Callback_Function = Callback_Function;
        UART4_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART4_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART4_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART4_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART4_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART4_IT);
    }
#endif
#if defined UART5
    if (UARTx == UART5) {
        UART5_Manage_Object.UART_Handler = UARTx;
        UART5_Manage_Object.Callback_Function = Callback_Function;
        UART5_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART5_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART5_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART5_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART5_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART5_IT);
    }
#endif
#if defined UART6
    if (UARTx == UART6) {
        UART6_Manage_Object.UART_Handler = UARTx;
        UART6_Manage_Object.Callback_Function = Callback_Function;
        UART6_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART6_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART6_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART6_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART6_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART6_IT);
    }
#endif
#if defined UART7
    if (UARTx == UART7) {
        UART7_Manage_Object.UART_Handler = UARTx;
        UART7_Manage_Object.Callback_Function = Callback_Function;
        UART7_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        UART7_Manage_Object.DMA_Rx_Manage_Object = DMA_Init(DMAx, DMA_Rx_CH_CHAN_ID, (uint32_t)&UARTx->RXDATA, (uint32_t)&UART7_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
        UART7_Manage_Object.DMA_Tx_Manage_Object = DMA_Init(DMAx, DMA_Tx_CH_CHAN_ID, (uint32_t)&UART7_Manage_Object.Tx_Buffer, (uint32_t)&UARTx->TXDATA, UART_BUFFER_SIZE);
        NVIC_Enable_IT(UART7_IT);
    }
#endif
}

uint8_t UART_Send_Data(UART_Regs *UARTx, uint8_t *pData, uint16_t Size) {
    if ((pData == NULL) || (Size == 0U)) {
        return STATUS_ERROR;
    }
    if ((UARTx->STAT & (STAT_TXFF | STAT_BUSY)) == 0) {
        UART0_Manage_Object.DMA_Tx_Manage_Object->Busy = STATUS_READY;
#if defined UART0
        if (UARTx == UART0) {
            return DMA_Send_Data(UART0_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART1
        if (UARTx == UART1) {
            return DMA_Send_Data(UART1_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART2
        if (UARTx == UART2) {
            return DMA_Send_Data(UART2_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART3
        if (UARTx == UART3) {
            return DMA_Send_Data(UART3_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART4
        if (UARTx == UART4) {
            return DMA_Send_Data(UART4_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART5
        if (UARTx == UART5) {
            return DMA_Send_Data(UART5_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART6
        if (UARTx == UART6) {
            return DMA_Send_Data(UART6_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
#if defined UART7
        if (UARTx == UART7) {
            return DMA_Send_Data(UART7_Manage_Object.DMA_Tx_Manage_Object, pData, Size);
        }
#endif
    }
    else {
        return STATUS_BUSY;
    }
    return STATUS_ERROR;
}

uint8_t UART_DMA_Receive(UART_Regs *UARTx, uint8_t *pData, uint16_t Size) {
    if ((pData == NULL) || (Size == 0U)) {
        return STATUS_ERROR;
    }
    if ((UARTx->STAT & (STAT_RXFF | STAT_BUSY)) == 0) {
#if defined UART0
        if (UARTx == UART0) {
            return DMA_Receive_Data(UART0_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART1
        if (UARTx == UART1) {
            return DMA_Receive_Data(UART1_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART2
        if (UARTx == UART2) {
            return DMA_Receive_Data(UART2_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART3
        if (UARTx == UART3) {
            return DMA_Receive_Data(UART3_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART4
        if (UARTx == UART4) {
            return DMA_Receive_Data(UART4_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART5
        if (UARTx == UART5) {
            return DMA_Receive_Data(UART5_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART6
        if (UARTx == UART6) {
            return DMA_Receive_Data(UART6_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
#if defined UART7
        if (UARTx == UART7) {
            return DMA_Receive_Data(UART7_Manage_Object.DMA_Rx_Manage_Object, pData, Size);
        }
#endif
    }
    else {
        return STATUS_BUSY;
    }
    return STATUS_DONE;
}

__WEAK void UART_IRQHandler(UART_Regs *UARTx) {
#if defined UART0
    if (UARTx == UART0) {
        switch (DL_UART_Main_getPendingInterrupt(UART0)) {
            case DL_UART_MAIN_IIDX_DMA_DONE_RX:
                UART0_Manage_Object.Callback_Function(UART0_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART0_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART1_Manage_Object.Callback_Function(UART1_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART1_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART2_Manage_Object.Callback_Function(UART2_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART2_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART3_Manage_Object.Callback_Function(UART3_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART3_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART4_Manage_Object.Callback_Function(UART4_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART4_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART5_Manage_Object.Callback_Function(UART5_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART5_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART6_Manage_Object.Callback_Function(UART6_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART6_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
                UART7_Manage_Object.Callback_Function(UART7_Manage_Object.Rx_Buffer, UART_BUFFER_SIZE);
                UART7_Manage_Object.DMA_Rx_Manage_Object->Busy = STATUS_READY;
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
