/**
 * @brief 菜单任务
 * @date 2026/6/14
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "tsk_menu.h"

/** 在此处引用任务函数头文件 -- begin -- */
#include "Tasks/Motion/tsk_motion.h"
/** 在此处引用任务函数头文件 --  end  -- */

/* 图片文件 */
#include "Algorithm/Graphics/alg_graphics.h"
#include "Device/LCD/dvc_icon.h"

/** 在此处定义任务函数 -- begin -- */
extern Class_Menu Menu_Object;

// 空任务模板
static inline void _Void_T(void) {
    static Enum_Menu_Item_State Void_Task_State = Menu_Item_State_IDLE;
    switch (Void_Task_State) {
    case Menu_Item_State_IDLE:
        // 空闲态，打印信息，并进入配置态
        Menu_Object.Display_Menu_Item(0, (const uint8_t*)"Press OK To Exit.");
        Void_Task_State = Menu_Item_State_CONFIG;
    case Menu_Item_State_CONFIG:
        // 配置态，处理输入，在特定条件下进入运行态
        Void_Task_State = Menu_Item_State_RUNNING;
    case Menu_Item_State_RUNNING:
        // 运行态，运行自动程序，在特定条件下进入退出态
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK) {
            Void_Task_State = Menu_Item_State_STOPPING;
            Menu_Object.Clear_Trigger();
        }
        break;
    case Menu_Item_State_STOPPING:
        // 退出态，进行善后工作，并回到空闲态
        Menu_Object.Hide_Menu_Item(0);
        Menu_Object.Exit_Menu_Item();
        Void_Task_State = Menu_Item_State_IDLE;
        break;
    }
}

// 配置任务模板
void _Config_T(uint8_t *name, float &para, float min, float max, float step) {
    static Enum_Menu_Item_State Config_Task_State = Menu_Item_State_IDLE;
    switch (Config_Task_State) {
    case Menu_Item_State_IDLE:
        Menu_Object.Display_Menu_Item(0, name);
        Menu_Object.Display_Menu_Value(1, para);
        Config_Task_State = Menu_Item_State_CONFIG;
    case Menu_Item_State_CONFIG:
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK) {
            Config_Task_State = Menu_Item_State_RUNNING;
            Menu_Object.Clear_Trigger();
        }
        if (Menu_Object.Get_Trigger() == Menu_Trigger_SWITCH_DOWN) {
            para += step;
            if (para < min) {
                para = max;
            } else if (para > max) {
                para = min;
            }
            Menu_Object.Display_Menu_Value(1, para);
            Menu_Object.Clear_Trigger();
        }
        break;
    case Menu_Item_State_RUNNING:
        Config_Task_State = Menu_Item_State_STOPPING;
    case Menu_Item_State_STOPPING:
        Menu_Object.Hide_Menu_Item(0);
        Menu_Object.Hide_Menu_Item(1);
        Menu_Object.Exit_Menu_Item();
        Config_Task_State = Menu_Item_State_IDLE;
        break;
    }
}

void Line_Tracking(void) {
    // 目标圈数
    static uint8_t rounds = 1;
    uint8_t flag = STATUS_BUSY;
    static Enum_Menu_Item_State Void_Task_State = Menu_Item_State_IDLE;
    switch (Void_Task_State) {
    case Menu_Item_State_IDLE:
        Menu_Object.Display_Menu_Item(0, (uint8_t *)"rounds");
        Menu_Object.Display_Menu_Value(1, (uint16_t)rounds);
        Void_Task_State = Menu_Item_State_CONFIG;
    case Menu_Item_State_CONFIG:
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK) {
            Menu_Object.Display_Menu_Item(2, (uint8_t *)"running");
            Void_Task_State = Menu_Item_State_RUNNING;
            Menu_Object.Clear_Trigger();
        }
        if (Menu_Object.Get_Trigger() == Menu_Trigger_SWITCH_DOWN) {
            rounds += 1;
            if (rounds < 1) {
                rounds = 5;
            } else if (rounds > 5) {
                rounds = 1;
            }
            Menu_Object.Display_Menu_Value(1, (uint16_t)rounds);
            Menu_Object.Clear_Trigger();
        }
        break;
    case Menu_Item_State_RUNNING:
        flag = Motion_Trace(500, rounds);
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK || flag == STATUS_DONE) {
            Void_Task_State = Menu_Item_State_STOPPING;
            Menu_Object.Clear_Trigger();
        }
        break;
    case Menu_Item_State_STOPPING:
        rounds = 0;
        Motion_Stop();
        Menu_Object.Hide_Menu_Item(0);
        Menu_Object.Hide_Menu_Item(1);
        Menu_Object.Hide_Menu_Item(2);
        Menu_Object.Exit_Menu_Item();
        Void_Task_State = Menu_Item_State_IDLE;
        break;
    }
}

