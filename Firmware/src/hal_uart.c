/**
 * UART Driver for STM32H743
 * USB CDC Virtual COM Port Communication
 */

#include "hal_uart.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include <string.h>

/* UART Handle */
static UART_HandleTypeDef huart;

/* RX Buffer */
#define RX_BUFFER_SIZE 512
static uint8_t rx_buffer[RX_BUFFER_SIZE];
static uint32_t rx_index = 0;
static uint32_t rx_start = 0;

/* ============================= */
/* INITIALIZATION                */
/* ============================= */

/**
 * @brief Initialize UART for CDC communication
 */
void UART_Init(void)
{
    /* Configure UART3 (USB CDC mapped) */
    huart.Instance = USART3;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    
    HAL_UART_Init(&huart);
    
    /* Enable RX interrupt */
    __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
}

/**
 * @brief De-initialize UART
 */
void UART_DeInit(void)
{
    HAL_UART_DeInit(&huart);
}

/* ============================= */
/* TRANSMISSION                  */
/* ============================= */

/**
 * @brief Send single byte
 */
void UART_SendByte(uint8_t byte)
{
    HAL_UART_Transmit(&huart, &byte, 1, HAL_MAX_DELAY);
}

/**
 * @brief Send buffer
 */
void UART_SendBuffer(const uint8_t* buffer, size_t length)
{
    if (buffer && length > 0)
    {
        HAL_UART_Transmit(&huart, (uint8_t*)buffer, length, HAL_MAX_DELAY);
    }
}

/**
 * @brief Send string
 */
void UART_SendString(const char* str)
{
    if (str)
    {
        UART_SendBuffer((const uint8_t*)str, strlen(str));
    }
}

/**
 * @brief Put character (for printf support)
 */
void UART_PutChar(char c)
{
    HAL_UART_Transmit(&huart, (uint8_t*)&c, 1, HAL_MAX_DELAY);
}

/* ============================= */
/* RECEPTION                     */
/* ============================= */

/**
 * @brief Receive single byte (blocking)
 */
uint8_t UART_ReceiveByte(void)
{
    uint8_t byte;
    HAL_UART_Receive(&huart, &byte, 1, HAL_MAX_DELAY);
    return byte;
}

/**
 * @brief Receive buffer
 */
size_t UART_ReceiveBuffer(uint8_t* buffer, size_t max_length)
{
    if (buffer && max_length > 0)
    {
        HAL_UART_Receive(&huart, buffer, max_length, HAL_MAX_DELAY);
        return max_length;
    }
    return 0;
}

/**
 * @brief Receive null-terminated string
 */
char* UART_ReceiveString(void)
{
    static char string_buffer[256];
    uint32_t index = 0;
    
    while (index < sizeof(string_buffer) - 1)
    {
        uint8_t byte = UART_ReceiveByte();
        
        /* Check for line endings */
        if (byte == '\n' || byte == '\r')
        {
            string_buffer[index] = '\0';
            return (index > 0) ? string_buffer : NULL;
        }
        
        /* Skip whitespace at start */
        if (index == 0 && (byte == ' ' || byte == '\t'))
            continue;
        
        /* Add character to buffer */
        string_buffer[index++] = (char)byte;
    }
    
    string_buffer[index] = '\0';
    return string_buffer;
}

/**
 * @brief Get character (for scanf support)
 */
int UART_GetChar(void)
{
    uint8_t byte;
    if (HAL_UART_Receive(&huart, &byte, 1, HAL_MAX_DELAY) == HAL_OK)
        return (int)byte;
    return -1;
}

/* ============================= */
/* STATUS                        */
/* ============================= */

/**
 * @brief Get RX buffer size
 */
uint32_t UART_GetRxSize(void)
{
    return rx_index - rx_start;
}

/**
 * @brief Check if data available
 */
bool UART_IsDataAvailable(void)
{
    return rx_index > rx_start;
}

/* ============================= */
/* HAL CALLBACKS                 */
/* ============================= */

/**
 * @brief UART RX Complete Callback
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart_inst)
{
    if (huart_inst->Instance == USART3)
    {
        rx_index++;
        if (rx_index >= RX_BUFFER_SIZE)
        {
            rx_index = 0;
        }
        
        /* Re-enable interrupt */
        __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
    }
}

/**
 * @brief UART Error Callback
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart_inst)
{
    if (huart_inst->Instance == USART3)
    {
        /* Clear error flags */
        __HAL_UART_CLEAR_OREFLAG(&huart);
        __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);
    }
}

/* ============================= */
/* PRINTF/SCANF SUPPORT          */
/* ============================= */

/**
 * @brief Redirect printf to UART
 */
#ifdef __GNUC__
int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        UART_PutChar(ptr[i]);
    }
    return len;
}
#endif

/**
 * @brief Redirect scanf from UART
 */
#ifdef __GNUC__
int _read(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        int c = UART_GetChar();
        if (c == -1)
            return i;
        ptr[i] = (char)c;
    }
    return len;
}
#endif

/* ============================= */
/* UART MSP INITIALIZATION       */
/* ============================= */

/**
 * @brief UART MSP Init Callback
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart_msp)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    if (huart_msp->Instance == USART3)
    {
        /* Enable UART3 clock */
        __HAL_RCC_USART3_CLK_ENABLE();
        
        /* Enable GPIO clocks */
        __HAL_RCC_GPIOD_CLK_ENABLE();
        
        /* Configure UART pins (PD8=TX, PD9=RX) */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
        
        /* Enable UART interrupt */
        HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
    }
}

/**
 * @brief UART MSP DeInit Callback
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart_msp)
{
    if (huart_msp->Instance == USART3)
    {
        __HAL_RCC_USART3_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8 | GPIO_PIN_9);
        HAL_NVIC_DisableIRQ(USART3_IRQn);
    }
}

/* ============================= */
/* UART IRQ HANDLER              */
/* ============================= */

/**
 * @brief UART3 Interrupt Handler
 */
void USART3_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart);
}