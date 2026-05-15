/**
 * @brief 调试用任务函数
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_config.h"

static void Block_Task_Entry(void) {
    for (int i = 0; i < MAX_BLOCK_TASK_NUM; i++) {
        if (Block_Task_List[i] != NULL) {
            Block_Task_List[i]();
        }
    }
}

static void Periodic_Task_Entry(void *param) {
    Struct_Periodic_Task_Manage_Object *task = (Struct_Periodic_Task_Manage_Object*)param;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;) {
        // 执行用户注册的回调
        task->Task_Function();

        // 等待下一个周期
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(task->Period));
    }
}

int Register_Block_Task(Task_Function_t _func) {
    if (_block_task_count >= MAX_BLOCK_TASK_NUM) return -1;

    Block_Task_List[_block_task_count++] = _func;
    return 0;
}

int Register_Periodic_Task(uint32_t _period, Task_Function_t _func,
                           uint16_t stack_size, UBaseType_t priority) {
    if (_periodic_task_count >= MAX_PERIODIC_TASK_NUM) return -1;

    Struct_Periodic_Task_Manage_Object *task = &Period_Task_List[_periodic_task_count];
    task->Task_Function = _func;
    task->Period = _period;
    task->Available = 1;

    BaseType_t ret = xTaskCreate(
        Periodic_Task_Entry,        // 统一的入口
        "Task",                     // 任务名
        stack_size,                 // 外部指定栈大小
        (void*)task,                // 传递参数，就是任务管理结构体指针
        priority,
        &task->Task_Handle
    );

    if (ret == pdPASS) {
        _periodic_task_count++;
        return 0;
    } else {
        // 内存不足
        task->Available = 0;
        return -2;
    }
}

void Task_Init(void) {
    // 阻塞式任务函数以1ms为周期调用
    if (Register_Periodic_Task(1, Block_Task_Entry, 256, 2)) {
        Error_Handler();
    }
    // 板载LED灯闪烁任务以500ms为周期调用
    if (Register_Periodic_Task(500, Task_Debug, 64, 2)) {
        Error_Handler();
    }

    /** 在此处注册任务函数 -- begin -- */

    /** 在此处注册任务函数 --  end  -- */

    vTaskStartScheduler();
}

void Task_Debug(void) {
    DL_GPIO_togglePins(GPIO_GRP_B_PORT, GPIO_GRP_B_PIN_22_PIN);
}
