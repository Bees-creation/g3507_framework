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
Class_Differential_Chassis chassis(Left_Motor, Right_Motor, CHASSIS_WHEEL_TRACK, CHASSIS_WHEEL_RADIUS);
Class_Stepping_Motor_D36A Step_Motor;

enum Enum_Car_State {
    Car_State_IDLE = 0,// 空闲
    Car_State_FORWARD,// 循迹行驶
    // Car_State_LEFT,// 左转
    // Car_State_RIGHT,// 右转
    Car_State_LOST,// 丢失轨迹
};

static Enum_Car_State state = Car_State_IDLE;// 小车运动状态机

// 差速权重
const int8_t weight[8] = {8, 6, 4, 2, -2, -4, -6, -8};

// 重复计数阈值
constexpr uint8_t threshold = 5;
// 重复计数器
Class_RepeatCounter Counter(threshold);

uint8_t Motion_Trace(float speed) {
    uint8_t status = 0;// 巡迹模块八位通道值
    int16_t bias = 0;// 轨迹偏离
    for (int i = 0; i < 8; i++) {
        if (Channels[i] == 1) {
            status |= 0x01;// 通道值转换
            bias += weight[i];// 计算轨迹偏离
        }
    }

    // 转向消抖检测
    static uint8_t filter = 0;
    // 状态记录器
    static uint8_t last_status = 0;

    // 状态识别
    if (last_status == status) {
        if (Counter.Count()) {
            switch (status) {
                case 0xFF:// 11111111
                    state = Car_State_IDLE;
                default:
                    state = Car_State_FORWARD;
                    break;
            }
        }
    }
    else {
        Counter.Collapse();
        last_status = status;
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
            chassis.Set_Target_Omega(bias * DIFF_KP);
            // 检查相对目标角
            if (Math_Abs(Target_Rotation - Current_Rotation) < 2.0f) {
                return STATUS_DONE;
            }
            break;
        case Car_State_LOST:
            // 默认丢失轨迹搜寻
            chassis.Set_Target_Velocity_Y(0);
            chassis.Set_Target_Omega((Target_Rotation - Current_Rotation) * DIFF_KP);
            break;
        default:
            break;
    }
    return STATUS_BUSY;
}

void Motion_Stop(void) {
    state = Car_State_IDLE;// 重置状态机
    chassis.Set_Target_Velocity_Y(0);
    chassis.Set_Target_Omega(0);
}

uint8_t Visual_Trace(void) {
    uint8_t flag = Visual_State.flag;
    float x = Visual_State.x;
    // 正常追踪
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
    Step_Motor.Init((TIMER_INST*)TIMG7, TIMER_CHANNEL_0, Motor_Control_Method_Omega, STEP_DIRECTION_PORT, STEP_DIRECTION_PIN, DELTA_TIME, STEP_CLOCK_FREQ, STEP_MIN_OMEGA, STEP_MAX_OMEGA, STEP_SCALE, STEP_DIVISION);
    Step_Motor.Set_Absolute_Target_Omega(0.2f);
    while (1);
}

void Motion_Task(void) {
    // 电机更新
    chassis.TIM_Update_PeriodElapsedCallback();
    // 步进电机更新
    Step_Motor.TIM_Calculate_PeriodElapsedCallback();
    Step_Motor.TIM_Output_PeriodElapsedCallback();
    Step_Motor.TIM_Feedback_PeriodElapsedCallback();
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
