Installation Guide - Frequency Generator Control System

## System Requirements

### Hardware Requirements
- **Microcontroller:** STM32H743ZI
- **USB Connection:** USB 2.0 High-Speed (Type-C)
- **Power Supply:** 5V DC, minimum 2A
- **Memory:** Minimum 256 MB RAM

### Software Requirements
- **Operating System:** Windows 7 or later (64-bit), Linux, or macOS
- **.NET Framework:** 4.7.2 or higher (for Desktop Application)
- **IDE:** STM32CubeIDE or Visual Studio
- **Compiler:** ARM GCC (arm-none-eabi-gcc) v9.0 or later

## Installation Steps

### 1. Clone the Repository
git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
cd FrequencyGeneratorControlSystem

### 2. Firmware Installation

#### Prerequisites
- STM32CubeIDE or STM32 Programmer CLI
- ST-Link v2 debugger
- ARM GCC toolchain

#### Steps

**Option A: Using STM32CubeIDE**

1. Open STM32CubeIDE
2. Navigate to File → Open Projects from File System
3. Select the Firmware folder
4. Click Finish
5. In Project Explorer, right-click project → Build Project (Ctrl+B)
6. Connect ST-Link to the STM32H743 board (SWD pins)
7. Click Run → Debug (F11) to program the device

**Option B: Using Command Line**

cd Firmware
make clean
make all

**Option C: Using STM32 Programmer CLI**

STM32_Programmer_CLI -c port=SWD -w Firmware/build/firmware.bin -v -rst

### 3. Desktop Application Installation

#### Prerequisites
- Visual Studio 2019 or later
- .NET Framework 4.7.2 or higher

#### Steps

1. Open Desktop/FrequencyGeneratorApp.sln in Visual Studio
2. Right-click solution → Restore NuGet Packages
3. Build the solution: Build → Build Solution (Ctrl+Shift+B)
4. Press F5 to run the application

### 4. Device Connection Configuration

1. Connect the Frequency Generator to your computer via USB Type-C cable
2. Wait for device enumeration (3-5 seconds)
3. Open Device Manager and note the COM port number
4. In the Desktop Application:
   - Go to File → Settings
   - Enter the COM port number (e.g., COM3)
   - Click Connect

## Verification

### Firmware Verification

In STM32CubeIDE Debug Console, you should see System initialized successfully message.

### Desktop Application Verification

1. Launch the application
2. Verify you see the main window with sections for Program Editor, RF Control Panel, Monitoring Dashboard, Audio Manager
3. Verify Connected status appears in the status bar

## Post-Installation

### First Steps

1. Update Firmware (Optional)
2. Calibrate Device
3. Test Basic Operation

Last Updated: 2026-01-21