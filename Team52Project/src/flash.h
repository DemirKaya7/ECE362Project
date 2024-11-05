#ifndef FLASH_H
#define FLASH_H

#include "stm32f0xx.h"

void Flash_Write_Integer(uint32_t value);
uint32_t Flash_Read_Integer(void);
void init_exti(uint32_t *);

#endif