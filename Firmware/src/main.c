/**
 * Frequency Generator Control System - Main Firmware
 * STM32H743 + MAX2871 RF Generator (10 MHz - 6 GHz)
 * 
 * Features:
 * - RF frequency synthesis using MAX2871
 * - Power control with attenuator
 * - Real-time monitoring (Temperature, Voltage, Current)
 * - USB CDC serial communication
 * - FreeRTOS real-time kernel
 * - Calibration data storage in FRAM
 */

#include "main.h"

/* FreeRTOS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* ============================= */
/* GLOBAL STATE VARIABLES       */
/* ============================= */
static uint32_t current_frequency = 2400000000UL;
static int8_t current_power = 0;
static bool rf_enabled = false;

static double system_temperature = 25.0;
static double system_voltage = 5.0;
static double system_current = 0.0;

/* FreeRTOS handles */
static TaskHandle_t monitor_task_handle = NULL;
static TaskHandle_t rf_control_task_handle = NULL;
static TaskHandle_t command_task_handle = NULL;
static SemaphoreHandle_t uart_semaphore = NULL;

/* ============================= */
/* FORWARD DECLARATIONS          */
/* ============================= */
static void MonitorTask(void *pvParameters);
static void RFControlTask(void *pvParameters);
static void CommandTask(void *pvParameters);
static void ProcessCommand(const char* command);

/* ============================= */
/* SYSTEM INITIALIZATION         */
/* ============================= */

/**
 * @brief Initialize entire system
 */
void SystemInit(void)
{
    /* Initialize hardware in correct order */
    
    /* 1. UART first (for debugging/commands) */
    UART_Init();
    printf("\n");
    printf("====================================\n");
    printf("Frequency Generator Control System\n");
    printf("STM32H743 + MAX2871\n");
    printf("v1.0.0\n");
    printf("====================================\n\n");
    
    /* 2. GPIO initialization */
    GPIO_Init();
    printf("[OK] GPIO initialized\n");
    
    /* 3. ADC initialization */
    ADC_Init();
    printf("[OK] ADC initialized\n");
    
    /* 4. I2C initialization */
    I2C_Init();
    printf("[OK] I2C initialized\n");
    
    /* 5. Calibration initialization */
    Calibration_Init();
    printf("[OK] Calibration initialized\n");
    
    /* 6. Load calibration from FRAM */
    Calibration_LoadFromFRAM();
    printf("[OK] Calibration loaded from FRAM\n");
    
    /* 7. RF subsystem initialization */
    MAX2871_Init();
    printf("[OK] MAX2871 RF Synthesizer initialized\n");
    
    /* 8. Create UART semaphore for thread-safe printf */
    uart_semaphore = xSemaphoreCreateMutex();
    
    printf("\nSystem initialization complete!\n");
    printf("Ready for commands...\n\n");
}

/**
 * @brief De-initialize system
 */
void SystemDeInit(void)
{
    printf("Shutting down system...\n");
    
    /* Disable RF output */
    RF_Enable(false);
    printf("[OK] RF output disabled\n");
    
    /* Save calibration to FRAM */
    Calibration_SaveToFRAM();
    printf("[OK] Calibration saved to FRAM\n");
    
    /* Delete FreeRTOS tasks */
    if (monitor_task_handle != NULL)
        vTaskDelete(monitor_task_handle);
    if (rf_control_task_handle != NULL)
        vTaskDelete(rf_control_task_handle);
    if (command_task_handle != NULL)
        vTaskDelete(command_task_handle);
    
    printf("System shutdown complete\n");
}

/* ============================= */
/* FREERTOS TASKS                */
/* ============================= */

/**
 * @brief Monitor task - reads sensors every 1 second
 */
