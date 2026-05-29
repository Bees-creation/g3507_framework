/**
 * @brief 串口调试信息
 * @date 2026/5/19
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_serialport.h"

void Class_Serialport::Init(UART_Regs *UARTx, uint8_t __Serialport_Rx_Variable_Assignment_Num, const char **__Serialport_Rx_Variable_Assignment_List, Enum_Serialport_Data_Type __Serialport_Tx_Data_Type, uint8_t __Frame_Header, uint8_t __Frame_Trailer) {
#if defined UART0
    if (UARTx == UART0) {
        UART_Manage_Object = &UART0_Manage_Object;
    }
#endif
#if defined UART1
    else if (UARTx == UART1) {
        UART_Manage_Object = &UART1_Manage_Object;
    }
#endif
#if defined UART2
    else if (UARTx == UART2) {
        UART_Manage_Object = &UART2_Manage_Object;
    }
#endif
#if defined UART3
    else if (UARTx == UART3) {
        UART_Manage_Object = &UART3_Manage_Object;
    }
#endif
#if defined UART4
    else if (UARTx == UART4) {
        UART_Manage_Object = &UART4_Manage_Object;
    }
#endif
#if defined UART5
    else if (UARTx == UART5) {
        UART_Manage_Object = &UART5_Manage_Object;
    }
#endif
#if defined UART6
    else if (UARTx == UART6) {
        UART_Manage_Object = &UART6_Manage_Object;
    }
#endif
#if defined UART7
    else if (UARTx == UART7) {
        UART_Manage_Object = &UART7_Manage_Object;
    }
#endif

    UART_Rx_Variable_Num = __Serialport_Rx_Variable_Assignment_Num;
    UART_Rx_Variable_List = __Serialport_Rx_Variable_Assignment_List;
    UART_Tx_Data_Type = __Serialport_Tx_Data_Type;
    Frame_Header = __Frame_Header;
    Frame_Trailer = __Frame_Trailer;

    // 开启DMA接收
    UART_DMA_Receive(UARTx, UART_Manage_Object->Rx_Buffer, UART_BUFFER_SIZE);
}

int8_t Class_Serialport::Get_Variable_Index() {
    return (Variable_Index);
}

double Class_Serialport::Get_Variable_Value() {
    return (Variable_Value);
}

void Class_Serialport::Set_Data(uint8_t Number, ...) {
    va_list data_ptr;
    va_start(data_ptr, Number);
    for (int i = 0; i < Number; i++) {
        Data[i] = (void *)va_arg(data_ptr, int);
    }
    va_end(data_ptr);
    Data_Number = Number;
}

void Class_Serialport::UART_RxCpltCallback(void) {
    int flag;
    flag = Judge_Variable_Name();
    Judge_Variable_Value(flag);
}

void Class_Serialport::TIM_Write_PeriodElapsedCallback() {
    Output();
    Send();
}

void Class_Serialport::TIM_Read_PeriodElapsedCallback() {
    UART_Manage_Object->Callback_Function(UART_Manage_Object->Rx_Buffer, UART_Manage_Object->Rx_Buffer_Length);
    UART_Manage_Object->DMA_Rx_Manage_Object->Busy = STATUS_READY;
}

uint8_t Class_Serialport::Judge_Variable_Name() {
    // 临时存储变量名
    char tmp_variable_name[SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH];
    // 等号位置标记
    int flag;

    // 记录变量名并标记等号位置
    for (flag = 0; UART_Manage_Object->Rx_Buffer[flag] != '=' && UART_Manage_Object->Rx_Buffer[flag] != 0; flag++) {
        tmp_variable_name[flag] = UART_Manage_Object->Rx_Buffer[flag];
    }
    tmp_variable_name[flag] = 0;

    // 比对是否在列表中
    for (int i = 0; i < UART_Rx_Variable_Num; i++) {
        // 如果在则标记变量名编号
        if (strcmp(tmp_variable_name, (char *)((int)UART_Rx_Variable_List + SERIALPORT_RX_VARIABLE_ASSIGNMENT_LENGTH * i)) == 0) {
            Variable_Index = i;
            return (flag + 1);
        }
    }
    // 如果变量名不在则-1
    Variable_Index = -1;
    return (flag + 1);
}

void Class_Serialport::Judge_Variable_Value(int flag) {
    // 小数点位置, 是否有负号
    int tmp_dot_flag, tmp_sign_coefficient, i;

    tmp_dot_flag = 0;
    tmp_sign_coefficient = 1;
    Variable_Value = 0.0f;

    // 列表里没有, 没必要比对直接返回
    if (Variable_Index == -1) {
        return;
    }

    // 判断是否有负号
    if (UART_Manage_Object->Rx_Buffer[flag] == '-') {
        tmp_sign_coefficient = -1;
        flag++;
    }

    // 计算值并注意小数点是否存在及其位置
    for (i = flag; UART_Manage_Object->Rx_Buffer[i] != '#' && UART_Manage_Object->Rx_Buffer[i] != 0; i++) {
        if (UART_Manage_Object->Rx_Buffer[i] == '.') {
            tmp_dot_flag = i;
        }
        else {
            Variable_Value = Variable_Value * 10.0f + (UART_Manage_Object->Rx_Buffer[i] - '0');
        }
    }

    // 如果有小数点则考虑
    if (tmp_dot_flag != 0) {
        Variable_Value /= pow(10.0f, i - tmp_dot_flag - 1.0f);
    }

    Variable_Value *= tmp_sign_coefficient;
}

void Class_Serialport::Output() {
    for (int i = 0; i < UART_BUFFER_SIZE; i++) {
        UART_Manage_Object->Tx_Buffer[i] = 0;
    }

    // 发送数组指针偏移
    uint8_t bias = 0;

    /* 特殊帧格式模式 */
    if (UART_Tx_Data_Type == Serialport_Data_Type_JUSTFLOAT) {
        // 填充float格式原始字节流
        for (int i = 0; i < Data_Number; i++) {
            memcpy(UART_Manage_Object->Tx_Buffer + bias, Data[i], sizeof(float));
            bias += sizeof(float);
        }
        
        // justfloat数据帧帧尾
        uint32_t tail = 0x7F800000;
        memcpy(UART_Manage_Object->Tx_Buffer + bias, &tail, sizeof(uint32_t));
        bias += sizeof(uint32_t);

        // 计算发送数组字节长度
        Frame_Size = bias;
        return;
    }

    /* 原始字节流模式 */
    // 放置帧头
    if (Frame_Header != 0x00) {
        UART_Manage_Object->Tx_Buffer[0] = Frame_Header;
        bias = 1;
    }
    
    // 填充数据
    if (UART_Tx_Data_Type == Serialport_Data_Type_UINT8 || UART_Tx_Data_Type == Serialport_Data_Type_INT8) {
        for (int i = 0; i < Data_Number; i++) {
            memcpy(UART_Manage_Object->Tx_Buffer + bias, Data[i], sizeof(uint8_t));
            bias += sizeof(uint8_t);
        }
    }
    else if (UART_Tx_Data_Type == Serialport_Data_Type_UINT16 || UART_Tx_Data_Type == Serialport_Data_Type_INT16) {
        for (int i = 0; i < Data_Number; i++) {
            memcpy(UART_Manage_Object->Tx_Buffer + bias, Data[i], sizeof(uint16_t));
            bias += sizeof(uint16_t);
        }
    }
    else if (UART_Tx_Data_Type == Serialport_Data_Type_UINT32 || UART_Tx_Data_Type == Serialport_Data_Type_INT32 || UART_Tx_Data_Type == Serialport_Data_Type_FLOAT) {
        for (int i = 0; i < Data_Number; i++) {
            memcpy(UART_Manage_Object->Tx_Buffer + bias, Data[i], sizeof(uint32_t));
            bias += sizeof(uint32_t);
        }
    }
    else if (UART_Tx_Data_Type == Serialport_Data_Type_DOUBLE) {
        for (int i = 0; i < Data_Number; i++) {
            memcpy(UART_Manage_Object->Tx_Buffer + bias, Data[i], sizeof(uint64_t));
            bias += sizeof(uint64_t);
        }
    }

    // 放置帧尾
    if (Frame_Trailer != 0x00) {
        memcpy(UART_Manage_Object->Tx_Buffer + bias, &Frame_Trailer, sizeof(uint8_t));
        bias += 1;
    }

    // 计算发送数组字节长度
    Frame_Size = bias;
}

void Class_Serialport::Send() {
    UART_Send_Data(UART_Manage_Object->UART_Handler, UART_Manage_Object->Tx_Buffer, Frame_Size);
}
