/**
 * @brief FreeRTOS回调函数定义
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief 栈溢出检测回调函数
 * @param xTask 任务句柄
 * @param pcTaskName 任务名
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    for (;;);
}

/**
 * @brief 空闲任务静态内存分配函数
 * @param ppxIdleTaskTCBBuffer 指向任务控制块指针的指针
 * @param ppxIdleTaskStackBuffer 指向栈空间指针的指针
 * @param pulIdleTaskStackSize 栈空间大小
 */
void vApplicationGetIdleTaskMemory(
    StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    uint32_t *pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configIDLE_TASK_STACK_DEPTH];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configIDLE_TASK_STACK_DEPTH;
}

/** 
 * @brief 定时器任务静态内存分配
 * @param ppxTimerTaskTCBBuffer 指向任务控制块指针的指针
 * @param ppxTimerTaskStackBuffer 指向栈空间指针的指针
 * @param pulTimerTaskStackSize 栈空间大小
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