static void MonitorTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    
    printf("[MonitorTask] Started\n");
    
    /* Start ADC conversion */
    ADC_StartConversion();
    
    while (1)
    {
        /* Update sensor readings */
        Monitor_Update();
        
        /* Check thermal shutdown */
        if (system_temperature > TEMP_SHUTDOWN)
        {
            RF_Enable(false);
            printf("[ERROR] THERMAL SHUTDOWN! Temp=%.1f°C\n", system_temperature);
        }
        /* Check temperature warning */
        else if (system_temperature > TEMP_WARNING)
        {
            printf("[WARNING] High temperature: %.1f°C\n", system_temperature);
        }
        
        /* Periodic wait */
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/**
 * @brief RF control task - maintains RF output
 */
static void RFControlTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(500);
    
    printf("[RFControlTask] Started\n");
    
    while (1)
    {
        /* Check PLL lock if RF is enabled */
        if (rf_enabled)
        {
            if (!MAX2871_IsPLLLocked())
            {
                printf("[WARNING] PLL not locked at %.0f Hz\n", (double)current_frequency);
            }
        }
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/**
 * @brief Command processing task - handles UART commands
 */
static void CommandTask(void *pvParameters)
{
    printf("[CommandTask] Started - waiting for commands...\n");
    
    while (1)
    {
        /* Wait for incoming command */
        char* command = UART_ReceiveString();
        
        if (command != NULL && strlen(command) > 0)
        {
            ProcessCommand(command);
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* ============================= */
/* RF CONTROL IMPLEMENTATION     */
/* ============================= */

/**
 * @brief Initialize RF subsystem
 */
void RF_Init(void)
{
    MAX2871_Init();
    printf("[OK] RF subsystem initialized\n");
}

/**
 * @brief Set RF frequency
 */
void RF_SetFrequency(uint32_t frequency_hz)
{
    if (frequency_hz < RF_FREQ_MIN || frequency_hz > RF_FREQ_MAX)
    {
        printf("ERROR: Frequency out of range\n");
        printf("Valid range: 10 MHz - 6 GHz\n");
        return;
    }
    
    current_frequency = frequency_hz;
    MAX2871_SetFrequency(frequency_hz);
    
    printf("OK\n");
}

/**
 * @brief Set RF power level
 */
void RF_SetPower(int8_t power_dbm)
{
    if (power_dbm < RF_POWER_MIN || power_dbm > RF_POWER_MAX)
    {
        printf("ERROR: Power out of range\n");
        printf("Valid range: -20 to +15 dBm\n");
        return;
    }
    
    current_power = power_dbm;
    Attenuator_SetPower(power_dbm);
    
    printf("OK\n");
}

/**
 * @brief Control attenuator for power adjustment
 */
void Attenuator_SetPower(int8_t power_dbm)
{
    /**
     * PE4314 Digital Attenuator Control
     * Maps -20 to +15 dBm to 0-31 control value
     * Each step = 0.5 dB
     */
    
    uint8_t atten_value;
    
    /* Convert power to attenuation value */
    /* Formula: atten = (15 - power) / 0.5 */
    atten_value = (uint8_t)((15 - power_dbm) * 2);
    
    if (atten_value > 63)
        atten_value = 63;
    
    /* TODO: Write to PE4314 via GPIO or SPI */
    /* For now, just track the value */
    (void)atten_value;
}

/**
 * @brief Enable/disable RF output
 */
void RF_Enable(bool enable)
{
    rf_enabled = enable;
    GPIO_SetRFOutput(enable);
    
    if (enable)
    {
        GPIO_SetStatusLED(true);
        printf("OK\n");
    }
    else
    {
        GPIO_SetStatusLED(false);
        printf("OK\n");
    }
}

/* ============================= */
/* MONITORING IMPLEMENTATION     */
/* ============================= */

/**
 * @brief Initialize monitoring subsystem
 */
void Monitor_Init(void)
{
    ADC_Init();
}

/**
 * @brief Update all monitoring values
 */
void Monitor_Update(void)
{
    system_temperature = ADC_GetTemperature();
    system_voltage = ADC_GetVoltage();
    system_current = ADC_GetCurrent();
}

/**
 * @brief Get current temperature
 */
double Monitor_GetTemperature(void)
{
    return system_temperature;
}

/**
 * @brief Get current supply voltage
 */
double Monitor_GetVoltage(void)
{
    return system_voltage;
}

/**
 * @brief Get current consumption
 */
double Monitor_GetCurrent(void)
{
    return system_current;
}

/* ============================= */
/* COMMAND PROCESSING            */
/* ============================= */

/**
 * @brief Process incoming command from UART
 */
static void ProcessCommand(const char* command)
{
    if (command == NULL || strlen(command) == 0)
        return;
    
    /* System commands */
    if (strncmp(command, "SYS:IDN?", 8) == 0)
    {
        printf("FrequencyGenerator,FG-STM32H743,SN123456,1.0.0\n");
    }
    else if (strncmp(command, "SYS:RESET", 9) == 0)
    {
        printf("OK\n");
        NVIC_SystemReset();
    }
    else if (strncmp(command, "SYS:STAT?", 9) == 0)
    {
        printf("TEMP:%.1f,VOLT:%.2f,CURR:%.2f\n", 
               system_temperature, system_voltage, system_current);
    }
    
    /* RF Frequency commands */
    else if (strncmp(command, "RF:FREQ ", 8) == 0)
    {
        uint32_t freq = strtoul(&command[8], NULL, 10);
        RF_SetFrequency(freq);
    }
    else if (strncmp(command, "RF:FREQ?", 8) == 0)
    {
        printf("%lu\n", current_frequency);
    }
    
    /* RF Power commands */
    else if (strncmp(command, "RF:POWER ", 9) == 0)
    {
        int8_t power = (int8_t)strtol(&command[9], NULL, 10);
        RF_SetPower(power);
    }
    else if (strncmp(command, "RF:POWER?", 9) == 0)
    {
        printf("%d\n", current_power);
    }
    
    /* RF Output commands */
    else if (strcmp(command, "RF:OUTPUT ON") == 0)
    {
        RF_Enable(true);
    }
    else if (strcmp(command, "RF:OUTPUT OFF") == 0)
    {
        RF_Enable(false);
    }
    else if (strncmp(command, "RF:OUTPUT?", 10) == 0)
    {
        printf("%s\n", rf_enabled ? "ON" : "OFF");
    }
    
    /* Program commands */
    else if (strncmp(command, "PROG:RUN", 8) == 0)
    {
        printf("OK\n");
    }
    else if (strncmp(command, "PROG:STOP", 9) == 0)
    {
        printf("OK\n");
    }
    
    /* Calibration commands */
    else if (strncmp(command, "CAL:START", 9) == 0)
    {
        printf("OK\n");
    }
    else if (strncmp(command, "CAL:SAVE", 8) == 0)
    {
        Calibration_SaveToFRAM();
        printf("OK\n");
    }
    
    /* Unknown command */
    else
    {
        printf("ERROR: Unknown command\n");
    }
}

/* ============================= */
/* MAIN ENTRY POINT              */
/* ============================= */

/**
 * @brief Main function - entry point
 */
int main(void)
{
    /* Initialize system hardware */
    SystemInit();
    
    /* Create FreeRTOS tasks */
    xTaskCreate(MonitorTask, 
                "Monitor", 
                512, 
                NULL, 
                2, 
                &monitor_task_handle);
    
    xTaskCreate(RFControlTask, 
                "RFControl", 
                256, 
                NULL, 
                1, 
                &rf_control_task_handle);
    
    xTaskCreate(CommandTask, 
                "Command", 
                512, 
                NULL, 
                3, 
                &command_task_handle);
    
    printf("Starting FreeRTOS scheduler...\n\n");
    
    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    printf("FATAL ERROR: Scheduler returned!\n");
    while (1);
    
    return 0;
}

/* ============================= */
/* FREERTOS HOOKS                */
/* ============================= */

/**
 * @brief Stack overflow handler
 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
    printf("\n!!! STACK OVERFLOW !!!\n");
    printf("Task: %s\n", pcTaskName);
    
    GPIO_SetErrorLED(true);
    
    while (1);
}

/**
 * @brief Memory allocation failed handler
 */
void vApplicationMallocFailedHook(void)
{
    printf("\n!!! MALLOC FAILED !!!\n");
    
    GPIO_SetErrorLED(true);
    
    while (1);
}

/**
 * @brief Idle hook - called when scheduler has no tasks
 */
void vApplicationIdleHook(void)
{
    __WFI();  /* Wait For Interrupt - reduces power */
}

/**
 * @brief Tick hook - called at each tick interrupt
 */
void vApplicationTickHook(void)
{
    /* Optional: periodic tasks here */
}

/**
 * @brief Get free heap size
 */
size_t xPortGetFreeHeapSize(void)
{
    return xGetFreeHeapSize();
}