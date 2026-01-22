# System Architecture

## Overview

```
┌─────────────────┐
│  Desktop App    │  Windows WPF Application
│   (C# MVVM)     │
└────────┬────────┘
         │ USB CDC
         │
┌────────▼─────────┐
│   USB Interface  │  CH340G USB-to-Serial
│   (USB CDC/ACM)  │
└────────┬─────────┘
         │ Serial (UART)
         │
┌────────▼──────────────────────┐
│  STM32H743 Microcontroller   │
│  + FreeRTOS Real-Time Kernel │
└────────┬─────────────────┬───┘
         │                 │
    ┌────▼────┐      ┌────▼────┐
    │ MAX2871 │      │ Control  │
    │ (RF Gen)│      │ Circuits │
    └────┬────┘      └────┬────┘
         │                │
    ┌────▼────┐      ┌────▼────┐
    │ RF Out  │      │ Monitoring
    │ (SMA)   │      │(Temp, V, I)
    └─────────┘      └─────────┘
```

## Hardware Components

- **STM32H743ZI:** Main microcontroller (Cortex-M7 @ 480 MHz)
- **MAX2871:** RF synthesizer (10 MHz - 6 GHz)
- **CH340G:** USB-to-Serial converter
- **Temperature Sensor:** NTC thermistor
- **Power Monitor:** INA219 or similar
- **FRAM:** FM25V02 for calibration storage

## Software Architecture

### Firmware (C)

```
Firmware/
├── inc/
│   ├── main.h
│   ├── max2871.h
│   ├── hal_uart.h
│   ├── hal_gpio.h
│   ├── hal_adc.h
│   ├── hal_i2c.h
│   └── calibration.h
├── src/
│   ├── main.c
│   ├── max2871.c
│   ├── hal_uart.c
│   ├── hal_gpio.c
│   ├── hal_adc.c
│   ├── hal_i2c.c
│   └── calibration.c
├── CMakeLists.txt
├── Makefile
└── linker.ld
```

### Desktop Application (C# MVVM)

```
Desktop/
├── Services/
│   ├── IUSBCommunicationService.cs
│   ├── USBCommunicationService.cs
│   ├── IProgramManagerService.cs
│   ├── ProgramManagerService.cs
│   ├── IMonitoringService.cs
│   └── MonitoringService.cs
├── ViewModels/
│   ├── MainViewModel.cs
│   ├── RFControlViewModel.cs
│   ├── ProgramEditorViewModel.cs
│   ├── MonitoringViewModel.cs
│   ├── SettingsViewModel.cs
│   └── CalibrationViewModel.cs
├── Views/
│   ├── MainWindow.xaml
│   └── MainWindow.xaml.cs
├── Models/
│   ├── Program.cs
│   ├── ProgramStep.cs
│   ├── SystemStatus.cs
│   └── CalibrationData.cs
├── App.xaml
├── App.xaml.cs
├── App.config
└── FrequencyGeneratorApp.csproj
```

## Communication Protocol

**Layer Model:**
- Application Layer: ASCII text commands
- Transport Layer: UART communication
- Link Layer: USB CDC virtual COM port
- Physical Layer: USB Type-C connector

**Baud Rate:** 115200 bps
**Data Format:** 8-N-1 (8 bits, no parity, 1 stop bit)
**Line Termination:** \n or \r\n

## Data Flow

### Frequency Setting

```
User Input (UI)
    ↓
RFControlViewModel.SetFrequency()
    ↓
USBCommunicationService.SendCommandAsync("RF:FREQ <freq>")
    ↓
Firmware Command Parser
    ↓
MAX2871 SPI Driver
    ↓
Frequency Changed ✓
```

## Performance

- **Frequency Change:** < 100 ms
- **Power Change:** < 50 ms
- **Status Update:** 50 ms
- **Calibration Time:** ~60 seconds