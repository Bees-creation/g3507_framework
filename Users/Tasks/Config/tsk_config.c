/**
 * @brief 调试用任务函数
 * @date 2026/5/15
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_config.h"

TaskHandle_t Task_Debug_1ms_Handle = {0};
TaskHandle_t Task_Debug_500ms_Handle = {0};

void Task_Init(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate(Task_Debug_1ms, "Task_Debug_1ms", 128, NULL, 2, &Task_Debug_1ms_Handle);
    if (xReturn != pdPASS) while(1);

    xReturn = xTaskCreate(Task_Debug_500ms, "Task_Debug_500ms", 128, NULL, 2, &Task_Debug_500ms_Handle);
    if (xReturn != pdPASS) while(1);

    vTaskStartScheduler();
}

void Task_Debug_1ms(void* argument)
{
    (void)argument;
    for (;;)
    {
        vTaskDelay(1);
    }
}

void Task_Debug_500ms(void* argument)
{
    (void)argument;
    for (;;)
    {
        DL_GPIO_togglePins(GPIO_GRP_B_PORT, GPIO_GRP_B_PIN_22_PIN);
        vTaskDelay(500);
    }
}
