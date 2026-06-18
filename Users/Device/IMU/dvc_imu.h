/**
 * @brief IMU
 * @date 2026/6/9
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_IMU_H
#define DVC_IMU_H

#include "Drivers/UART/drv_uart.h"

typedef struct Struct_Accelerometer{
    float x_accel;// 右方加速度
    float y_accel;// 前方加速度
    float z_accel;// 上方加速度
} Struct_Accelerometer;

typedef struct Struct_Gyroscope{
    float x_gyro;// 俯仰加速度，向上拉升为正
    float y_gyro;// 翻滚加速度，向右翻滚为正
    float z_gyro;// 偏航加速度，向左旋转为正
} Struct_Gyroscope;

typedef struct Struct_Euler {
    float pitch;// 俯仰角
    float roll;// 翻滚角
    float yaw;// 偏航角
} Struct_Euler;

/**
 * @brief 规定东北天坐标系，旋转遵循右手定则，单位rad、mm、s
 */
class Class_IMU {
public:
    virtual void TIM_Feedback_PeriodElapsedCallback() = 0;

    inline float Get_AccelX() const { return accel.x_accel; }
    inline float Get_AccelY() const { return accel.y_accel; }
    inline float Get_AccelZ() const { return accel.z_accel; }
    inline float Get_GyroX() const { return gyro.x_gyro; }
    inline float Get_GyroY() const { return gyro.y_gyro; }
    inline float Get_GyroZ() const { return gyro.z_gyro; }
    inline float Get_Pitch() const { return eular.pitch; }
    inline float Get_Roll() const { return eular.roll; }
    inline float Get_Yaw() const { return eular.yaw; }

protected:
    Struct_Accelerometer accel = {0};
    Struct_Gyroscope gyro = {0};
    Struct_Euler eular = {0};
};

/**
 * @brief 串口陀螺仪
 */
class Class_IMU_Mspm0g3507:public Class_IMU {
public:
    Struct_UART_Manage_Object &UART_Manage_Object;

    Class_IMU_Mspm0g3507(Struct_UART_Manage_Object &__UART_Manage_Object) : UART_Manage_Object(__UART_Manage_Object) {
        
    };

    void Init(void);

    virtual void TIM_Feedback_PeriodElapsedCallback() override;

    /**
     * @brief 接收回调函数
     */
    void UART_Callback();

protected:
    short rawWz;// 原始Z轴角速度数据

    /**
     * @brief 数据解析函数，接收0x5A开头的5字节数据帧
     * 
     * @param ucData 接收的字节数据
     */
    void CopeSerial2Data(unsigned char ucData);

    /**
     * @brief 发送Z轴角度归零命令
     */
    void sendCaliYawCommand(void);

    /**
     * @brief 执行零偏校准
     */
    void performCaliBias(void);
};

#endif /* DVC_IMU_H */
