#include "hal_i2c.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"

static I2C_HandleTypeDef hi2c;

void I2C_Init(void)
{
    hi2c.Instance = I2C1;
    hi2c.Init. Timing = 0x00C0EAFF;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init. AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c. Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    
    HAL_I2C_Init(&hi2c);
}

void I2C_WriteData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{
    uint8_t buffer[256];
    buffer[0] = reg;
    for (uint16_t i = 0; i < len; i++)
        buffer[i + 1] = data[i];
    
    HAL_I2C_Master_Transmit(&hi2c, (uint16_t)(addr << 1), buffer, len + 1, HAL_MAX_DELAY);
}

void I2C_ReadData(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_I2C_Master_Transmit(&hi2c, (uint16_t)(addr << 1), &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c, (uint16_t)(addr << 1), data, len, HAL_MAX_DELAY);
}

bool I2C_IsDeviceReady(uint8_t addr)
{
    return HAL_I2C_IsDeviceReady(&hi2c, (uint16_t)(addr << 1), 3, 100) == HAL_OK;
}