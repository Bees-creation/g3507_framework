/**
 * @brief 显示屏
 * @date 2026/6/12
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_LCD_H
#define DVC_LCD_H

#include "dvc_font.h"

#include "Drivers/SPI/drv_spi.h"
#include "Algorithm/Math/alg_math.h"

typedef enum Enum_LCD_Direction {
    LCD_Direction_0 = 0,
    LCD_Direction_90,
    LCD_Direction_180,
    LCD_Direction_270,
} Enum_LCD_Direction;

/* 颜色列表 */
#define WHITE 0xFFFF // 白色
#define BLACK 0x0000 // 黑色
#define BLUE 0x001F // 蓝色
#define BRED 0xF81F
#define GRED 0xFFE0
#define GBLUE 0x07FF
#define RED 0xF800 // 红色
#define MAGENTA 0xF81F // 品红色
#define GREEN 0x07E0 // 绿色
#define CYAN 0x7FFF // 青色
#define YELLOW 0xFFE0 // 黄色
#define BROWN 0xBC40 // 棕色
#define BRRED 0xFC07 // 棕红色
#define GRAY 0x8430 // 灰色
#define DARKBLUE 0x01CF // 深蓝色
#define LIGHTBLUE 0x7D7C // 浅蓝色
#define GRAYBLUE 0x5458 // 灰蓝色
#define LIGHTGREEN 0x841F // 浅绿色
#define LGRAY 0xC618 // 浅灰色，窗体背景色
#define LGRAYBLUE 0xA651 // 浅灰蓝色，中间层颜色
#define LBBLUE 0x2B12 // 浅棕蓝色，选择条目的反色

/* 寄存器列表 */
#define SLPOUT 0x11 // 退出睡眠模式
#define INVON 0x21 // 反色显示
#define DISPON 0x29 // 显示开
#define CASET 0x2A // 32位列地址集[XS[15:0], XE[15:0]]，其中XS[7:0]为起始列地址，XE[7:0]为结束列地址
#define RASET 0x2B // 32位行地址集[YS[15:0], YE[15:0]]，其中YS[15:0]为起始行地址，YE[15:0]为结束行地址
#define RAMWR 0x2C // 存储器写入
#define MADCTL 0x36 // 存储器数据访问控制[MY, MX, MV, ML, RGB, MH, -, -]
#define COLMOD 0x3A // 接口像素格式[0, D6, D5, D4, 0, D2, D1, D0]
#define PORCTRL 0xB2 // 显示沿设置
#define GCTRL 0xB7 // 栅极驱动电压设置
#define VCOMS 0xBB // 参考电压设置
#define VDVVRHEN 0xC2 // VDV和VRH使能
#define VRHS 0xC3 // 升压电路高位电压设置
#define VDVS 0xC4 // 驱动电压调节值
#define FRCTRL2 0xC6 // 正常模式下的帧率控制
#define PWCTRL1 0xD0 // 电源控制1
#define PVGAMCTRL 0xE0 // 正极性电压伽马控制
#define NVGAMCTRL 0xE1 // 负极性电压伽马控制

class Class_LCD {
public:
    uint16_t Display_Width;
    uint16_t Display_Height;

    void Init(SPI_INST *SPIx, Enum_LCD_Direction __Direction, GPIO_PORT *__RES_Port, GPIO_PIN __RES_Pin, GPIO_PORT *__DC_Port, GPIO_PIN __DC_Pin, GPIO_PORT *__BLK_Port, GPIO_PIN __BLK_Pin);

    void Reset(void);
    
    void TIM_Write_PeriodElapsedCallback();

    void Display_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

    void Display_Point(uint16_t x, uint16_t y, uint16_t color);

    void Display_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

    void Display_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

    void Display_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

    void Display_Char(uint16_t x, uint16_t y, uint8_t ch, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size, uint8_t overlay);

    void Display_String(uint16_t x, uint16_t y, const uint8_t *str, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size, uint8_t overlay);

    void Display_Picture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t pic[]);

    void Display_Int(uint16_t x, uint16_t y, uint16_t val, uint8_t len, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size);

    void Display_Float(uint16_t x, uint16_t y, float val, uint8_t len, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size);
    
    void Display_Icon(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t icon[], uint16_t fcolor, uint16_t bcolor);

protected:
    SPI_INST *SPI;

    Enum_LCD_Direction Direction;

    GPIO_PORT *RES_Port;
    GPIO_PIN RES_Pin;
    GPIO_PORT *DC_Port;
    GPIO_PIN DC_Pin;
    GPIO_PORT *BLK_Port;
    GPIO_PIN BLK_Pin;

    uint8_t TxData[2];

    void Write_Command(uint8_t Command);
    
    void Write_Data8(uint8_t Data);
    void Write_Data16(uint16_t Data);

    void Select_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
};

#endif /* DVC_LCD_H */
