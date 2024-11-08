#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"
#include "irsensor.h"
#include "flash.h"
#include "lcd.h"
#include "calculations.h"

extern void autotest();
extern void internal_clock();

void init_all(void) {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;

    // Configure PB8 (CS), PB14 (DC), and PB11 (RST) as general output pins
    GPIOB->MODER &= ~(GPIO_MODER_MODER8_1 | GPIO_MODER_MODER14_1 | GPIO_MODER_MODER11_1);
    GPIOB->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER11_0;

    // PB5 PB3 AF
    GPIOB->MODER &= ~(GPIO_MODER_MODER3_0 | GPIO_MODER_MODER5_0);
    GPIOB->MODER |= (GPIO_MODER_MODER3_1 | GPIO_MODER_MODER5_1);
    GPIOB->AFR[0] &= ~(1 << GPIO_AFRL_AFRL3_Pos);
    GPIOB->AFR[0] &= ~(1 << GPIO_AFRL_AFRL5_Pos);


    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~(SPI_CR1_BR);
    SPI1->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
    SPI1->CR2 &= ~(SPI_CR2_DS_3);


    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_SSI | SPI_CR1_SSM;
    SPI1->CR2 |= SPI_CR2_TXDMAEN;

    SPI1->CR1 |= SPI_CR1_SPE;

}


int main(void) {
    setup_serial();
    internal_clock();
    IrSensor_Init();

    // autotest();
    setup_tim3();

    // init display
    init_all();
    LCD_Setup();
    LCD_Clear(0x0);

    uint32_t universal_step = 0;

    u16 black = 0x0000;

    while(1) {
        turn_CW(&universal_step);
        LCD_Clear(black);
        turn_CCW(&universal_step);
        LCD_Clear(black);
    }
}
