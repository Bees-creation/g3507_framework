/**
 * @brief 菜单任务
 * @date 2026/6/14
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef TSK_MENU_H
#define TSK_MENU_H

#include "Drivers/FreeRTOS/drv_os.h"
#include "Device/Menu/dvc_menu.h"

#define CS_PORT GPIO_PORT_B
#define CS_PIN GPIO_PIN_14
#define RES_PORT GPIO_PORT_B
#define RES_PIN GPIO_PIN_10
#define DC_PORT GPIO_PORT_B
#define DC_PIN GPIO_PIN_11
#define BLK_PORT GPIO_PORT_B
#define BLK_PIN GPIO_PIN_26

#define KEY_OK_PORT GPIO_PORT_B
#define KEY_OK_PIN GPIO_PIN_21

/**
 * @brief 菜单初始化
 */
void Menu_Init(void);

/**
 * @brief 菜单项任务
 */
void Menu_Item_Task(void);

/**
 * @brief 菜单任务
 */
void Menu_Task(void);

/**
 * @brief 显示屏回调函数
 */
void LCD_Callback(uint8_t *Buffer, uint16_t Length);

#endif /* TSK_MENU_H */
