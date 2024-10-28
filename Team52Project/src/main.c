#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"
#include "irsensor.h"

extern void autotest();
extern void internal_clock();

int main(void) {
    setup_serial();
    internal_clock();
    IrSensor_Init();

    autotest();
    printf("setting up tim3\n");
    setup_tim3();
    printf("done setting up tim3\n");

    int universal_step = 0;
    while(1) {
        printf("Turning CW\n");
        turn_CW(&universal_step);
        printf("Turning CCW\n");
        turn_CCW(&universal_step);
    }
}
