#include "flash.h"
#include "stdlib.h"


// #define FLASH_USER_START_ADDR   0x0801FC00  // Start address for user data
#define FLASH_USER_START_ADDR   0x08005000  // Start address for user data
#define FLASH_USER_END_ADDR     0x08005004  // End address (4 bytes for one integer)

uint32_t * universal_step;

void Flash_Write_Integer(uint32_t value) {
    printf("we writing\n");
    // Unlock the Flash
    FLASH->KEYR = 0x45670123; // First unlock key
    FLASH->KEYR = 0xCDEF89AB; // Second unlock key

    // Wait until the Flash is ready
    while (FLASH->SR & FLASH_SR_BSY);
    printf("after while1\n");
    // Erase the sector (assume sector 1 for this example)
    FLASH->CR |= FLASH_CR_PER; // Page Erase
    FLASH->AR = FLASH_USER_START_ADDR; // Set the address for the erase
    FLASH->CR |= FLASH_CR_STRT; // Start the erase

    //
    FLASH->CR |= (FLASH_CR_ERRIE | FLASH_CR_EOPIE);
    //

    // Wait until the Flash is ready
    while (FLASH->SR & FLASH_SR_BSY);
    printf("after while2\n");
    // Clear the PER bit
    FLASH->CR &= ~FLASH_CR_PER;

    // Wait until the Flash is ready
    while (FLASH->SR & FLASH_SR_BSY);
    printf("after while3\n");
    // Program the integer
    FLASH->CR |= FLASH_CR_PG; // Set the programming bit
    *(volatile uint32_t*)FLASH_USER_START_ADDR = value; // Write the value

    //
    if(FLASH->SR & FLASH_SR_WRPERR)
    {
        printf("ERROR HERE\n");
    }
    
    //

    // Wait until the Flash is ready
    while (FLASH->SR & FLASH_SR_BSY);
    printf("after while4\n");

    // Clear the PG bit
    FLASH->CR &= ~FLASH_CR_PG;

    // Lock the Flash
    FLASH->CR |= FLASH_CR_LOCK; 
}

uint32_t Flash_Read_Integer() {
    printf("reading now\n");
    return *(volatile uint32_t*)FLASH_USER_START_ADDR; // Read the integer from Flash
}

void init_exti(uint32_t * step) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR0_0);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

	EXTI->RTSR |= EXTI_RTSR_TR0;

	EXTI->IMR |= EXTI_IMR_IM0;

	NVIC_EnableIRQ(EXTI0_1_IRQn);

    universal_step = step;
}

void EXTI0_1_IRQHandler(void) {
	EXTI->PR |= EXTI_PR_PR0;
    Flash_Write_Integer(*universal_step);
    exit(0);
}