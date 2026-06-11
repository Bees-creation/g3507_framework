/**
 * @brief IMU
 * @date 2026/6/9
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_imu.h"

//解锁指令
static uint8_t Key[5] = {0x55, 0xAA, 0x13, 0x8E, 0x5F};
//Z轴角度归零指令
static uint8_t Yaw_Zero[5] = {0x55, 0xAA, 0x15, 0x00, 0x00};
//保存指令
static uint8_t Save[5] = {0x55, 0xAA, 0x00, 0x00, 0x00};
//获取零偏指令
static uint8_t BIAS_CAL[5] = {0x55, 0xAA, 0x0A, 0x01, 0x00};

void Class_IMU_Mspm0g3507::Init(void) {
    sendCaliYawCommand();
}

void Class_IMU_Mspm0g3507::TIM_Feedback_PeriodElapsedCallback() {
    
}

void Class_IMU_Mspm0g3507::UART_Callback() {
    UART_Receive_Data(UART_Manage_Object.UART_Handler, UART_Manage_Object.Rx_Buffer, 1);
    CopeSerial2Data(UART_Manage_Object.Rx_Buffer[0]);
}

void Class_IMU_Mspm0g3507::CopeSerial2Data(unsigned char ucData)
{
    static unsigned char ucRxBuffer[11];
    static unsigned char ucRxCnt = 0;

    ucRxBuffer[ucRxCnt++] = ucData;

    if (ucRxBuffer[0] != 0x5A)
    {
        ucRxCnt = 0;
        return;
    }

    if (ucRxCnt < 5) return;

    unsigned char sum = 0;
    if (ucRxBuffer[1] == 0xAA)
    {
        // 角速度帧校验和：0x5A + 0xAA + AzL + AzH 
        sum = ucRxBuffer[0] + ucRxBuffer[1] +
              ucRxBuffer[2] + ucRxBuffer[3] ;

        if (sum != ucRxBuffer[4])
        {
            ucRxCnt = 0;
            return;
        }

        short wz = (short)((ucRxBuffer[3] << 8) | ucRxBuffer[2]);

        gyro.z_gyro = (float)wz / 32768.0f * 2000.0f;
    }
    else if (ucRxBuffer[1] == 0xBB)
    {
        // 角度帧校验和：0x5A + 0xBB + YawH + YawL 
        sum = ucRxBuffer[0] + ucRxBuffer[1] +
              ucRxBuffer[2] + ucRxBuffer[3];

        if (sum != ucRxBuffer[4])
        {
            ucRxCnt = 0;
            return;
        }

        short rawYaw = (short)((ucRxBuffer[3] << 8) | ucRxBuffer[2]);
        eular.yaw = (float)rawYaw / 32768.0f * 180.0f;
    }
    ucRxCnt = 0;
}

void Class_IMU_Mspm0g3507::sendCaliYawCommand(void) 
{
    UART_Send_Data(UART_Manage_Object.UART_Handler, Key, 5);
    Sys_Delay(100 * 1000);
    UART_Send_Data(UART_Manage_Object.UART_Handler, Yaw_Zero, 5);
    Sys_Delay(100 * 1000);
    UART_Send_Data(UART_Manage_Object.UART_Handler, Save, 5);
}

void Class_IMU_Mspm0g3507::performCaliBias(void) 
{ 
    UART_Send_Data(UART_Manage_Object.UART_Handler, Key, 5);
    Sys_Delay(100 * 1000);
    UART_Send_Data(UART_Manage_Object.UART_Handler, BIAS_CAL, 5);
    Sys_Delay(21000 * 1000);
    UART_Send_Data(UART_Manage_Object.UART_Handler, Save, 5);
}
