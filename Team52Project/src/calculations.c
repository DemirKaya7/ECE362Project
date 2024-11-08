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
    double step_in_degrees = conversion_rate * (*step);
    printf("step in degrees = %d\n", (int)step_in_degrees);
    u16 x = (int)(distance * sin(step_in_degrees) * 2);     // *2 for cm to pixel
    printf("x = %d\n", x);
    u16 y = (int)(distance * cos(step_in_degrees) * 2) + 160;     // *2 for cm to pixel
    printf("y = %d\n", y);
    u16 color = 0xFFFF;
    printf("color\n");

    // printf("SIN IN DEGREES = %d\n", (int)(100*sin(step_in_degrees)));
    // u16 radius = 2;
    // LCD_Circle(x, y, radius, color, color);
    // LCD_DrawPoint(x, y, color);
    LCD_DrawFillRectangle(x, y, x+2, y+2, color);
    printf("draw p\n");
}