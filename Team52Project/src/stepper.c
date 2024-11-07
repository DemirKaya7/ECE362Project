#include "stm32f0xx.h"
#include "stepper.h"
#include <math.h>
#include <stdio.h>
#include "irsensor.h"

#define LOOPVAL 10000
#define CCRVAL 1000
#define STEPS_180 1024
//100000 loop value works

// write an ISR for button interrupt


void turn_CW(uint32_t * step) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while((*step) <= STEPS_180) {
        switch((*step) % 4)
        {
            case 0:
                for(i = 0; i < LOOPVAL; i++) {
                    TIM3->CCR1 = CCRVAL;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = 0;
                }
                i = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 1:
                for(j = 0; j < LOOPVAL; j++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = CCRVAL;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = 0;
                }
                j = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 2:
                for(k = 0; k < LOOPVAL; k++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = CCRVAL;
                    TIM3->CCR4 = 0;
                }
                k = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 3:
                for(l = 0; l < LOOPVAL; l++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = CCRVAL;
                }
                l = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;
        }
        (*step)++;
        printf("step = %ld\n", (*step));
    }
}

void turn_CCW(uint32_t * step) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while((*step) > 0) {
        switch((*step) % 4)
        {
            case 3:
                for(i = 0; i < LOOPVAL; i++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = CCRVAL;
                }
                i = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 2:
                for(j = 0; j < LOOPVAL; j++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = CCRVAL;
                    TIM3->CCR4 = 0;
                }
                j = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 1:
                for(k = 0; k < LOOPVAL; k++) {
                    TIM3->CCR1 = 0;
                    TIM3->CCR2 = CCRVAL;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = 0;
                }
                k = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;

            case 0:
                for(l = 0; l < LOOPVAL; l++) {
                    TIM3->CCR1 = CCRVAL;
                    TIM3->CCR2 = 0;
                    TIM3->CCR3 = 0;
                    TIM3->CCR4 = 0;
                }
                l = 0;
                // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
                break;
        }
        (*step)--;
        printf("step = %ld\n", (*step));
    }
}

void setup_tim3(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // enable pB[6,7,8,9] -> [] in AF (for tim3 channels 1-4)
    GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOC->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1 | GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);

    // set for frequency of 48000 KHz
    TIM3->PSC = 480 - 1;
    TIM3->ARR = 1000 - 1;

    // enable PWM mode 1 and enable timer
    TIM3->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
    TIM3->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
    TIM3->CCMR2 |= (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
    TIM3->CCMR2 |= (TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2);

    TIM3->CCER |= TIM_CCER_CC1E;
    TIM3->CCER |= TIM_CCER_CC2E;
    TIM3->CCER |= TIM_CCER_CC3E;
    TIM3->CCER |= TIM_CCER_CC4E;
    TIM3->CR1 |= TIM_CR1_CEN;
}
