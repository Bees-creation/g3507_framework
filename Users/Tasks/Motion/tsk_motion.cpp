/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_motion.h"

/* 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Sensor/tsk_sensor.h"
/* 在此处引用任务函数头文件 --  end  -- */

Struct_Motor_State Motor_State_Left = {0};
Struct_Motor_State Motor_State_Right = {0};

Struct_Chassis_State Chassis_State = {0};

Struct_Trace_State Trace_State;
Struct_Visual_State Visual_State;

Class_Brush_Motor_Drv8701e Left_Motor;
Class_Brush_Motor_Drv8701e Right_Motor;
Class_Differential_Chassis chassis(Left_Motor, Right_Motor, CHASSIS_WHEEL_TRACK, CHASSIS_WHEEL_RADIUS);

enum Enum_Car_State {
    Car_State_IDLE = 0,// 空闲
    Car_State_FORWARD,// 循迹行驶
    Car_State_LEFT,// 左转
    Car_State_RIGHT,// 右转
    Car_State_LOST,// 丢失轨迹
};

uint8_t Motion_Trace(float speed, uint8_t rounds) {
    static Enum_Car_State state = Car_State_IDLE;// 小车运动状态机

    uint8_t status = 0;// 巡迹模块八位通道值
    const int8_t weight[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
    int8_t bias = 0;// 轨迹偏离
    for (int i = 0; i < 8; i++) {
        if (Channels[i] == 1) {
            status |= 0x01;// 通道值转换
            bias += weight[i];// 计算轨迹偏离
        }
    }
    bias *= DIFF_KP;// 计算旋转速度

    // 转向控制角度
    static float Target_Yaw;

    // 根据八位通道值判断巡迹状态
    switch (status) {
    case 0xF0:// 11110000
    case 0xF8:// 11111000
    case 0xFC:// 11111100
    /* 直角左转 */
        if (state == Car_State_FORWARD) {
            Target_Yaw = Yaw - 90.0f;// 设定转向角度
            state = Car_State_LEFT;// 如果正在循迹行驶，那么进入左转状态
        }
        break;
    case 0x0F:// 00001111
    case 0x1F:// 00011111
    case 0x3F:// 00111111
    /* 直角右转 */
        if (state == Car_State_FORWARD) {
            Target_Yaw = Yaw + 90.0f;// 设定转向角度
            state = Car_State_RIGHT;// 如果正在循迹行驶，那么进入右转状态
        }
        break;
    case 0x00:// 00000000
    /* 丢失轨迹处理 */
        if (state == Car_State_FORWARD) {
            state = Car_State_LOST;// 如果正在循迹行驶，那么进入丢失轨迹状态
        }
        break;
    default:
        if (state == Car_State_IDLE || state == Car_State_LOST) {
            state = Car_State_FORWARD;// 如果正在空闲或丢失轨迹，那么进入循迹行驶状态
        }
        break;
    }

    // 小车运动状态机控制
    switch (state) {
        case Car_State_IDLE:
            // 空闲时静止
            chassis.Set_Target_Velocity_Y(0);
            chassis.Set_Target_Omega(0);
            break;
        case Car_State_FORWARD:
            // 默认巡迹方法
            chassis.Set_Target_Velocity_Y(speed);
            chassis.Set_Target_Omega(bias);
            break;
        case Car_State_LEFT:
            // 左转 90 度
            chassis.Set_Target_Velocity_Y(100);
            chassis.Set_Target_Omega(0.4f);
            if (Math_Abs(Target_Yaw - Yaw) < 5.0f) {
                state = Car_State_IDLE;
                return Trace_State.Turn(rounds);
            }
            break;
        case Car_State_RIGHT:
            // 右转 90 度
            chassis.Set_Target_Velocity_Y(100);
            chassis.Set_Target_Omega(-0.4f);
            if (Math_Abs(Target_Yaw - Yaw) < 5.0f) {
                state = Car_State_IDLE;
                return Trace_State.Turn(rounds);
            }
            break;
        case Car_State_LOST:
            // 默认丢失轨迹寻找
            chassis.Set_Target_Velocity_Y(-100);
            chassis.Set_Target_Omega(0);
            break;
    }
    return STATUS_BUSY;
}

void Motion_Stop(void) {
    Trace_State.Clear();// 清空圈数记录
    chassis.Set_Target_Velocity_Y(0);
    chassis.Set_Target_Omega(0);
}

uint8_t Visual_Trace(void) {
    uint8_t flag = Visual_State.flag;
    float x = Visual_State.x;
    float y = Visual_State.y;
    // 判断操作
    switch (flag) {
    case 0:// 正常追踪
    
        break;
    case 1:// 丢失

        break;
    }
    return STATUS_BUSY;
}

void Motion_Init(void) {
    // PID初始化
    Left_Motor.Omega_Loop.Init(CHASSIS_LEFT_PID_OMEGA_KP, CHASSIS_LEFT_PID_OMEGA_KI, CHASSIS_LEFT_PID_OMEGA_KD, 0.0f, CHASSIS_LEFT_PID_OMEGA_I_OUT_MAX, CHASSIS_LEFT_PID_OMEGA_OUT_MAX, DELTA_TIME);
    Right_Motor.Omega_Loop.Init(CHASSIS_RIGHT_PID_OMEGA_KP, CHASSIS_RIGHT_PID_OMEGA_KI, CHASSIS_RIGHT_PID_OMEGA_KD, 0.0f, CHASSIS_RIGHT_PID_OMEGA_I_OUT_MAX, CHASSIS_RIGHT_PID_OMEGA_OUT_MAX, DELTA_TIME);
    // 编码器初始化
    Left_Motor.QEI.Init(DELTA_TIME, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_BA, MOTOR_LEFT_QEI_PHASE_A_PORT, MOTOR_LEFT_QEI_PHASE_A_PIN, MOTOR_LEFT_QEI_PHASE_B_PORT, MOTOR_LEFT_QEI_PHASE_B_PIN);
    Right_Motor.QEI.Init(DELTA_TIME, CHASSIS_WHEEL_QEI_SCALE, Encoder_Count_Method_A_UP_BA, MOTOR_RIGHT_QEI_PHASE_A_PORT, MOTOR_RIGHT_QEI_PHASE_A_PIN, MOTOR_RIGHT_QEI_PHASE_B_PORT, MOTOR_RIGHT_QEI_PHASE_B_PIN);
    // 电机初始化
    Left_Motor.Init((TIMER_INST*)TIMG8, TIMER_CHANNEL_0, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_LEFT_DIRECTION_PORT, MOTOR_LEFT_DIRECTION_PIN, DELTA_TIME, FILTER);
    Right_Motor.Init((TIMER_INST*)TIMG8, TIMER_CHANNEL_1, Motor_Control_Method_Omega, Motor_Control_Algorithm_PID, MOTOR_RIGHT_DIRECTION_PORT, MOTOR_RIGHT_DIRECTION_PIN, DELTA_TIME, FILTER);
}

void Motion_Task(void) {
    chassis.TIM_Update_PeriodElapsedCallback();
    // Motor_State_Left.now_angle = Left_Motor.Get_Angle();
    // Motor_State_Left.now_omega = Left_Motor.Get_Omega();
    // Motor_State_Right.now_angle = Right_Motor.Get_Angle();
    // Motor_State_Right.now_omega = Right_Motor.Get_Omega();
    // Chassis_State.now_speed = chassis.Get_Now_Velocity_Y();
    // Chassis_State.now_omega = chassis.Get_Now_Omega();
}

#ifdef __cplusplus
extern "C" {
#endif

void GPIOB_PIN2_IRQHandler(void) {
    Right_Motor.QEI.GPIO_InterruptCallback();
}

void GPIOB_PIN23_IRQHandler(void) {
    Left_Motor.QEI.GPIO_InterruptCallback();
}

#ifdef __cplusplus
}
#endif
