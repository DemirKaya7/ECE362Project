#ifndef LCD_H
#define LCD_H

#include "stm32f0xx.h"

void init_spi();
void init_lcd();
void send_comand(uint8_t);
void send_data(uint8_t);
void init_oled();
void lcd_reset();
void draw_pixel(uint16_t, uint16_t, uint16_t);

void spi1_setup_dma();
void spi1_enable_dma();

#endif