void Target_Detection(void) {
    uint8_t flag = STATUS_BUSY;
    static Enum_Menu_Item_State Void_Task_State = Menu_Item_State_IDLE;
    switch (Void_Task_State) {
    case Menu_Item_State_IDLE:
        Menu_Object.Display_Menu_Item(0, (const uint8_t*)"running");
        Void_Task_State = Menu_Item_State_CONFIG;
    case Menu_Item_State_CONFIG:
        Void_Task_State = Menu_Item_State_RUNNING;
    case Menu_Item_State_RUNNING:
        flag = Visual_Trace();
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK || flag == STATUS_DONE) {
            Void_Task_State = Menu_Item_State_STOPPING;
            Menu_Object.Clear_Trigger();
        }
        break;
    case Menu_Item_State_STOPPING:
        Menu_Object.Hide_Menu_Item(0);
        Menu_Object.Exit_Menu_Item();
        Void_Task_State = Menu_Item_State_IDLE;
        break;
    }
}

void Auto_Aim(void) {
    _Void_T();
}

void Config_Kp(void) {
    float& Kpl = chassis.Left_Motor.Omega_Loop.Get_K_P();
    float& Kpr = chassis.Right_Motor.Omega_Loop.Get_K_P();
    _Config_T((uint8_t*)"Kp", Kpl, 50.0f, 150.0f, 10.0f);
    Kpr = Kpl;
}

void _Display_Cube(CubeRenderer::ScreenPoint _pts[8], uint16_t color) {
    Class_LCD &lcd = Menu_Object.Get_LCD();
    lcd.Display_Line(_pts[0].x, _pts[0].y, _pts[1].x, _pts[1].y, color);
    lcd.Display_Line(_pts[1].x, _pts[1].y, _pts[2].x, _pts[2].y, color);
    lcd.Display_Line(_pts[2].x, _pts[2].y, _pts[3].x, _pts[3].y, color);
    lcd.Display_Line(_pts[3].x, _pts[3].y, _pts[0].x, _pts[0].y, color);
    lcd.Display_Line(_pts[4].x, _pts[4].y, _pts[5].x, _pts[5].y, color);
    lcd.Display_Line(_pts[5].x, _pts[5].y, _pts[6].x, _pts[6].y, color);
    lcd.Display_Line(_pts[6].x, _pts[6].y, _pts[7].x, _pts[7].y, color);
    lcd.Display_Line(_pts[7].x, _pts[7].y, _pts[4].x, _pts[4].y, color);
    lcd.Display_Line(_pts[0].x, _pts[0].y, _pts[4].x, _pts[4].y, color);
    lcd.Display_Line(_pts[1].x, _pts[1].y, _pts[5].x, _pts[5].y, color);
    lcd.Display_Line(_pts[2].x, _pts[2].y, _pts[6].x, _pts[6].y, color);
    lcd.Display_Line(_pts[3].x, _pts[3].y, _pts[7].x, _pts[7].y, color);
}

