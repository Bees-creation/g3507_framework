/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_motion.h"

/* 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Sensor/tsk_sensor.h"
/* 在此处引用任务函数头文件 --  end  -- */

Class_Brush_Motor_Drv8701e Left_Motor;
Class_Brush_Motor_Drv8701e Right_Motor;
Class_Differential_Chassis chassis(Left_Motor, Right_Motor, CHASSIS_WHEEL_TRACK, CHASSIS_WHEEL_RADIUS);

enum Enum_Car_Operation_Type {
    Car_Operation_Type_FORWARD = 0,
    Car_Operation_Type_LEFT,
    Car_Operation_Type_RIGHT,
    Car_Operation_Type_LOST,
};

void Motion_Trace(void)
{
    Enum_Car_Operation_Type operation = Car_Operation_Type_FORWARD;
    // 计算轨迹偏离
    const int8_t weight[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
    int8_t bias = 0;
    for (int i = 0; i < 8; i++) {
        if (Channels[i] == 1) {
            bias += weight[i];
        }
    }

    // 计算轨迹状态
    uint8_t status = 0;
    for (int i = 0; i < 8; i++) {
        if (Channels[i] == 1) {
            status |= 0x01;
        }
        status = (status << 1);
    }

    uint8_t lost = 0;
    switch (status)
    {
    case 0xF0:// 11110000
    case 0xF4:// 11111000
    /* 左转 */
        operation = Car_Operation_Type_LEFT;
        break;
    case 0x0F:// 00001111
    case 0x1F:// 00011111
    /* 右转 */
        operation = Car_Operation_Type_RIGHT;
        break;
    case 0x00:// 00000000
    /* 丢失轨迹处理 */
        operation = Car_Operation_Type_LOST;
        break;
    default:
        break;
    }

    static int16_t last_bias = 0;
    if (operation == Car_Operation_Type_LOST) {
        bias = last_bias; // 使用上次有效误差
    } else {
        last_bias = bias;
    }

    int16_t diff = DIFF_KP * bias;
    chassis.Set_Target_Velocity_Y(0);
    chassis.Set_Target_Omega(diff);
}

void Motion_Init(void) {
    // PID初始化
    Left_Motor.Omega_Loop.Init(CHASSIS_LEFT_PID_OMEGA_KP, CHASSIS_LEFT_PID_OMEGA_KI, 0.0f, 0.0f, CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX, CHASSIS_LEFT_PID_OMEGA_OUT_MAX);
    Right_Motor.Omega_Loop.Init(CHASSIS_RIGHT_PID_OMEGA_KP, CHASSIS_RIGHT_PID_OMEGA_KI, 0.0f, 0.0f, CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX, CHASSIS_RIGHT_PID_OMEGA_OUT_MAX);
    // 编码器初始化
    Left_Motor.QEI.Init(0.01, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_AB, MOTOR_LEFT_QEI_PHASE_A_PORT, MOTOR_LEFT_QEI_PHASE_A_PIN, MOTOR_LEFT_QEI_PHASE_B_PORT, MOTOR_LEFT_QEI_PHASE_B_PIN);
    Right_Motor.QEI.Init(0.01, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_AB, MOTOR_RIGHT_QEI_PHASE_A_PORT, MOTOR_RIGHT_QEI_PHASE_A_PIN, MOTOR_RIGHT_QEI_PHASE_B_PORT, MOTOR_RIGHT_QEI_PHASE_B_PIN);
    // 电机初始化
    Left_Motor.Init((TIMER_INST*)TIMA0, TIMER_CHANNEL_0, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_LEFT_DIRECTION_PORT, MOTOR_LEFT_DIRECTION_PIN);
    Right_Motor.Init((TIMER_INST*)TIMA0, TIMER_CHANNEL_1, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_RIGHT_DIRECTION_PORT, MOTOR_RIGHT_DIRECTION_PIN);
}

void Motion_Task(void) {
    Motion_Trace();
    chassis.TIM_Update_PeriodElapsedCallback();
}

void GPIOB_PIN23_IRQHandler (void) {
    Left_Motor.QEI.GPIO_InterruptCallback();
}

void GPIOB_PIN2_IRQHandler (void) {
    Right_Motor.QEI.GPIO_InterruptCallback();
}
