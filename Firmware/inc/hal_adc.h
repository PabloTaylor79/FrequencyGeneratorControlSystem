#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

/**
 * ADC Driver for Temperature, Voltage and Current Monitoring
 */

typedef struct {
    double temperature;
    double voltage;
    double current;
} ADC_Readings_t;

void ADC_Init(void);
void ADC_StartConversion(void);
ADC_Readings_t ADC_GetReadings(void);
double ADC_GetTemperature(void);
double ADC_GetVoltage(void);
double ADC_GetCurrent(void);

#endif