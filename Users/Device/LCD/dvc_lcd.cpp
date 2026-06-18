/**
 * @brief 显示屏
 * @date 2026/6/12
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "dvc_lcd.h"

void Class_LCD::Init(SPI_INST *SPIx, Enum_LCD_Direction __Direction, GPIO_PORT *__RES_Port, GPIO_PIN __RES_Pin, GPIO_PORT *__DC_Port, GPIO_PIN __DC_Pin, GPIO_PORT *__BLK_Port, GPIO_PIN __BLK_Pin) {
    SPI = SPIx;

    Direction = __Direction;
    switch (__Direction) {
    case LCD_Direction_0:
    case LCD_Direction_180:
        Display_Width = 240;
        Display_Height = 280;
        break;
    case LCD_Direction_90:
    case LCD_Direction_270:
        Display_Width = 280;
        Display_Height = 240;
        break;
    }

    RES_Port = __RES_Port;
    RES_Pin = __RES_Pin;
    DC_Port = __DC_Port;
    DC_Pin = __DC_Pin;
    BLK_Port = __BLK_Port;
    BLK_Pin = __BLK_Pin;
}

void Class_LCD::Reset(void) {
    GPIO_Set_Pins(RES_Port, RES_Pin, STATUS_DISABLE);// 复位
    Sys_Delay(20000);
    GPIO_Set_Pins(RES_Port, RES_Pin, STATUS_ENABLE);
    Sys_Delay(20000);
    GPIO_Set_Pins(BLK_Port, BLK_Pin, STATUS_ENABLE);// 打开背光
    Write_Command(SLPOUT);// 退出睡眠模式
    Sys_Delay(120 * 1000);// 120ms
    /* 初始化程序 */
    Write_Command(MADCTL);
    switch (Direction) {
    case LCD_Direction_0:
        Write_Data8(0x00);
        break;
    case LCD_Direction_90:
        Write_Data8(0x70);
        break;
    case LCD_Direction_180:
        Write_Data8(0xC0);
        break;
    case LCD_Direction_270:
        Write_Data8(0xA0);
        break;
    default:
        break;
    }
    Write_Command(COLMOD);
    Write_Data8(0x05);

    Write_Command(PORCTRL);
    Write_Data8(0x0C);
    Write_Data8(0x0C);
    Write_Data8(0x00);
    Write_Data8(0x33);
    Write_Data8(0x33);

    Write_Command(GCTRL);
    Write_Data8(0x35);

    Write_Command(VCOMS);
    Write_Data8(0x32);

    Write_Command(VDVVRHEN);
    Write_Data8(0x01);

    Write_Command(VRHS);
    Write_Data8(0x15);

    Write_Command(VDVS);
    Write_Data8(0x20);

    Write_Command(FRCTRL2);
    Write_Data8(0x0F);

    Write_Command(PWCTRL1);
    Write_Data8(0xA4);
    Write_Data8(0xA1);

    Write_Command(0xE0);
    Write_Data8(0xD0);
    Write_Data8(0x08);
    Write_Data8(0x0E);
    Write_Data8(0x09);
    Write_Data8(0x09);
    Write_Data8(0x05);
    Write_Data8(0x31);
    Write_Data8(0x33);
    Write_Data8(0x48);
    Write_Data8(0x17);
    Write_Data8(0x14);
    Write_Data8(0x15);
    Write_Data8(0x31);
    Write_Data8(0x34);

    Write_Command(NVGAMCTRL);
    Write_Data8(0xD0);
    Write_Data8(0x08);
    Write_Data8(0x0E);
    Write_Data8(0x09);
    Write_Data8(0x09);
    Write_Data8(0x15);
    Write_Data8(0x31);
    Write_Data8(0x33);
    Write_Data8(0x48);
    Write_Data8(0x17);
    Write_Data8(0x14);
    Write_Data8(0x15);
    Write_Data8(0x31);
    Write_Data8(0x34);

    Write_Command(INVON);

    Write_Command(DISPON);
}

void Class_LCD::TIM_Write_PeriodElapsedCallback() {

}

