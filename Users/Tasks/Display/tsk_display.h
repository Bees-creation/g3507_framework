/**
 * @brief 调试信息显示
 * @date 2026/5/24
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_DISPLAY_H
#define TSK_DISPLAY_H

#include "Device/Serialport/dvc_serialport.h"

typedef struct Struct {
    float angle;
    float omega;
    float torque;
} Struct_Motion_State;

/**
 * @brief 信息显示初始化
 */
void Display_Init(void);

/**
 * @brief 信息显示任务
 */
void Display_Task(void);

/**
 * @brief 串口工具回调函数
 */
void Serialport_Callback(uint8_t *Buffer, uint16_t Length);

#endif /* TSK_DISPLAY_H */
