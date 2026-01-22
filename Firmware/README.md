# Firmware

STM32H743 microcontroller firmware for RF frequency generator control.

## Overview

This firmware runs on STM32H743 microcontroller with FreeRTOS real-time kernel.

## Features

- RF frequency synthesis (10 MHz - 6 GHz)
- Power control (-20 to +15 dBm)
- USB CDC virtual COM port communication
- Real-time monitoring (temperature, voltage, current)
- Calibration data storage in FRAM
- FreeRTOS task scheduling

## Hardware

- **MCU:** STM32H743ZI (Cortex-M7 @ 480 MHz)
- **RF Generator:** MAX2871 (SPI interface)
- **Communication:** UART3 to CH340G USB-to-Serial
- **Monitoring:** ADC for temperature/voltage/current
- **Storage:** I2C FRAM for calibration
- **Power:** 5V supply with monitoring

## Building

### Prerequisites
```bash
arm-none-eabi-gcc --version
cmake --version
make --version