#include "stm32f0xx.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "serial.h"
// #include "irsensor.h"
#include "lcd.h"

extern void autotest();
extern void internal_clock();

int main(void) {
    setup_serial();
    internal_clock();

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


    //init spi1 slow
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~(SPI_CR1_BR);
    SPI1->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
    SPI1->CR2 &= ~(SPI_CR2_DS_3);


    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_SSI | SPI_CR1_SSM;
    SPI1->CR2 |= SPI_CR2_TXDMAEN;

    SPI1->CR1 |= SPI_CR1_SPE;
    
    // IrSensor_Init();

    // autotest();
    // printf("setting up tim3\n");
    // setup_tim3();
    // printf("done setting up tim3\n");

    // while(1) {
    //     printf("Turning CW\n");
    //     turn_CW();
    //     printf("Turning CCW\n");
    //     turn_CCW();
    // }

    LCD_Setup();
    LCD_Clear(0x0);

    LCD_DrawFillRectangle(100, 100, 200, 200, 0x0);

    printf("drawn\n");



    // lcd_reset();
    // init_lcd();
    // draw_pixel(120, 160, 0x0);
    // draw_pixel(120, 161, 0x0);
    // draw_pixel(120, 162, 0x0);
    // draw_pixel(120, 163, 0x0);
    // draw_pixel(121, 160, 0x0);
    // draw_pixel(121, 161, 0x0);
    // draw_pixel(121, 162, 0x0);
    // draw_pixel(121, 163, 0x0);
    // draw_pixel(122, 160, 0x0);
    // draw_pixel(122, 161, 0x0);
    // draw_pixel(122, 162, 0x0);
    // draw_pixel(122, 163, 0x0);
    // printf("pixel drawn\n"); // pixel should be shown, but nothing is changing on the screen, this line is being printed
    // spi1_setup_dma();
    // spi1_enable_dma();
    // for (int i = 0; i < 240; i++) { 
    //     for (int j = 0; j < 240; j++){
    //         if (i == 0 && j == 0) {
    //             printf("drawing\n");
    //         }
    //         draw_pixel(i,j,0x0000);
    //     }
    // }
}
