/**
 * @brief 任务函数入口
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_config.h"

/** 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Display/tsk_display.h"
#include "Tasks/Visual/tsk_visual.h"
#include "Tasks/Motion/tsk_motion.h"
/** 在此处引用任务函数头文件 --  end  -- */

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

uint8_t Register_Block_Task(Task_Function_t _func) {
    if (_block_task_count >= MAX_BLOCK_TASK_NUM) return STATUS_ERROR;

    Block_Task_List[_block_task_count++] = _func;
    return STATUS_DONE;
}

uint8_t Register_Periodic_Task(uint32_t _period, Task_Function_t _func,
                           uint16_t stack_size, UBaseType_t priority) {
    if (_periodic_task_count >= MAX_PERIODIC_TASK_NUM) return STATUS_ERROR;

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
        return STATUS_DONE;
    } else {
        // 内存不足
        task->Available = 0;
        return STATUS_OOM;
    }
}

void Task_Init(void) {
    /** 在此处执行初始化操作 -- begin -- */
    Display_Init();
    Visual_Init();
    Motion_Init();
    /** 在此处执行初始化操作 --  end  -- */

    // 板载LED灯闪烁任务以500ms为周期调用
    if (Register_Periodic_Task(500, Task_Debug, 64, 2) != STATUS_DONE) {
        Error_Handler();
    }

    /** 在此处注册任务函数 -- begin -- */
    if (Register_Block_Task(Display_Task) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Block_Task(Visual_Task) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Periodic_Task(10, Motion_Task, 128, 2) != STATUS_DONE) {
        Error_Handler();
    }
    /** 在此处注册任务函数 --  end  -- */

    // 阻塞式任务函数以10ms为周期调用
    if (Register_Periodic_Task(10, Block_Task_Entry, 256, 2) != STATUS_DONE) {
        Error_Handler();
    }

    vTaskStartScheduler();
}

void Task_Debug(void) {
    GPIO_Toggle_Pins(GPIO_PORT_B, GPIO_PIN_22);
}
