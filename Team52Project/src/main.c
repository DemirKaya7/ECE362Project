#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>

extern void autotest();
extern void internal_clock();

void setup_tim3(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // enable pb[0, 1, 4, 5] in AF (for tim3 channels 1-4) 
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_0);
    GPIOB->MODER |= GPIO_MODER_MODER0_1;
    GPIOB->MODER &= ~(GPIO_MODER_MODER1_0);
    GPIOB->MODER |= GPIO_MODER_MODER1_1;
    GPIOB->MODER &= ~(GPIO_MODER_MODER4_0);
    GPIOB->MODER |= GPIO_MODER_MODER5_1;
    GPIOB->MODER &= ~(GPIO_MODER_MODER5_0);
    GPIOB->MODER |= GPIO_MODER_MODER5_1;

    // specify AF1
    GPIOC->AFR[0] |= (1 << GPIO_AFRL_AFRL0_Pos);
    GPIOD->AFR[0] |= (1 << GPIO_AFRL_AFRL1_Pos);
    GPIOC->AFR[0] |= (1 << GPIO_AFRL_AFRL4_Pos);
    GPIOD->AFR[0] |= (1 << GPIO_AFRL_AFRL5_Pos);

    // set for frequency of 48000 KHz
    TIM3->PSC = 48000 - 1;
    TIM3->ARR = 999;

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
    // set CCR
    TIM3->CCR1 = 800;
    TIM3->CCR2 = 400;
    TIM3->CCR3 = 200;
    TIM3->CCR4 = 100;
}



int main(void) {
    internal_clock();
    autotest();
    sprintf(stdout, "\nstart\n");
    setup_tim3();
    sprintf(stdout, "\nsuccess\n");
}

