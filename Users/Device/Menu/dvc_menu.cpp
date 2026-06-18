/**
 * @brief 菜单逻辑
 * @date 2026/6/14
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_menu.h"

void Class_Menu::Display_Home(void) {
    Last_Menu = NULL;
    Menu = Home;// 回到主菜单
    Display_Top_Bar_Item(0, 0, 0, NULL);
    Display_Menu_Background();
    Display_Bottom_Bar_Item(0, 0, 0, NULL);
    Display_Menu();
}

void Class_Menu::Display_Top_Bar_Item(uint8_t Pos, uint8_t Width, uint8_t Height, const uint8_t *icon) {
    // 状态栏边栏显示
    if (icon == NULL) {
        LCD.Display_Fill(0, 0, LCD.Display_Width, Bar_Top_Height, background_color);
        // 重置状态栏项位置
        Bar_Top_Item_Pos = Bar_Top_Item_Bias;
        return;
    }
    // 状态栏图标显示
    LCD.Display_Icon(Bar_Top_Item_Pos, (Bar_Top_Height - Height) / 2, Width, Height, icon, icon_color, background_color);
    Bar_Top_Item_Pos = Bar_Top_Item_Pos + Bar_Top_Item_Gaps + Width;
}

void Class_Menu::Display_Bottom_Bar_Item(uint8_t Pos, uint8_t Width, uint8_t Height, const uint8_t *icon) {
    // 状态栏边栏显示
    if (icon == NULL) {
        LCD.Display_Fill(0, LCD.Display_Height - Bar_Bottom_Height, LCD.Display_Width, LCD.Display_Height, background_color);
        // 重置状态栏项位置
        Bar_Bottom_Item_Pos = Bar_Bottom_Item_Bias;
        return;
    }
    // 状态栏图标显示
    LCD.Display_Icon(Bar_Bottom_Item_Pos, LCD.Display_Height - (Bar_Bottom_Height - Height) / 2, Width, Height, icon, icon_color, background_color);
    Bar_Bottom_Item_Pos = Bar_Bottom_Item_Pos + Bar_Bottom_Item_Bias + Width;
}

void Class_Menu::Display_Menu_Background(uint16_t color) {
    LCD.Display_Fill(0, Bar_Top_Height, LCD.Display_Width, LCD.Display_Height - Bar_Bottom_Height, color);
}

void Class_Menu::Display_Menu(void) {
    // 菜单栏背景显示
    if (Last_Menu != NULL && Last_Menu->Menu_Item_List != NULL) {
        LCD.Display_Fill(0, Bar_Top_Height, LCD.Display_Width, Bar_Top_Height + Menu_Item_Font * Last_Menu->Menu_Count, foreground_color);
    }
    // 菜单栏选项显示
    if (Menu != NULL && Menu->Menu_Item_List != NULL) {
        int count;
        for (count = 0; count < Menu->Menu_Count; count++) {
            if (count == Menu->Menu_Index) {
                Display_Menu_Item(count, Menu->Menu_Item_List[count].Text, text_color, cursor_color);
            }
            else {
                Display_Menu_Item(count, Menu->Menu_Item_List[count].Text, text_color, foreground_color);
            }
        }
    }
}

void Class_Menu::Display_Menu_Item(uint8_t index, const uint8_t *str, uint16_t fcolor, uint16_t bcolor) {
    LCD.Display_String(Menu_Item_Bias, Bar_Top_Height + Menu_Item_Font * index, str, fcolor, bcolor, Menu_Item_Font, 0);
}

void Class_Menu::Display_Menu_Item(uint8_t index, float val, uint16_t len, uint16_t fcolor, uint16_t bcolor) {
    LCD.Display_Float(Menu_Item_Bias, Bar_Top_Height + Menu_Item_Font * index, val, len, fcolor, bcolor, Menu_Item_Font);
}

void Class_Menu::Enter_Menu_Item(void) {
    if (Menu != NULL && Menu->Menu_Item_List != NULL) {// 如果当前菜单非空
        // 菜单指针转存，上次菜单设为当前菜单，上级菜单设为当前菜单，当前菜单设为子菜单
        Last_Menu = Menu;
        Previous_Menu = Menu;
        Menu = Menu->Menu_Item_List[Menu->Menu_Index].Sub_Menu;
        // 如果进入的菜单没有菜单项，则判定为选项，开始程序
        uint8_t *flag = Previous_Menu->Menu_Item_List[Previous_Menu->Menu_Index].Status;
        if (Menu == NULL && flag != NULL) {
            *flag = 1;
        }
        // 菜单界面绘制
        Display_Menu();
    }
    else {
        // 填充触发器
        Trigger = Menu_Trigger_OK;
    }
}

void Class_Menu::Exit_Menu_Item(void) {
    if (Previous_Menu != NULL) {// 如果上级菜单非空
        // 菜单指针转存，上次菜单设为当前菜单，当前菜单设为上次菜单，上次菜单设为空菜单
        Last_Menu = Menu;
        Menu = Previous_Menu;
        Previous_Menu = Previous_Menu->Previous_Menu;
        // 如果退出的菜单没有菜单项，则判定为选项，终止程序
        uint8_t *flag = Menu->Menu_Item_List[Menu->Menu_Index].Status;
        if (Last_Menu == NULL && flag != NULL) {
            *flag = 0;
        }
        // 菜单界面绘制
        Display_Menu();
    }
    
    // 清空触发器
    Clear_Trigger();
}

void Class_Menu::Switch_UP_Menu_Item(void) {
    if (Menu != NULL && Menu->Menu_Item_List != NULL) {
        // 索引项
        uint8_t index = Menu->Menu_Index;
        // 总项数
        uint8_t count = Menu->Menu_Count;
        if (index <= 0) {// 如果索引项 = 零，则设为总项数
            index = count - 1;
        }
        else {
            index--;
        }
        Display_Menu_Item(Menu->Menu_Index, Menu->Menu_Item_List[Menu->Menu_Index].Text, text_color, foreground_color);
        Display_Menu_Item(index, Menu->Menu_Item_List[index].Text, text_color, cursor_color);
        Menu->Menu_Index = index;
    }
    else {
        Trigger = Menu_Trigger_SWITCH_UP;
    }
}

void Class_Menu::Switch_DOWN_Menu_Item(void) {
    if (Menu != NULL && Menu->Menu_Item_List != NULL) {
        // 索引项
        uint8_t index = Menu->Menu_Index;
        // 总项数
        uint8_t count = Menu->Menu_Count;
        index++;
        if (index >= count) {// 如果索引项 >= 总项数，则索引项归零
            index = 0;
        }
        // 刷新选定项
        Display_Menu_Item(Menu->Menu_Index, Menu->Menu_Item_List[Menu->Menu_Index].Text, text_color, foreground_color);
        Display_Menu_Item(index, Menu->Menu_Item_List[index].Text, text_color, cursor_color);
        Menu->Menu_Index = index;
    }
    else {
        Trigger = Menu_Trigger_SWITCH_DOWN;
    }
}