void Class_LCD::Display_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t i, j;
    Select_Address(x1, y1, x2 - 1, y2 - 1);
    for (i = y1; i < y2; i++) {
        for (j = x1; j < x2; j++) {
            Write_Data16(color);
        }
    }
}

void Class_LCD::Display_Point(uint16_t x, uint16_t y, uint16_t color) {
    Select_Address(x, y, x, y);
    Write_Data16(color);
}

void Class_LCD::Display_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;// 计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;// 画线起点坐标
    uCol = y1;
    if (delta_x > 0) { incx = 1; }// 设置单步方向
    else if (delta_x == 0) { incx = 0; }// 垂直线
    else { incx = -1; delta_x = -delta_x; }
    if (delta_y > 0) { incy = 1; }
    else if (delta_y == 0) { incy = 0; }// 水平线
    else { incy = -1; delta_y = -delta_y; }
    if (delta_x > delta_y) { distance = delta_x; }// 选取基本增量坐标轴
    else { distance = delta_y; }
    for (t = 0; t < distance + 1; t++) {
        Display_Point(uRow, uCol, color);// 画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void Class_LCD::Display_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    Display_Line(x1, y1, x2, y1, color);
    Display_Line(x1, y1, x1, y2, color);
    Display_Line(x1, y2, x2, y2, color);
    Display_Line(x2, y1, x2, y2, color);
}

void Class_LCD::Display_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    int a, b;
    a = 0; b = r;
    while (a < b) {
        Display_Point(x - b, y - a, color);
        Display_Point(x + b, y - a, color);
        Display_Point(x - a, y + b, color);
        Display_Point(x - a, y - b, color);
        Display_Point(x + b, y + a, color);
        Display_Point(x + a, y - b, color);
        Display_Point(x + a, y + b, color);
        Display_Point(x - b, y + a, color);
        a++;
        // 判断要画的点是否过远
        if ((a * a + b * b) > (r * r)) {
            b--;
        }
    }
}

void Class_LCD::Display_Char(uint16_t x, uint16_t y, uint8_t ch, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size, uint8_t overlay) {
    uint8_t charWidth, countWidth = 0;
    uint16_t byteData, byteIndex, bitIndex, charDataBytes;
    uint16_t charX = x;

    charWidth = size / 2;// 字符宽度为高度的一半
    charDataBytes = (charWidth / 8 + ((charWidth % 8) ? 1 : 0)) * size;// 计算该字符在字库中占用的字节数

    ch = ch - ' ';// 字体列表偏移

    Select_Address(x, y, x + charWidth - 1, y + size - 1);// 设置光标窗口
    for (byteIndex = 0; byteIndex < charDataBytes; byteIndex++) {
        // 根据字体大小获取对应的点阵字节数据
        if (size == Font_Size_12_06) { byteData = ASCII_12_06[ch][byteIndex]; }
        else if (size == Font_Size_16_08) { byteData = ASCII_16_08[ch][byteIndex]; }
        else if (size == Font_Size_24_12) { byteData = ASCII_24_12[ch][byteIndex]; }
        else if (size == Font_Size_32_16) { byteData = ASCII_32_16[ch][byteIndex]; }
        else return;

        for (bitIndex = 0; bitIndex < 8; bitIndex++) {
            if (!overlay) {// 非叠加模式，批量填充窗口
                if (byteData & (0x01 << bitIndex)) { Write_Data16(fcolor); }
                else { Write_Data16(bcolor); }
                countWidth++;
                if (countWidth % charWidth == 0) {
                    countWidth = 0;
                    break;// 换行
                }
            }
            else {// 叠加模式，逐点绘制
                if (byteData & (0x01 << bitIndex)) { Display_Point(x, y, fcolor); }
                x++;
                if ((x - charX) == charWidth) {
                    x = charX;
                    y++;
                    break;// 换行
                }
            }
        }
    }
}

void Class_LCD::Display_String(uint16_t x, uint16_t y, const uint8_t *str, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size, uint8_t overlay) {
    while (*str != '\0') {
        Display_Char(x, y, *str, fcolor, bcolor, size, overlay);
        x += size / 2;
        str++;
    }
}

