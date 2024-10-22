#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>

extern void autotest();
extern void internal_clock();

void setup_serial(void)
{
    RCC->AHBENR |= 0x00180000;
    GPIOC->MODER  |= 0x02000000;
    GPIOC->AFR[1] |= 0x00020000;
    GPIOD->MODER  |= 0x00000020;
    GPIOD->AFR[0] |= 0x00000200;
    RCC->APB1ENR |= 0x00100000;
    USART5->CR1 &= ~0x00000001;
    USART5->CR1 |= 0x00008000;
    USART5->BRR = 0x340;
    USART5->CR1 |= 0x0000000c;
    USART5->CR1 |= 0x00000001;
}

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
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL0_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL1_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL4_Pos);
    GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFRL5_Pos);

    // set for frequency of 48000 KHz
    TIM3->PSC = 48 - 1;
    TIM3->ARR = 10000 - 1;

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
    TIM3->CCR1 = 5000;
    TIM3->CCR2 = 2500;
    TIM3->CCR3 = 1250;
    TIM3->CCR4 = 625;
}



int main(void) {
    setup_serial();
    internal_clock();
    
    autotest();
    printf("\nstart\n");
    setup_tim3();
    printf("\nsuccess\n");

    while(1) {
        if ((USART5->ISR & USART_ISR_RXNE))  // if receive buffer has some data in it
            USART5->TDR = USART5->RDR;       // copy that data into transmit buffer.
    }
}

