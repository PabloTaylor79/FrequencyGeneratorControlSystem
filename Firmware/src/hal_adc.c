/**
 * ADC Driver for STM32H743
 * Reads: Temperature, Supply Voltage, Output Current
 */

#include "hal_adc.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include <math.h>

/* ADC Handle */
static ADC_HandleTypeDef hadc;

/* Calibration constants */
#define ADC_REF_VOLTAGE 3.3
#define ADC_RESOLUTION 4096.0

/* Temperature sensor: NTC thermistor calibration */
#define TEMP_SENSOR_SLOPE -3.5        /* mV/°C (negative for NTC) */
#define TEMP_SENSOR_OFFSET_25 750     /* mV at 25°C */
#define TEMP_25_CELSIUS 25.0

/* Voltage monitoring: 10:1 divider */
#define VOLTAGE_DIVIDER 10.0

/* Current sensing: 0.1 Ohm shunt = 100mV per Amp */
#define CURRENT_GAIN 10.0

/* ============================= */
/* INITIALIZATION                */
/* ============================= */

/**
 * @brief Initialize ADC
 */
void ADC_Init(void)
{
    hadc.Instance = ADC1;
    hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    hadc.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc.Init.LowPowerAutoWait = DISABLE;
    hadc.Init.ContinuousConvMode = ENABLE;
    hadc.Init.NbrOfConversion = 3;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc.Init.DMAContinuousRequests = DISABLE;
    hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    hadc.Init.LeftAlignment = ADC_LEFTALGN_DISABLE;
    
    HAL_ADC_Init(&hadc);
    
    /* Configure ADC channels */
    ADC_ChannelConfTypeDef sConfig = {0};
    
    /* Channel 1: Temperature (PC0 - ADC12_IN10) */
    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_387CYCLES;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    
    /* Channel 2: Voltage (PC1 - ADC12_IN11) */
    sConfig.Channel = ADC_CHANNEL_11;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    
    /* Channel 3: Current (PC2 - ADC12_IN12) */
    sConfig.Channel = ADC_CHANNEL_12;
    sConfig.Rank = ADC_REGULAR_RANK_3;
    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    
    /* Enable internal temperature sensor */
    __HAL_ADC_ENABLE_TEMP_SENSOR();
    __HAL_ADC_ENABLE_VREF();
    
    printf("ADC initialized\n");
}

/* ============================= */
/* CONVERSION CONTROL            */
/* ============================= */

/**
 * @brief Start ADC conversions
 */
void ADC_StartConversion(void)
{
    HAL_ADC_Start(&hadc);
}

/* ============================= */
/* DATA ACQUISITION              */
/* ============================= */

/**
 * @brief Get all ADC readings
 */
ADC_Readings_t ADC_GetReadings(void)
{
    ADC_Readings_t readings;
    readings.temperature = ADC_GetTemperature();
    readings.voltage = ADC_GetVoltage();
    readings.current = ADC_GetCurrent();
    return readings;
}

/**
 * @brief Get temperature from NTC thermistor
 * @return Temperature in Celsius
 */
double ADC_GetTemperature(void)
{
    /* Wait for conversion and get value */
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc);
    
    /* Convert ADC value to voltage (mV) */
    double voltage_mv = (adc_value / ADC_RESOLUTION) * ADC_REF_VOLTAGE * 1000;
    
    /* NTC thermistor: voltage decreases with temperature increase */
    /* Formula: T = T25 + (V25 - V) / SLOPE */
    double temperature = TEMP_25_CELSIUS + 
                       (TEMP_SENSOR_OFFSET_25 - voltage_mv) / TEMP_SENSOR_SLOPE;
    
    /* Bounds check: -40°C to +125°C */
    if (temperature < -40.0) temperature = -40.0;
    if (temperature > 125.0) temperature = 125.0;
    
    return temperature;
}

/**
 * @brief Get supply voltage
 * @return Voltage in Volts (0-50V measured range)
 */
double ADC_GetVoltage(void)
{
    /* Wait for conversion */
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc);
    
    /* Convert ADC value to voltage */
    /* 10:1 divider: ADC reads 0-3.3V for 0-33V input */
    /* Actual supply: 0-5V typical */
    double voltage = (adc_value / ADC_RESOLUTION) * ADC_REF_VOLTAGE * VOLTAGE_DIVIDER;
    
    /* Bounds check: 0-5.5V */
    if (voltage < 0.0) voltage = 0.0;
    if (voltage > 5.5) voltage = 5.5;
    
    return voltage;
}

/**
 * @brief Get output current
 * @return Current in Amperes
 */
double ADC_GetCurrent(void)
{
    /* Wait for conversion */
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc);
    
    /* Convert ADC value to voltage */
    double voltage = (adc_value / ADC_RESOLUTION) * ADC_REF_VOLTAGE;
    
    /* Current sense: 0.1 Ohm shunt resistor */
    /* 100mV per 1A: I = V / 0.1 = V * 10 */
    double current = voltage * CURRENT_GAIN;
    
    /* Bounds check: 0-2A */
    if (current < 0.0) current = 0.0;
    if (current > 2.0) current = 2.0;
    
    return current;
}

/* ============================= */
/* ADC MSP INITIALIZATION        */
/* ============================= */

/**
 * @brief ADC MSP Init Callback
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc_msp)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    if (hadc_msp->Instance == ADC1)
    {
        /* Enable ADC1 clock */
        __HAL_RCC_ADC12_CLK_ENABLE();
        
        /* Enable GPIO clock */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        
        /* Configure ADC input pins as analog */
        /* PC0, PC1, PC2 */
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
        printf("ADC GPIO initialized\n");
    }
}

/**
 * @brief ADC MSP DeInit Callback
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc_msp)
{
    if (hadc_msp->Instance == ADC1)
    {
        __HAL_RCC_ADC12_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
    }
}