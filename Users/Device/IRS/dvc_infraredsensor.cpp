/**
 * @brief 红外传感器
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "Drivers/FreeRTOS/drv_os.h"
#include "Device/IRS/dvc_infraredsensor.h"

void Class_8C_IRS::Init(Enum_IRS_Detect_Type __IRS_Detect_Type, GPIO_PORT *__Selector_Port_AD0, GPIO_PIN __Selector_Pin_AD0, GPIO_PORT *__Selector_Port_AD1, GPIO_PIN __Selector_Pin_AD1, GPIO_PORT *__Selector_Port_AD2, GPIO_PIN __Selector_Pin_AD2, GPIO_PORT *__Data_Port, GPIO_PIN __Data_Pin) {
    IRS_Detect_Type = __IRS_Detect_Type;
    Selector_Ports[0] = __Selector_Port_AD0;
    Selector_Pins[0] = __Selector_Pin_AD0;
    Selector_Ports[1] = __Selector_Port_AD1;
    Selector_Pins[1] = __Selector_Pin_AD1;
    Selector_Ports[2] = __Selector_Port_AD2;
    Selector_Pins[2] = __Selector_Pin_AD2;
    Data_Port = __Data_Port;
    Data_Pin = __Data_Pin;
}

void Class_8C_IRS::TIM_Feedback_PeriodElapsedCallback() {
    for (int i = 0; i < 8; i++) {
        GPIO_Set_Pins(Selector_Ports[0], Selector_Pins[0], !!(i & 0x01));
        GPIO_Set_Pins(Selector_Ports[1], Selector_Pins[1], !!(i & 0x02));
        GPIO_Set_Pins(Selector_Ports[2], Selector_Pins[2], !!(i & 0x04));

        Sys_Delay(50);
        switch (IRS_Detect_Type) {
        case IRS_Detect_Type_Positive:
            Channels[i] = !GPIO_Read_Pins(Data_Port, Data_Pin);
            break;
        case IRS_Detect_Type_Negative:
            Channels[i] = GPIO_Read_Pins(Data_Port, Data_Pin);
            break;
        default:
            break;
        }
    }
}

void Class_I2C_IRS::Init(I2C_INST *I2Cx, Enum_IRS_Detect_Type __IRS_Detect_Type) {
    I2C = I2Cx;
    IRS_Detect_Type = __IRS_Detect_Type;
    I2C_Address = GW_GRAY_ADDR_DEF;
    Pending_Register = 0;

    for (uint8_t i = 0; i < 8; i++) {
        Digital_Channels[i] = 0;
        Analog_Channels[i] = 0;
    }
}

uint8_t Class_I2C_IRS::I2C_Write_Register(uint8_t reg, uint8_t *data, uint8_t len) {
    uint8_t buffer[16];
    buffer[0] = reg;
    for (uint8_t i = 0; i < len; i++) {
        buffer[i + 1] = data[i];
    }
    uint8_t status = I2C_Send_Data(I2C, I2C_Address, buffer, len + 1);
    if (status == STATUS_BUSY) {
        return status;// 总线忙，不阻塞等待，由上层下次重试
    }
    return status;
}

uint8_t Class_I2C_IRS::I2C_Read_Register(uint8_t reg, uint8_t *data, uint8_t len) {
    uint8_t status;
    // 发送寄存器地址
    status = I2C_Send_Data(I2C, I2C_Address, &reg, 1);
    if (status == STATUS_BUSY) {
        return status;// 总线忙，不阻塞等待，由上层下次重试
    }
    if (status != STATUS_DONE) {
        return STATUS_ERROR;
    }
    // 读取寄存器数据
    status = I2C_Receive_Data(I2C, I2C_Address, data, len);
    if (status == STATUS_BUSY) {
        return status;// 总线忙，不阻塞等待，由上层下次重试
    }
    return status;
}

uint8_t Class_I2C_IRS::Ping(void) {
    uint8_t data;
    if (I2C_Read_Register(GW_GRAY_PING, &data, 1) != STATUS_DONE) {
        return STATUS_ERROR;
    }
    if (data == GW_GRAY_PING_OK) {
        return STATUS_DONE;
    }
    else {
        return STATUS_ERROR;
    }
}

uint8_t Class_I2C_IRS::Read_Digital(uint8_t *data) {
    return I2C_Read_Register(GW_GRAY_DIGITAL_MODE, data, 1);
}

uint8_t Class_I2C_IRS::Read_Analog(uint8_t *buffer) {
    return I2C_Read_Register(GW_GRAY_ANALOG_BASE, buffer, 8);
}

uint8_t Class_I2C_IRS::Read_Single_Analog(uint8_t channel, uint8_t *data) {
    return I2C_Read_Register(GW_GRAY_ANALOG(channel), data, 1);
}

uint8_t Class_I2C_IRS::Read_Normalize(uint8_t *buffer) {
    uint8_t enable = 0xFF;
    uint8_t disable = 0x00;

    // 使能归一化
    if (I2C_Write_Register(GW_GRAY_ANALOG_NORMALIZE, &enable, 1) != STATUS_DONE) {
        return STATUS_ERROR;
    }
    vTaskDelay(10); // 等待传感器刷新数据

    // 读取归一化数据
    if (I2C_Read_Register(GW_GRAY_ANALOG_MODE, buffer, 8) != STATUS_DONE) {
        I2C_Write_Register(GW_GRAY_ANALOG_NORMALIZE, &disable, 1);
        return STATUS_ERROR;
    }

    // 关闭归一化
    I2C_Write_Register(GW_GRAY_ANALOG_NORMALIZE, &disable, 1);
    return STATUS_DONE;
}

void Class_I2C_IRS::Set_Calibration_Black(uint8_t threshold) {
    I2C_Write_Register(GW_GRAY_CALIBRATION_BLACK, &threshold, 1);
}

void Class_I2C_IRS::Set_Calibration_White(uint8_t threshold) {
    I2C_Write_Register(GW_GRAY_CALIBRATION_WHITE, &threshold, 1);
}

void Class_I2C_IRS::Set_Channel_Enable(uint8_t mask) {
    I2C_Write_Register(GW_GRAY_ANALOG_CHANNEL_ENABLE, &mask, 1);
}

void Class_I2C_IRS::Set_Address(uint8_t addr) {
    I2C_Write_Register(GW_GRAY_CHANGE_ADDR, &addr, 1);
    I2C_Address = addr;
}

uint8_t Class_I2C_IRS::Get_Error(uint8_t *data) {
    return I2C_Read_Register(GW_GRAY_ERROR, data, 1);
}

uint8_t Class_I2C_IRS::Get_Firmware(uint8_t *data) {
    return I2C_Read_Register(GW_GRAY_FIRMWARE, data, 1);
}

void Class_I2C_IRS::Reboot(void) {
    uint8_t dummy = 0;
    I2C_Write_Register(GW_GRAY_REBOOT, &dummy, 1);
}

void Class_I2C_IRS::Broadcast_Reset(void) {
    uint8_t magic[] = {0xB8, 0xD0, 0xCE, 0xAA, 0xBF, 0xC6, 0xBC, 0xBC};
    I2C_Send_Data(I2C, 0x00, magic, 8);
}

void Class_I2C_IRS::TIM_Feedback_PeriodElapsedCallback() {
    uint8_t digital;
    // 读取数字通道值
    if (Read_Digital(&digital) == STATUS_DONE) {
        GW_Gray_Split_Channels(digital, Digital_Channels);
        if (IRS_Detect_Type == IRS_Detect_Type_Positive) {
            for (uint8_t i = 0; i < 8; i++) {
                Digital_Channels[i] = !Digital_Channels[i];
            }
        }
    }
    // 读取模拟通道值
    if (Read_Analog(Analog_Channels) != STATUS_DONE) {
        // 读取失败时保留上一帧的模拟值，不清零
    }
}

void Class_I2C_IRS::I2C_Callback(uint8_t *Buffer, uint16_t Length) {
    // 根据等待的寄存器地址解析 DMA 接收数据
    switch (Pending_Register) {
    case GW_GRAY_DIGITAL_MODE:
        // Buffer[0] = 8 位数字通道值
        GW_Gray_Split_Channels(Buffer[0], Digital_Channels);
        if (IRS_Detect_Type == IRS_Detect_Type_Positive) {
            for (uint8_t i = 0; i < 8; i++) {
                Digital_Channels[i] = !Digital_Channels[i];
            }
        }
        break;
    case GW_GRAY_ANALOG_BASE:
        // Buffer[0..7] = 8 通道模拟值
        for (uint8_t i = 0; i < 8; i++) {
            Analog_Channels[i] = Buffer[i];
        }
        break;
    default:
        break;
    }
    Pending_Register = 0; // 清除等待状态
}
