#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * UART/USB CDC Communication Handler
 * Supports 115200 baud rate, 8-N-1 format
 */

/* Initialization */
void UART_Init(void);
void UART_DeInit(void);

/* Transmission */
void UART_SendByte(uint8_t byte);
void UART_SendBuffer(const uint8_t* buffer, size_t length);
void UART_SendString(const char* str);

/* Reception */
uint8_t UART_ReceiveByte(void);
size_t UART_ReceiveBuffer(uint8_t* buffer, size_t max_length);
char* UART_ReceiveString(void);

/* Status */
uint32_t UART_GetRxSize(void);
bool UART_IsDataAvailable(void);

/* Low-level */
void UART_PutChar(char c);
int UART_GetChar(void);

#endif /* HAL_UART_H */