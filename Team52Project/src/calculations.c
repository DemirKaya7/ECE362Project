#include "stm32f0xx.h"
#include "calculations.h"
#include "stepper.h"
#include "math.h"
#include "lcd.h"
#include <stdio.h>
#include <stdint.h>

#define conversion_rate (M_PI / 1024)

void calculate_and_display(int * step, float distance) {
    // 180 degrees = 1024 steps
    double step_in_degrees = conversion_rate * (1024 - (*step));
    u16 x = (distance * sin(step_in_degrees) * 2);     // *2 for cm to pixel
    u16 y = (distance * cos(step_in_degrees) * 2) + 160;     // *2 for cm to pixel
    u16 white = 0xFFFF;
    u16 black = 0x0000;
    // printf("SIN IN DEGREES = %d\n", (int)(100*sin(step_in_degrees)));
    // u16 radius = 2;
    // LCD_Circle(x, y, radius, color, color);
    // LCD_DrawPoint(x, y, color);
    // LCD_DrawLine(0, 160, x, y, white);
    LCD_DrawFillRectangle(x, y, x+1, y+1, white);
}