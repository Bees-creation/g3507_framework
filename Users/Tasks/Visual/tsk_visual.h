/**
 * @brief 视觉任务
 * @date 2026/5/31
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_VISUAL_H
#define TSK_VISUAL_H

#include "Device/IRS/dvc_infraredsensor.h"

extern float Channels[8];

#define IRS_PORT_AD0 GPIO_PORT_B
#define IRS_PIN_AD0 GPIO_PIN_23
#define IRS_PORT_AD1 GPIO_PORT_B
#define IRS_PIN_AD1 GPIO_PIN_26
#define IRS_PORT_AD2 GPIO_PORT_B
#define IRS_PIN_AD2 GPIO_PIN_27
#define IRS_PORT_OUT GPIO_PORT_A
#define IRS_PIN_OUT GPIO_PIN_29

void Visual_Init(void);

void Visual_Task(void);

#endif
