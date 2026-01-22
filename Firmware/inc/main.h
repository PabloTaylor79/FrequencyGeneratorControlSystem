#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* System Configuration */
#define SYSTEM_CLOCK_HZ 480000000UL
#define UART_BAUD_RATE 115200

/* RF Parameters */
#define RF_FREQ_MIN 10000000UL      /* 10 MHz */
#define RF_FREQ_MAX 6000000000UL    /* 6 GHz */
#define RF_POWER_MIN -20            /* dBm */
#define RF_POWER_MAX 15             /* dBm */

/* Temperature Limits */
#define TEMP_WARNING 70             /* °C */
#define TEMP_SHUTDOWN 85            /* °C */

/* =========================== */
/* SYSTEM INITIALIZATION       */
/* =========================== */
void SystemInit(void);
void SystemDeInit(void);
int SystemRun(void);

/* =========================== */
/* RF CONTROL FUNCTIONS        */
/* =========================== */
void RF_Init(void);
void RF_SetFrequency(uint32_t frequency_hz);
void RF_SetPower(int8_t power_dbm);
void RF_Enable(bool enable);
void Attenuator_SetPower(int8_t power_dbm);

/* =========================== */
/* MONITORING FUNCTIONS        */
/* =========================== */
void Monitor_Init(void);
void Monitor_Update(void);
double Monitor_GetTemperature(void);
double Monitor_GetVoltage(void);
double Monitor_GetCurrent(void);

/* =========================== */
/* CALIBRATION FUNCTIONS       */
/* =========================== */
void Calibration_Init(void);
void Calibration_LoadFromFRAM(void);
void Calibration_SaveToFRAM(void);

/* =========================== */
/* UART COMMUNICATION          */
/* =========================== */
void UART_Init(void);
void UART_SendString(const char* str);
void UART_SendByte(uint8_t byte);
char* UART_ReceiveString(void);

/* =========================== */
/* GPIO CONTROL                */
/* =========================== */
void GPIO_Init(void);
void GPIO_SetRFOutput(bool enable);
bool GPIO_GetRFOutput(void);
void GPIO_SetStatusLED(bool on);
void GPIO_SetErrorLED(bool on);

/* =========================== */
/* ADC MONITORING              */
/* =========================== */
void ADC_Init(void);
void ADC_StartConversion(void);
double ADC_GetTemperature(void);
double ADC_GetVoltage(void);
double ADC_GetCurrent(void);

/* =========================== */
/* I2C COMMUNICATION           */
/* =========================== */
void I2C_Init(void);
void I2C_WriteData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);
void I2C_ReadData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);
bool I2C_IsDeviceReady(uint8_t addr);

/* =========================== */
/* MAX2871 RF SYNTHESIZER      */
/* =========================== */
void MAX2871_Init(void);
void MAX2871_SetFrequency(uint32_t frequency_hz);
uint32_t MAX2871_GetFrequency(void);
bool MAX2871_IsPLLLocked(void);

#endif /* MAIN_H */