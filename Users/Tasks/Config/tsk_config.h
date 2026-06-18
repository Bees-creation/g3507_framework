/**
 * @brief 任务函数入口
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_CONFIG_H
#define TSK_CONFIG_H

#include "Drivers/FreeRTOS/drv_os.h"
#include "Drivers/GPIO/drv_gpio.h"

// 最大阻塞式任务数量
#define MAX_BLOCK_TASK_NUM      10
// 最大并发式任务数量
#define MAX_PERIODIC_TASK_NUM   10

// 任务函数指针类型
typedef void (*Task_Function_t)(void);

/**
 * @brief 并发式任务管理结构体
 * @param Task_Function 任务函数指针
 * @param Period 任务周期，单位为毫秒
 * @param Task_Handle 任务句柄
 * @param Available 任务创建状态，0为未创建，1为已创建
 */
typedef struct {
    Task_Function_t Task_Function;
    uint32_t Period;
    TaskHandle_t Task_Handle;
    uint8_t Available;
} Struct_Periodic_Task_Manage_Object;

// 阻塞式调度任务列表
static Task_Function_t Block_Task_List[MAX_BLOCK_TASK_NUM];
static uint8_t _block_task_count;
// 并发式调度任务列表
static Struct_Periodic_Task_Manage_Object Period_Task_List[MAX_PERIODIC_TASK_NUM];
static uint8_t _periodic_task_count;

/**
 * @brief 错误处理: 关闭中断并进入死循环
 */
inline void Error_Handler() {
    taskDISABLE_INTERRUPTS();
    for (;;) {
        // 错误处理
    }
}

/**
 * @brief 阻塞式任务函数入口
 */
static void _Block_Task_Entry(void);
/**
 * @brief 并发式任务函数入口
 */
static void _Periodic_Task_Entry(void *param);

/**
 * @brief 阻塞式任务注册函数
 * @param _func 任务函数指针
 */
uint8_t Register_Block_Task(Task_Function_t _func);

/**
 * @brief 并发式任务注册函数
 * @param _period 任务周期，单位为毫秒
 * @param _func 任务函数指针
 * @param stack_size 任务栈空间大小
 * @param priority 任务优先级
 */
uint8_t Register_Periodic_Task(uint32_t _period, Task_Function_t _func,
                           uint16_t stack_size, UBaseType_t priority);

/**
 * @brief 阻塞式任务注销函数
 * @param _func 任务函数指针
 */
uint8_t Unregister_Block_Task(Task_Function_t _func);

/**
 * @brief 并发式任务注销函数
 * @param _func 任务函数指针
 */
uint8_t Unregister_Periodic_Task(Task_Function_t _func);

/**
 * @brief 全局初始化函数
 */
void Task_Init(void);

/**
 * @brief 测试任务函数
 */
void Debug_Task(void);

#endif /* TSK_CONFIG_H */
