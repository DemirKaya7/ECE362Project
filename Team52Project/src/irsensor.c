#include "irsensor.h"
#include "math.h"
#include <stdio.h>

void IrSensor_Init()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER1_Msk;
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0)
    {
    }

    ADC1->CR |= ADC_CR_ADEN;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0)
    {
    }

    ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
}

void StartSensorReading()
{
   ADC1->CR |= ADC_CR_ADSTART;
}

uint32_t WaitForAdcSensorReading()
{
   uint32_t voltage;
   while(ADC1->ISR & ADC_ISR_EOC == 0)
    {

    }
    voltage = ADC1->DR;
    return voltage;
}

static float adcToVoltage(uint32_t adcValue) {
    return ((float)adcValue / (pow(2, 12))) * 5;
}

static float adcToDistance(uint32_t adc)
{
   if(adc == 0)
   {
      return 0;
   }
   //Equation being used for now
   //Distance (cm) = 29.988 X POW(Volt , -1.173)
   float voltage = adcToVoltage(adc);
   float distance = 29.988 * pow(voltage, -1.173);
   return distance;
}

float GetIrSensorDistanceInCm()
{
   StartSensorReading();
   uint32_t adc = WaitForAdcSensorReading();
   float distance = adcToDistance(adc);
   return distance;
}
