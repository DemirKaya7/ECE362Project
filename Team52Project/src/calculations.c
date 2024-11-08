#include "stm32f0xx.h"
#include "calculations.h"
#include "stepper.h"
#include "math.h"
#include "lcd.h"
#include <stdio.h>
#include <stdint.h>

#define conversion_rate (180.0 / 1024.0)

void calculate_and_display(int * step, float distance) {
    // 180 degrees = 1024 steps
    int step_in_degrees = conversion_rate * (*step);
    printf("step in degrees = %d\n", step_in_degrees);
    u16 x = (distance * cos(step_in_degrees) * 2);     // *2 for cm to pixel
    printf("x = %d\n", x);
    u16 y = (distance * sin(step_in_degrees) * 2) + 160;     // *2 for cm to pixel
    printf("y = %d\n", y);
    u16 color = 0xFFFF;
    printf("color\n");

    // LCD_DrawPoint(x, y, color);
    LCD_DrawFillRectangle(x, y, x+5, y+5, color);
    printf("draw p\n");
}