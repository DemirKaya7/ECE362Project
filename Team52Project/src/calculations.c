#include "calculations.h"
#include "stepper.h"
#include "math.h"
#include "lcd.h"
#include <stdio.h>

#define conversion_rate 180/1024

void calculate_and_display(int * step, float distance) {
    // 180 degrees = 1024 steps
    int step_in_degrees = conversion_rate * (*step);
    __uint16_t x = distance * cos(step_in_degrees);
    __uint16_t y = distance * sin(step_in_degrees);
    __uint16_t color = 0xFFFF

    LCD_DrawPoint(x, y, color);
}