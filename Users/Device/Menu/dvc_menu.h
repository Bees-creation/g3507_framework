/**
 * @brief 菜单逻辑
 * @date 2026/6/14
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_MENU_H
#define DVC_MENU_H

#include "Device/LCD/dvc_lcd.h"
#include "Device/Key/dvc_key.h"

/* 显示设置 */

// 色彩模式
constexpr uint16_t background_color = BLACK;// 背景色
constexpr uint16_t icon_color = WHITE;// 图标色
constexpr uint16_t foreground_color = BLACK;// 前景色
constexpr uint16_t text_color = WHITE;// 文字色
constexpr uint16_t cursor_color = LBBLUE;// 光标色

// 顶部状态栏属性
constexpr uint8_t Bar_Top_Height = 32;// 栏高度
constexpr uint8_t Bar_Top_Item_Width = 32;// 项宽度
constexpr uint8_t Bar_Top_Item_Height = 32;// 项高度
constexpr uint8_t Bar_Top_Item_Bias = 32;// 项缩进
constexpr uint8_t Bar_Top_Item_Gaps = 12;// 项间隔
// 底部状态栏属性
constexpr uint8_t Bar_Bottom_Height = 32;
constexpr uint8_t Bar_Bottom_Item_Width = 32;
constexpr uint8_t Bar_Bottom_Item_Height = 32;
constexpr uint8_t Bar_Bottom_Item_Bias = 32;
constexpr uint8_t Bar_Bottom_Item_Gaps = 12;

// 菜单栏属性
constexpr Enum_Font_Size Menu_Item_Font = Font_Size_24_12;// 字体大小
constexpr uint8_t Menu_Item_Bias = 0;// 项缩进

typedef struct Struct_Menu Struct_Menu;// 菜单前向声明

/**
 * @brief 菜单项
 * 
 * @param Text 显示文字
 * @param Status 任务状态位指针
 * @param Sub_Menu 子菜单
 */
typedef struct Struct_Menu_Item {
    const uint8_t *Text;
    uint8_t *Status;
    Struct_Menu *Sub_Menu;
} Struct_Menu_Item;

/**
 * @brief 菜单
 * 
 * @param Menu_Item_List 当前菜单项列表
 * @param Menu_Count 当前菜单项个数
 * @param Previous_Menu 上级菜单
 * @param Menu_Index 当前菜单项
 */
typedef struct Struct_Menu {
    const Struct_Menu_Item *Menu_Item_List;
    const uint8_t Menu_Count;
    Struct_Menu *Previous_Menu;
    uint8_t Menu_Index = 0;
} Struct_Menu;

/**
 * @brief 触发器信号
 */
enum Enum_Menu_Trigger {
    Menu_Trigger_IDLE = 0x00,
    Menu_Trigger_OK = 0x01,
    Menu_Trigger_SWITCH_UP = 0x02,
    Menu_Trigger_SWITCH_DOWN = 0x04,
};

/**
 * @brief 菜单项状态
 */
enum Enum_Menu_Item_State {
    Menu_Item_State_IDLE = 0,
    Menu_Item_State_RUNNING,
    Menu_Item_State_STOPPING,
};

class Class_Menu {
public:
    /**
     * @brief 构造函数
     * 
     * @param __LCD 绑定的显示屏
     * @param Home 主菜单数组指针
     * @param Home_Count 主菜单项个数
     */
    Class_Menu(Class_LCD &__LCD, Struct_Menu *__Home) : LCD(__LCD), Home(__Home), Menu(__Home) {
        Bar_Top_Item_Pos = Bar_Top_Item_Bias;
        Bar_Bottom_Item_Pos = Bar_Bottom_Item_Bias;
    }

    /**
     * @brief 显示主菜单
     */
    void Display_Home(void);

    /**
     * @brief 显示顶部状态栏
     */
    void Display_Top_Bar_Item(uint8_t Pos, uint8_t Width, uint8_t Height, const uint8_t *icon);

    /**
     * @brief 显示底部状态栏
     */
    void Display_Bottom_Bar_Item(uint8_t Pos, uint8_t Width, uint8_t Height, const uint8_t *icon);

    /**
     * @brief 显示菜单背景
     */
    void Display_Menu_Background(uint16_t color = foreground_color);

    /**
     * @brief 显示菜单
     */
    void Display_Menu(void);

    /**
     * @brief 显示菜单项
     */
    void Display_Menu_Item(uint8_t index, const uint8_t *str, uint16_t fcolor = text_color, uint16_t bcolor = foreground_color);

    /**
     * @brief 显示菜单项
     */
    void Display_Menu_Item(uint8_t index, float val, uint16_t len = 5, uint16_t fcolor = text_color, uint16_t bcolor = foreground_color);

    /**
     * @brief 进入菜单项或任务项，并执行程序
     */
    void Enter_Menu_Item(void);

    /**
     * @brief 退出菜单项或任务项，并终止程序
     */
    void Exit_Menu_Item(void);

    /**
     * @brief 上移菜单项
     */
    void Switch_UP_Menu_Item(void);

    /**
     * @brief 下移菜单项
     */
    void Switch_DOWN_Menu_Item(void);

    inline Class_LCD &Get_LCD(void) {
        return LCD;
    }

    inline Struct_Menu *Get_Menu(void) {
        return Menu;
    }

    inline Enum_Menu_Trigger Get_Trigger(void) {
        return Trigger;
    }

    inline void Clear_Trigger(void) {
        Trigger = Menu_Trigger_IDLE;
    }
    
protected:
    // 绑定的显示屏
    Class_LCD &LCD;

    /* 状态栏内部变量 */

    // 状态栏项位置
    uint8_t Bar_Top_Item_Pos;
    uint8_t Bar_Bottom_Item_Pos;

    /* 菜单栏内部变量 */

    // 主菜单
    Struct_Menu *Home;
    // 当前菜单
    Struct_Menu *Menu;
    // 上级菜单
    Struct_Menu *Previous_Menu = NULL;
    // 上次菜单
    Struct_Menu *Last_Menu = NULL;

    /* 任务调度内部变量 */

    // 触发器
    Enum_Menu_Trigger Trigger = Menu_Trigger_IDLE;
};

#endif /* DVC_MENU_H */
