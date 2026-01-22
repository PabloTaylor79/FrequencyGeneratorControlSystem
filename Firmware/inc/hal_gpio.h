#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * GPIO Control for RF Output and LEDs
 */

typedef enum {
    GPIO_PIN_RF_OUTPUT,
    GPIO_PIN_LED_STATUS,
    GPIO_PIN_LED_ERROR
} GPIO_Pin_t;

/* Initialization */
void GPIO_Init(void);

/* RF Control */
void GPIO_SetRFOutput(bool enable);
bool GPIO_GetRFOutput(void);

/* LED Control */
void GPIO_SetStatusLED(bool on);
void GPIO_SetErrorLED(bool on);
void GPIO_ToggleLED(GPIO_Pin_t pin);

#endif /* HAL_GPIO_H */