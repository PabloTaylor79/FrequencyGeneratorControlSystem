#ifndef MAX2871_H
#define MAX2871_H

#include <stdint. h>
#include <stdbool.h>

/**
 * MAX2871 RF Synthesizer Driver
 * Frequency range: 10 MHz - 6 GHz
 */

typedef struct {
    uint32_t frequency_hz;
    bool pll_locked;
    uint8_t power_mode;
} MAX2871_Status_t;

/* Initialization */
void MAX2871_Init(void);
void MAX2871_DeInit(void);

/* Frequency Control */
void MAX2871_SetFrequency(uint32_t frequency_hz);
uint32_t MAX2871_GetFrequency(void);
bool MAX2871_IsPLLLocked(void);

/* Power Control */
void MAX2871_SetPowerMode(uint8_t mode);
uint8_t MAX2871_GetPowerMode(void);

/* Status */
MAX2871_Status_t MAX2871_GetStatus(void);

/* SPI Communication */
void MAX2871_WriteRegister(uint8_t reg, uint32_t data);
uint32_t MAX2871_ReadRegister(uint8_t reg);

#endif /* MAX2871_H */