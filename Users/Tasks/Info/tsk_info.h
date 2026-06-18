/**
 * @brief 调试信息显示
 * @date 2026/5/24
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_INFO_H
#define TSK_INFO_H

#include "Device/Serialport/dvc_serialport.h"

/**
 * @brief 信息显示初始化
 */
void Info_Init(void);

/**
 * @brief 信息显示任务
 */
void Info_Task(void);

/**
 * @brief 串口工具回调函数
 */
void Serialport_Callback(uint8_t *Buffer, uint16_t Length);

#endif /* TSK_INFO_H */