void About(void) {
    // 立方体渲染器
    static CubeRenderer renderer(240, 280);
    static CubeRenderer::ScreenPoint pts[8];
    static float time = 0.0f;

    static Enum_Menu_Item_State Config_Task_State = Menu_Item_State_IDLE;
    switch (Config_Task_State) {
    case Menu_Item_State_IDLE:
        Menu_Object.Get_LCD().Display_String(32, 44, (const uint8_t*)"Github @Bees-creation", LIGHTBLUE, foreground_color, Font_Size_16_08, 0);
        Config_Task_State = Menu_Item_State_CONFIG;
        break;
    case Menu_Item_State_CONFIG:
        Config_Task_State = Menu_Item_State_RUNNING;
    case Menu_Item_State_RUNNING:
        if (Menu_Object.Get_Trigger() == Menu_Trigger_OK) {
            Config_Task_State = Menu_Item_State_STOPPING;
            Menu_Object.Clear_Trigger();
        }
        _Display_Cube(pts, foreground_color);
        // 计算当前帧的8个屏幕坐标
        renderer.computeScreenPoints(time * 0.8f, time * 1.2f, time * 0.5f, pts);
        // 计算颜色
        _Display_Cube(pts, CubeRenderer::_rgb565Gen(time));
        time += 0.2f;
        break;
    case Menu_Item_State_STOPPING:
        _Display_Cube(pts, foreground_color);
        Menu_Object.Get_LCD().Display_Fill(0, 44, 240, 60, foreground_color);
        Menu_Object.Exit_Menu_Item();
        Config_Task_State = Menu_Item_State_IDLE;
        break;
    }
}
/** 在此处定义任务函数 --  end  -- */

/* 任务状态 */
void (*Task_List[])(void) = { Line_Tracking, Target_Detection, Auto_Aim, Config_Kp, About, };
constexpr uint8_t TASK_NUMS = (sizeoflist(Task_List));
uint8_t Task_Status[TASK_NUMS];

extern Struct_Menu Home;
extern Struct_Menu Runs;
extern Struct_Menu Options;

/* 菜单项 = { 显示名称, 任务标志位指针, 下级菜单指针 } */

Struct_Menu_Item Home_Item_List[] = {
    { (const uint8_t*)"Runs", NULL, &Runs },
    { (const uint8_t*)"Options", NULL, &Options },
};

Struct_Menu_Item Runs_Item_List[] = {
    { (const uint8_t*)"..", NULL, &Home },
    { (const uint8_t*)"Line Tracking", &Task_Status[0], NULL },
    { (const uint8_t*)"Target Detection", &Task_Status[1], NULL },
    { (const uint8_t*)"Auto Aim", &Task_Status[2], NULL },
};

Struct_Menu_Item Options_Item_List[] = {
    { (const uint8_t*)"..", NULL, &Home },
    { (const uint8_t*)"Config Kp", &Task_Status[3], NULL },
    { (const uint8_t*)"About", &Task_Status[4], NULL },
};

/* 菜单 = { 菜单项列表, 菜单项列表大小, 上级菜单指针 } */
Struct_Menu Home = {
    Home_Item_List, (sizeoflist(Home_Item_List)), NULL,
};

Struct_Menu Runs = {
    Runs_Item_List, (sizeoflist(Runs_Item_List)), &Home,
};

Struct_Menu Options = {
    Options_Item_List, (sizeoflist(Options_Item_List)), &Home,
};

Class_LCD LCD_Object;
Class_Menu Menu_Object(LCD_Object, &Home);
Class_Key Key_OK;

void _Key_OK_Function(void) {
    Menu_Object.Enter_Menu_Item();
}

void _Key_DOWN_Function(void) {
    Menu_Object.Switch_DOWN_Menu_Item();
}

void Menu_Init(void) {
    SPI_DMA_Init(SPI1, DMA, -1, DMA_CHANNEL_2, CS_PORT, CS_PIN, 0, LCD_Callback);
    LCD_Object.Init(SPI1, LCD_Direction_180, RES_PORT, RES_PIN, DC_PORT, DC_PIN, BLK_PORT, BLK_PIN);
    LCD_Object.Reset();
    Key_OK.Init(KEY_OK_PORT, KEY_OK_PIN, _Key_DOWN_Function, _Key_OK_Function);
    /* 显示屏开始绘制 */
    Menu_Object.Display_Home();
}

void Menu_Item_Task(void) {
    uint8_t _Task_Status[TASK_NUMS];

    // 临界区内复制有效列表
    taskENTER_CRITICAL();
    for (int i = 0; i < TASK_NUMS; i++) {
        _Task_Status[i] = Task_Status[i];
    }
    taskEXIT_CRITICAL();

    for (int i = 0; i < TASK_NUMS; i++) {
        if (_Task_Status[i] && Task_List[i] != NULL) {
            Task_List[i]();
        }
    }
}

void Menu_Task(void) {
    Key_OK.TIM_Detect_PeriodElapsedCallback();
}

void LCD_Callback(uint8_t *Buffer, uint16_t Length) {

}
