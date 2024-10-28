#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"
#include "irsensor.h"
#include "flash.h"


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

    uint32_t write_this_thang = 46;
    Flash_Write_Integer(write_this_thang);


    uint32_t universal_step = Flash_Read_Integer();
    // init_exti(&universal_step);
    printf("uni step = %ld\n", universal_step);


    // while(1) {
    //     printf("Turning CW\n");
    //     turn_CW(&universal_step);
    //     printf("Turning CCW\n");
    //     turn_CCW(&universal_step);
    // }

}
