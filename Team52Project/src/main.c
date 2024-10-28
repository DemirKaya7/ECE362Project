#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"
#include "irsensor.h"
#include "lcd.h"

extern void autotest();
extern void internal_clock();

int main(void) {
    setup_serial();
    internal_clock();
    // IrSensor_Init();

    autotest();
    // printf("setting up tim3\n");
    // setup_tim3();
    // printf("done setting up tim3\n");

    // while(1) {
    //     printf("Turning CW\n");
    //     turn_CW();
    //     printf("Turning CCW\n");
    //     turn_CCW();
    // }

    init_spi();
    lcd_reset();
    init_lcd();
    for (int i = 0; i < 240; i++) { 
        for (int j = 0; j < 240; j++){
            if (i == 0 && j == 0) {
                printf("drawing\n");
            }
            draw_pixel(i,j,0x0f00);
        }
    }
}
