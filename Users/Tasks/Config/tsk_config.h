/**
 * @brief 调试用任务函数
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_DEBUG_H
#define TSK_DEBUG_H

#include "ti_msp_dl_config.h"
#include "FreeRTOS.h"
#include "task.h"

void Task_Init(void);

void Task_Debug_1ms(void* argument);
extern TaskHandle_t Task_Debug_1ms_Handle;

void Task_Debug_500ms(void* argument);
extern TaskHandle_t Task_Debug_500ms_Handle;

#endif
