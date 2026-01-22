#include "hal_gpio.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"

/**
 * @brief Initialize GPIO ports
 */
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /* Enable GPIO clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    /* Configure RF Output (PA1) */
    GPIO_InitStruct. Pin = GPIO_PIN_1;
    GPIO_InitStruct. Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /* Configure Status LED (PB0) */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    /* Configure Error LED (PB1) */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * @brief Set RF output
 */
void GPIO_SetRFOutput(bool enable)
{
    if (enable)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

/**
 * @brief Get RF output state
 */
bool GPIO_GetRFOutput(void)
{
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET;
}

/**
 * @brief Set status LED
 */
void GPIO_SetStatusLED(bool on)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, on ?  GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**
 * @brief Set error LED
 */
void GPIO_SetErrorLED(bool on)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, on ? GPIO_PIN_SET :  GPIO_PIN_RESET);
}

/**
 * @brief Toggle LED
 */
void GPIO_ToggleLED(GPIO_Pin_t pin)
{
    if (pin == GPIO_PIN_LED_STATUS)
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    else if (pin == GPIO_PIN_LED_ERROR)
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
}