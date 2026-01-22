/**
 * MAX2871 RF Synthesizer Driver
 * Frequency Range: 10 MHz - 6 GHz
 * Communication: SPI
 */

#include "max2871.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>

/* SPI Handle */
static SPI_HandleTypeDef hspi;

/* Status variables */
static uint32_t current_frequency = 2400000000UL;
static bool pll_locked = false;

/* ============================= */
/* INITIALIZATION                */
/* ============================= */

/**
 * @brief Initialize MAX2871 RF Synthesizer
 */
void MAX2871_Init(void)
{
    /* Initialize SPI for MAX2871 */
    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_32BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    
    HAL_SPI_Init(&hspi);
    
    printf("MAX2871 SPI initialized\n");
    
    /* Set default frequency (2400 MHz) */
    MAX2871_SetFrequency(2400000000UL);
    
    printf("MAX2871 initialized - Freq: 2400 MHz\n");
}

/**
 * @brief De-initialize MAX2871
 */
void MAX2871_DeInit(void)
{
    HAL_SPI_DeInit(&hspi);
}

/* ============================= */
/* FREQUENCY CONTROL             */
/* ============================= */

/**
 * @brief Set RF frequency
 * @param frequency_hz Frequency in Hz (10 MHz - 6 GHz)
 */
void MAX2871_SetFrequency(uint32_t frequency_hz)
{
    if (frequency_hz < 10000000UL || frequency_hz > 6000000000UL)
    {
        printf("MAX2871: Frequency out of range\n");
        return;
    }
    
    current_frequency = frequency_hz;
    
    /**
     * MAX2871 Frequency Calculation
     * R_DIVIDER = 25 MHz (reference)
     * N_VALUE = frequency / (R_DIVIDER / R)
     * Simplified: N = frequency / 25MHz
     */
    
    uint32_t n_divider = frequency_hz / 25000000UL;
    
    /* Write to MAX2871 register 0 (N value) */
    MAX2871_WriteRegister(0, n_divider);
    
    /* Wait for PLL to lock */
    HAL_Delay(100);
    pll_locked = true;
    
    printf("MAX2871: Frequency set to %lu Hz (N=%lu)\n", frequency_hz, n_divider);
}

/**
 * @brief Get current frequency
 */
uint32_t MAX2871_GetFrequency(void)
{
    return current_frequency;
}

/**
 * @brief Check if PLL is locked
 */
bool MAX2871_IsPLLLocked(void)
{
    return pll_locked;
}

/* ============================= */
/* POWER CONTROL                 */
/* ============================= */

/**
 * @brief Set power mode
 */
void MAX2871_SetPowerMode(uint8_t mode)
{
    if (mode > 3)
        return;
    
    uint32_t config = (mode & 0x03) << 24;
    MAX2871_WriteRegister(4, config);
    
    printf("MAX2871: Power mode set to %u\n", mode);
}

/**
 * @brief Get power mode
 */
uint8_t MAX2871_GetPowerMode(void)
{
    /* TODO: Read from register */
    return 0;
}

/* ============================= */
/* STATUS                        */
/* ============================= */

/**
 * @brief Get device status
 */
MAX2871_Status_t MAX2871_GetStatus(void)
{
    MAX2871_Status_t status;
    status.frequency_hz = current_frequency;
    status.pll_locked = pll_locked;
    status.power_mode = 0;
    return status;
}

/* ============================= */
/* SPI COMMUNICATION             */
/* ============================= */

/**
 * @brief Write 32-bit register via SPI
 */
void MAX2871_WriteRegister(uint8_t reg, uint32_t data)
{
    uint32_t spi_data = (data << 3) | (reg & 0x07);
    
    /* Pull CS low */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(1);
    
    /* Send 32-bit data */
    HAL_SPI_Transmit(&hspi, (uint8_t*)&spi_data, 4, HAL_MAX_DELAY);
    
    /* Pull CS high */
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

/**
 * @brief Read 32-bit register via SPI
 */
uint32_t MAX2871_ReadRegister(uint8_t reg)
{
    uint32_t spi_data = 0;
    
    /* Pull CS low */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(1);
    
    /* Read 32-bit data */
    HAL_SPI_Receive(&hspi, (uint8_t*)&spi_data, 4, HAL_MAX_DELAY);
    
    /* Pull CS high */
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    
    return spi_data;
}

/* ============================= */
/* MAX2871 MSP INITIALIZATION    */
/* ============================= */

/**
 * @brief SPI MSP Init
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi_msp)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    if (hspi_msp->Instance == SPI1)
    {
        /* Enable SPI1 clock */
        __HAL_RCC_SPI1_CLK_ENABLE();
        
        /* Enable GPIO clocks */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* Configure SPI pins */
        /* PA5=SCK, PA6=MISO, PA7=MOSI, PA4=CS */
        GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        /* Configure CS pin (PA4) */
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    }
}