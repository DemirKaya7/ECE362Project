#include "lcd.h"

void init_spi() {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN; 

    GPIOA->MODER &= ~((3 << (5 * 2)) | (3 << (7 * 2))); // Clear mode bits
    GPIOA->MODER |= (2 << (5 * 2)) | (2 << (7 * 2));    // Set to AF mode
    GPIOA->AFR[0] |= (5 << (5 * 4)) | (5 << (7 * 4));   // Set AF5 (SPI1) for PA5 and PA7

    // Configure PA4 (CS), PA6 (DC), and PA3 (RST) as general output pins
    GPIOA->MODER |= (1 << (4 * 2)) | (1 << (6 * 2)) | (1 << (3 * 2));

    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 |= SPI_CR1_BR;
    
    SPI1->CR2 |= SPI_CR2_DS_3 | SPI_CR2_DS_0;
    SPI1->CR2 &= ~(SPI_CR2_DS_2 | SPI_CR2_DS_1);

    SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_NSSP;
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_SSI | SPI_CR1_SSM;
    SPI1->CR2 |= SPI_CR2_TXDMAEN;

    SPI1->CR1 |= SPI_CR1_SPE;
}

void send_command(uint8_t command) {
    GPIOA->BSRR = (1 << 6) << 16; // DC low for command
    GPIOA->BSRR = (1 << 4) << 16; // CS low
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until TX buffer is empty
    SPI1->DR = command;
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until transmission is complete
    GPIOA->BSRR = (1 << 4);           // CS high
}

void send_data(uint8_t data) {
    GPIOA->BSRR = (1 << 6);       // DC high for data
    GPIOA->BSRR = (1 << 4) << 16; // CS low
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until TX buffer is empty
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until transmission is complete
    GPIOA->BSRR = (1 << 4);           // CS high
}

void lcd_reset() {
    GPIOA->BSRR = (1 << 3) << 16; // Set PA3 (RST) low
    for (volatile int i = 0; i < 100000; i++); // Short delay
    GPIOA->BSRR = (1 << 3);       // Set PA3 (RST) high
}

void init_lcd() {
    lcd_reset();           // Reset the LCD
    send_command(0x28);    // Display OFF
    send_command(0x11);    // Exit Sleep mode
    for (volatile int i = 0; i < 1000000; i++); // Short delay

    // Initialization sequence specific to your LCD
    send_command(0xCF);
    send_data(0x00);
    send_data(0xC1);
    send_data(0x30);

    // Additional commands for your LCD...
    send_command(0x29); // Display ON
}

void draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    // Set column address
    send_command(0x2A);
    send_data(x >> 8);
    send_data(x & 0xFF);

    // Set row address
    send_command(0x2B);
    send_data(y >> 8);
    send_data(y & 0xFF);

    // Write color data
    send_command(0x2C);
    send_data(color >> 8);
    send_data(color & 0xFF);
}