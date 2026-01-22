#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stdbool.h>

/**
 * I2C Driver for FRAM Storage and Sensors
 */

void I2C_Init(void);
void I2C_WriteData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);
void I2C_ReadData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);
bool I2C_IsDeviceReady(uint8_t addr);

#endif