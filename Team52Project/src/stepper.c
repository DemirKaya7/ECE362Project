#include "stm32f0xx.h"
#include "stepper.h"
#include <math.h>
#include <stdio.h>
#include "irsensor.h"

#define LOOPVAL 10000
#define CCRVAL 1000
#define STEPS_180 1024
//100000 loop value works

void turn_CW(int * step) {
    int current_step = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while(current_step < STEPS_180) {
        for(i = 0; i < LOOPVAL; i++) {
            TIM3->CCR1 = CCRVAL;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = 0;
        }
        i = 0;
        current_step++;
        (*step)++;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(j = 0; j < LOOPVAL; j++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = CCRVAL;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = 0;
        }
        j = 0;
        current_step++;
        (*step)++;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(k = 0; k < LOOPVAL; k++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = CCRVAL;
            TIM3->CCR4 = 0;
        }
        k = 0;
        current_step++;
        (*step)++;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(l = 0; l < LOOPVAL; l++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = CCRVAL;
        }
        l = 0;
        current_step++;
        (*step)++;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
        printf("step = %d\n", (*step));
    }
}

void turn_CCW(int * step) {
    int current_step = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while(current_step < STEPS_180)
    {
        for(i = 0; i < LOOPVAL; i++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = CCRVAL;
        }
        i = 0;
        current_step++;
        (*step)--;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(j = 0; j < LOOPVAL; j++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = CCRVAL;
            TIM3->CCR4 = 0;
        }
        j = 0;
        current_step++;
        (*step)--;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(k = 0; k < LOOPVAL; k++) {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = CCRVAL;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = 0;
        }
        k = 0;
        current_step++;
        (*step)--;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());

        for(l = 0; l < LOOPVAL; l++) {
            TIM3->CCR1 = CCRVAL;
            TIM3->CCR2 = 0;
            TIM3->CCR3 = 0;
            TIM3->CCR4 = 0;
        }
        l = 0;
        current_step++;
        (*step)--;
        // printf("%d cm\n", (int)GetIrSensorDistanceInCm());
        printf("step = %d\n", (*step));
    }
}

void setup_tim3(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // enable pb[0, 1, 4, 5] in AF (for tim3 channels 1-4)
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5);
    GPIOB->MODER |= (GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1 | GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1);

    // specify AF1
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL0_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL1_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL4_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL5_Pos);

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
