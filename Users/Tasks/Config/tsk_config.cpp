/**
 * @brief 任务函数入口
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_config.h"

/** 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Sensor/tsk_sensor.h"
#include "Tasks/Motion/tsk_motion.h"
#include "Tasks/Info/tsk_info.h"
#include "Tasks/Menu/tsk_menu.h"
/** 在此处引用任务函数头文件 --  end  -- */

static void _Block_Task_Entry(void) {
    Task_Function_t _Task_List[MAX_BLOCK_TASK_NUM];
    uint8_t _Task_Num;

    // 临界区内复制有效列表
    taskENTER_CRITICAL();
    _Task_Num = _block_task_count;
    for (int i = 0; i < _Task_Num; i++) {
        _Task_List[i] = Block_Task_List[i];
    }
    taskEXIT_CRITICAL();

    // 临界区外执行有效列表
    for (int i = 0; i < _Task_Num; i++) {
        if (_Task_List[i] != NULL) {
            _Task_List[i]();
        }
    }
}

static void _Periodic_Task_Entry(void *param) {
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
        _Periodic_Task_Entry, // 统一的入口
        "Task", // 任务名
        stack_size, // 外部指定栈大小
        (void*)task, // 传递参数，就是任务管理结构体指针
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

uint8_t Unregister_Block_Task(Task_Function_t _func) {
    uint8_t result = STATUS_ERROR;

    taskENTER_CRITICAL();
    for (int i = 0; i < _block_task_count; i++) {
        if (Block_Task_List[i] == _func) {
            // 将后续元素前移，覆盖待删除项
            for (int j = i; j < _block_task_count - 1; j++) {
                Block_Task_List[j] = Block_Task_List[j + 1];
            }
            _block_task_count--;
            result = STATUS_DONE;
            break;
        }
    }
    taskEXIT_CRITICAL();

    return result;
}

uint8_t Unregister_Periodic_Task(Task_Function_t _func) {
    uint8_t result = STATUS_ERROR;
    TaskHandle_t task_handle = NULL;
    uint8_t index = 0;

    taskENTER_CRITICAL();
    for (int i = 0; i < _periodic_task_count; i++) {
        if (Period_Task_List[i].Task_Function == _func &&
            Period_Task_List[i].Available == 1) {
            task_handle = Period_Task_List[i].Task_Handle;
            index = i;
            result = STATUS_DONE;
            break;
        }
    }

    if (result == STATUS_DONE) {
        // 将后续元素前移，覆盖待删除项
        for (int j = index; j < _periodic_task_count - 1; j++) {
            Period_Task_List[j] = Period_Task_List[j + 1];
        }
        _periodic_task_count--;
    }
    taskEXIT_CRITICAL();

    // 临界区外删除任务，允许删除自身
    if (task_handle != NULL) {
        vTaskDelete(task_handle);
    }

    return result;
}

void Task_Init(void) {
    /** 在此处执行初始化操作 -- begin -- */
    Sensor_Init();
    Motion_Init();
    Info_Init();
    Menu_Init();
    /** 在此处执行初始化操作 --  end  -- */

    // 板载LED灯闪烁任务以500ms为周期调用
    if (Register_Periodic_Task(500, Debug_Task, 64, 3) != STATUS_DONE) {
        Error_Handler();
    }

    /** 在此处注册任务函数 -- begin -- */
    if (Register_Block_Task(Info_Task) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Block_Task(Sensor_Task) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Periodic_Task(10, Motion_Task, 128, 2) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Periodic_Task(10, Menu_Item_Task, 384, 2) != STATUS_DONE) {
        Error_Handler();
    }

    if (Register_Periodic_Task(10, Menu_Task, 256, 3) != STATUS_DONE) {
        Error_Handler();
    }
    /** 在此处注册任务函数 --  end  -- */

    // 阻塞式任务函数以10ms为周期调用
    if (Register_Periodic_Task(10, _Block_Task_Entry, 256, 2) != STATUS_DONE) {
        Error_Handler();
    }

    vTaskStartScheduler();
}

void Debug_Task(void) {
    GPIO_Toggle_Pins(GPIO_PORT_B, GPIO_PIN_22);
}
