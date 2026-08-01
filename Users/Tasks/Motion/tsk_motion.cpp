/**
 * @brief 运动控制任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_motion.h"

/* 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Sensor/tsk_sensor.h"
/* 在此处引用任务函数头文件 --  end  -- */

Struct_Visual_State Visual_State;

Class_Brush_Motor_Drv8701e Left_Motor;
Class_Brush_Motor_Drv8701e Right_Motor;
Class_Differential_Chassis Chassis(Left_Motor, Right_Motor, CHASSIS_WHEEL_TRACK, CHASSIS_WHEEL_RADIUS);
Class_Stepping_Motor_D36A Step_Motor;
Class_Screw_Lift Screw_Lift(Step_Motor, SCREW_LEAD);
Class_Balance_Arm Balance_Arm(Screw_Lift);

enum Enum_Car_State {
    Car_State_IDLE = 0,// 空闲
    Car_State_FORWARD,// 循迹行驶
    // Car_State_LEFT,// 左转
    // Car_State_RIGHT,// 右转
    Car_State_LOST,// 丢失轨迹
};

static Enum_Car_State state = Car_State_IDLE;// 小车运动状态机

// 差速权重
const int8_t weight[8] = {10, 7, 4, 1, -1, -4, -7, -10};

uint8_t Motion_Trace(float speed) {
    uint8_t status = 0;// 巡迹模块八位通道值
    float bias = 0.0f;// 轨迹偏离
    static float last_bias = 0;// 轨迹偏离历史值
    uint8_t count = 0;// 检测到轨迹的传感器数量
    for (int i = 0; i < 8; i++) {
        if (Digital_Channels[i] == 1) {
            status |= (0x01 << i);// 通道值转换
            bias += weight[i];// 计算轨迹偏离
            count++;
        }
    }

    // 平均化和一次滤波
    if (count) {
        bias /= count;
        bias = Filter_First_Order(bias, last_bias, 0.7f);
        last_bias = bias;
    }
    else {
        bias = last_bias;
    }

    // 状态识别
    switch (status) {
        // 三线连续
        case 0xE0:// 11100000
        case 0x70:// 01110000
        case 0x38:// 00111000
        case 0x1C:// 00011100
        case 0x0E:// 00001110
        case 0x07:// 00000111
        // 四线连续
        case 0xF0:// 11110000
        case 0x78:// 01111000
        case 0x3C:// 00111100
        case 0x1E:// 00011110
        case 0x0F:// 00001111
        // 五线连续
        case 0xF8:// 11111000
        case 0x7C:// 01111100
        case 0x3E:// 00111110
        case 0x1F:// 00011111
        // 六线连续
        case 0xFC:// 11111100
        case 0x7E:// 01111110
        case 0x3F:// 00111111
        // 七线连续
        case 0xFE:// 11111110
        case 0x7F:// 01111111
        // 八线连续
        case 0xFF:// 11111111
            return STATUS_DONE;
        case 0x00:// 00000000
            // 脱线处理已经默认定义
            break;
        default:
            state = Car_State_FORWARD;
            break;
    }

    // 小车运动状态机控制
    switch (state) {
        case Car_State_IDLE:
            // 空闲时静止
            Chassis.Set_Target_Velocity_Y(0);
            Chassis.Set_Target_Omega(0);
            Chassis.Left_Motor.Omega_Loop.Set_Integral_Error(0.0f);
            Chassis.Right_Motor.Omega_Loop.Set_Integral_Error(0.0f);
            break;
        case Car_State_FORWARD:
            // 检查相对目标角
            if (Math_Abs((float)Target_Rotation - (float)Current_Rotation) < 45.0f) {
                // 降速搜寻
                speed *= 0.2f;
            }
            // 默认巡迹方法
            Chassis.Set_Target_Velocity_Y(speed);
            Chassis.Set_Target_Omega(bias * DIFF_KP);
            break;
        case Car_State_LOST:
            // 默认丢失轨迹搜寻
            Chassis.Set_Target_Velocity_Y(0);
            Chassis.Set_Target_Omega(((float)Target_Rotation - (float)Current_Rotation) * DIFF_KP);
            break;
        default:
            break;
    }
    return STATUS_BUSY;
}

void Motion_Stop(void) {
    state = Car_State_IDLE;// 重置状态机
    Chassis.Set_Target_Velocity_Y(0.0f);
    Chassis.Set_Target_Omega(0.0f);
    Chassis.Left_Motor.Omega_Loop.Set_Integral_Error(0.0f);
    Chassis.Right_Motor.Omega_Loop.Set_Integral_Error(0.0f);
}

void _Visual_Feedback(void) {
    // 更新小球当前状态，速度做一阶低通滤波抑制噪声
    static float filtered_v = 0.0f;
    filtered_v = Filter_First_Order(Visual_State.v, filtered_v, 0.6f);
    Balance_Arm.Set_Now_State(Visual_State.x, filtered_v);
}

void Visual_Set_Target(float target) {
    Balance_Arm.Set_Target_Position(target);
}

uint8_t Visual_Trace(void) {
    // 设定目标位置
    Visual_Set_Target(0.0f);
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
    // 步进电机初始化
    Step_Motor.Init((TIMER_INST*)TIMG7, TIMER_CHANNEL_0, Stepping_Motor_Control_Method_Omega, STEPPING_MOTOR_DIRECTION_PORT, STEPPING_MOTOR_DIRECTION_PIN, DELTA_TIME, STEPPING_MOTOR_CLOCK_FREQ, STEPPING_MOTOR_MIN_OMEGA, STEPPING_MOTOR_MAX_OMEGA, STEPPING_MOTOR_SCALE, STEPPING_MOTOR_DIVISION);
    // 丝杆角度限位
    Screw_Lift.Set_Angle_Limit(SCREW_ANGLE_MIN, SCREW_ANGLE_MAX);
    // 丝杆控制模式与角度环参数
    Screw_Lift.Set_Control_Mode(SCREW_CONTROL_MODE);
    Screw_Lift.Set_Angle_Kp(SCREW_ANGLE_KP);
    // 平衡球控制初始化
    Balance_Arm.Position_PID.Init(BALANCE_POSITION_PID_KP, BALANCE_POSITION_PID_KI, BALANCE_POSITION_PID_KD, 0.0f, BALANCE_POSITION_PID_I_OUT_MAX, BALANCE_POSITION_PID_OUT_MAX, DELTA_TIME, BALANCE_POSITION_PID_DEAD_ZONE);
    Balance_Arm.Velocity_PID.Init(BALANCE_VELOCITY_PID_KP, BALANCE_VELOCITY_PID_KI, BALANCE_VELOCITY_PID_KD, 0.0f, BALANCE_VELOCITY_PID_I_OUT_MAX, BALANCE_VELOCITY_PID_OUT_MAX, DELTA_TIME, BALANCE_VELOCITY_PID_DEAD_ZONE);
    // 设定初始平衡值
    Balance_Arm.Set_Target_Position(0.0f);
}

void Motion_Task(void) {
    // 电机更新
    Chassis.TIM_Update_PeriodElapsedCallback();
    // 平衡球视觉反馈
    _Visual_Feedback();
    // 平衡球控制更新
    Balance_Arm.TIM_Update_PeriodElapsedCallback();
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
