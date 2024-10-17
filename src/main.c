/**
  ******************************************************************************
  * @file    main.c
  * @author  Demir Kaya, Ameen Abubakr, Eric Bartzcak, Akash
  * @date    Oct 17, 2024
  * @brief   ECE 362 Team 52 Project
  ******************************************************************************
*/

#include "stm32f0xx.h"
#include <math.h>
#include <stdint.h>

void internal_clock();

int main(void) {
    internal_clock();
    printf("\nsuccess\n");
}
