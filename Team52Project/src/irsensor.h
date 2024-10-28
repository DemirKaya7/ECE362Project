#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "stm32f0xx.h"

void IrSensor_Init(void);
void StartSensorReading(void);
uint32_t WaitForAdcSensorReading(void);
uint32_t GetIrSensor(void);

#endif