void Class_LCD::Display_Picture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t pic[]) {
    uint16_t countWidth, countHeight;
    uint32_t index = 0;
    Select_Address(x, y, x + width - 1, y + height - 1);
    for (countWidth = 0; countWidth < width; countWidth++) {
        for (countHeight = 0; countHeight < height; countHeight++) {
            Write_Data8(pic[index * 2]);
            Write_Data8(pic[index * 2 + 1]);
            index++;
        }
    }
}

void Class_LCD::Display_Int(uint16_t x, uint16_t y, uint16_t val, uint8_t len, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size) {
    uint8_t count, digit;
    uint8_t available = 0;
    uint8_t charWidth = size / 2;
    for (count = 0; count < len; count++) {
        digit = (val / (uint32_t)pow(10, len - count - 1)) % 10;
        if (available == 0 && count < (len - 1)) {
            if (digit == 0) {
                Display_Char(x + count * charWidth, y, ' ', fcolor, bcolor, size, 0);
                continue;
            }
            else {
                available = 1;
            }
        }
        Display_Char(x + count * charWidth, y, digit + 48, fcolor, bcolor, size, 0);
    }
}

void Class_LCD::Display_Float(uint16_t x, uint16_t y, float val, uint8_t len, uint16_t fcolor, uint16_t bcolor, Enum_Font_Size size) {
    uint8_t count, digit;
    uint8_t available = 0;
    uint8_t charWidth = size / 2;
    uint16_t val_int = val * 100;
    for (count = 0; count < len; count++) {
        digit = (val_int / (uint32_t)pow(10, len - count - 1)) % 10;
        if (count == (len - 2)) {
            Display_Char(x + (len - 2) * charWidth, y, '.', fcolor, bcolor, size, 0);
            count++;
            len += 1;
        }
        Display_Char(x + count * charWidth, y, digit + 48, fcolor, bcolor, size, 0);
    }
}

void Class_LCD::Display_Icon(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t icon[], uint16_t fcolor, uint16_t bcolor) {
    uint16_t countWidth, countHeight;
    uint32_t index = 0;
    Select_Address(x, y, x + width - 1, y + height - 1);
    for (countWidth = 0; countWidth < width; countWidth++) {
        for (countHeight = 0; countHeight < height; countHeight++) {
            if (icon[index >> 3] >> (7 - (index & 7))) { Write_Data16(fcolor); }
            else { Write_Data16(bcolor); }
            index++;
        }
    }
}

void Class_LCD::Write_Command(uint8_t Command) {
    GPIO_Set_Pins(DC_Port, DC_Pin, STATUS_DISABLE);
    Write_Data8(Command);
    GPIO_Set_Pins(DC_Port, DC_Pin, STATUS_ENABLE);
}

void Class_LCD::Write_Data8(uint8_t Data) {
    TxData[0] = Data;
    SPI_Exchange_Data(SPI, &TxData[0], NULL, 1);
}

void Class_LCD::Write_Data16(uint16_t Data) {
    TxData[0] = (Data >> 8) & 0xFF;
    TxData[1] = Data & 0xFF;
    SPI_Exchange_Data(SPI, &TxData[0], NULL, 1);
    SPI_Exchange_Data(SPI, &TxData[1], NULL, 1);
}

void Class_LCD::Select_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    switch (Direction) {
        case LCD_Direction_0:
        case LCD_Direction_180:
            Write_Command(CASET);// 列地址设置
            Write_Data16(x1);
            Write_Data16(x2);
            Write_Command(RASET);// 行地址设置
            Write_Data16(y1 + 20);
            Write_Data16(y2 + 20);
            Write_Command(RAMWR);// 储存器写
            break;
        case LCD_Direction_90:
        case LCD_Direction_270:
        default:
            Write_Command(CASET);// 列地址设置
            Write_Data16(x1 + 20);
            Write_Data16(x2 + 20);
            Write_Command(RASET);// 行地址设置
            Write_Data16(y1);
            Write_Data16(y2);
            Write_Command(RAMWR);// 储存器写
            break;
    }
}


