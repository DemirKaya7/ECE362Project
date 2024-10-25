#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"

extern void autotest();
extern void internal_clock();



int main(void) {
    setup_serial();
    internal_clock();
    
    autotest();
    printf("setting up tim3\n");
    setup_tim3();
    printf("done setting up tim3\n");

    while(1) {
        printf("Turning CW\n");
        turn_CW();
        printf("Turning CCW\n");
        turn_CCW();
    }

    // while(1) {
    //     if ((USART5->ISR & USART_ISR_RXNE))  // if receive buffer has some data in it
    //         USART5->TDR = USART5->RDR;       // copy that data into transmit buffer.
    // }
}

