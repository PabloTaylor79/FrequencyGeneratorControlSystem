# Installation Guide - Frequency Generator Control System

Complete step-by-step installation and setup instructions for both firmware and desktop application.

## Table of Contents

1. [Hardware Requirements](#hardware-requirements)
2. [Firmware Installation](#firmware-installation)
3. [Desktop Application Installation](#desktop-application-installation)
4. [Hardware Assembly](#hardware-assembly)
5. [Initial Setup](#initial-setup)
6. [Troubleshooting](#troubleshooting)

---

## Hardware Requirements

### BOM (Bill of Materials)

| Component | Part Number | Quantity | Purpose |
|-----------|------------|----------|---------|
| Microcontroller | STM32H743ZI | 1 | Main processor |
| RF Synthesizer | MAX2871 | 1 | Frequency generation |
| Power Amplifier | PE4259 | 1 | RF amplification |
| Attenuator | PE4314 | 1 | Output power control |
| Audio Amplifier | MAX98357A | 1 | Audio feedback |
| USB Hub Controller | CH340G | 1 | USB interface |
| FRAM Memory | FM25V02A | 1 | Calibration storage |
| Oscillator | 10 MHz TCXO | 1 | Reference clock |
| Power Supply | 5V/2A | 1 | Device power |
| ST-Link Debugger | ST-Link/V2 | 1 | Programming |
| USB Cable | USB Type-C | 1 | Device connection |

### Tools Required

- Soldering iron (25W+)
- Solder (lead-free, 0.5-0.8mm diameter)
- Flux pen
- Wire strippers
- Multimeter
- SMA connectors and cables
- Tweezers for SMD assembly

### Development Environment

**For Firmware:**
- Windows 10/11 or Linux
- 4GB RAM minimum
- 2GB free disk space

**For Desktop Application:**
- Windows 10/11
- 4GB RAM minimum
- 2GB free disk space

---

## Firmware Installation

### Step 1: Install ARM Toolchain

#### On Windows

1. Download ARM GCC Compiler:
   - Visit: https://developer.arm.com/downloads/-/gnu-rm
   - Download: arm-none-eabi (latest version)
   
2. Run installer and select:
   - ✅ Add path to environment variables
   - ✅ Install ARM Cortex-M support

3. Verify installation:
   ```bash
   arm-none-eabi-gcc --version
   ```

#### On Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install gcc-arm-none-eabi
sudo apt-get install gdb-arm-none-eabi
sudo apt-get install libnewlib-arm-none-eabi
```

### Step 2: Install CMake

#### Windows
```bash
# Download from: https://cmake.org/download/
# Or use package manager:
choco install cmake
```

#### Linux
```bash
sudo apt-get install cmake
```

### Step 3: Install STM32CubeIDE (Optional)

1. Download from: https://www.st.com/en/development-tools/stm32cubeide.html
2. Install and launch
3. Workspace location: Choose your project directory

### Step 4: Clone and Build Firmware

```bash
# Clone repository
git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
cd FrequencyGeneratorControlSystem/Firmware

# Build with CMake
mkdir build
cd build
cmake ..
make

# Or build with Makefile
make clean all

# Output files
# - firmware.elf (ELF executable)
# - firmware.bin (Binary image)
# - firmware.hex (Hex format for programming)
```

### Step 5: Install ST-Link Drivers

#### Windows
1. Download: https://www.st.com/en/development-tools/stsw-link009.html
2. Run installer
3. Restart computer

#### Linux
```bash
sudo apt-get install openocd
sudo apt-get install stlink-tools
```

### Step 6: Program Device

#### Using ST-Link

```bash
# Using st-flash (Linux/Mac)
st-flash write firmware.bin 0x08000000

# Using STM32 Cube Programmer (Windows)
# 1. Launch STM32CubeProgrammer
# 2. Connect via ST-Link
# 3. Open firmware.bin
# 4. Click "Download"
```

#### Using OpenOCD

```bash
# Start OpenOCD
openocd -f interface/stlink-v2.cfg -f target/stm32h7x.cfg

# In another terminal, use GDB
arm-none-eabi-gdb firmware.elf
(gdb) target remote :3333
(gdb) load
(gdb) continue
```

### Step 7: Verify Programming

1. Connect USB cable to device
2. Check if device appears as COM port in Device Manager
3. Open terminal and test:

```bash
# Linux/Mac
screen /dev/ttyUSB0 115200

# Windows
# Use Tera Term or PuTTY
# Connect to COMx, 115200 baud

# Send command
SYS:IDN?

# Should receive
FrequencyGenerator,FG-STM32H743,SN123456,1.0.0
```

---

## Desktop Application Installation

### Step 1: Install Prerequisites

#### Visual Studio 2019 or Later

1. Download from: https://visualstudio.microsoft.com/
2. Select workloads:
   - ✅ .NET desktop development
   - ✅ C# development tools
   - ✅ NuGet package manager

3. Install .NET Framework 4.7.2 or later

### Step 2: Clone Repository

```bash
git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
cd FrequencyGeneratorControlSystem/Desktop
```

### Step 3: Restore NuGet Packages

```bash
# Visual Studio
# Build → Restore NuGet Packages

# Or command line
dotnet restore
```

### Step 4: Build Application

#### Visual Studio

1. Open FrequencyGeneratorApp.sln
2. Set Configuration to Release or Debug
3. Build → Build Solution (Ctrl+Shift+B)

#### Command Line

```bash
dotnet build -c Release
```

### Step 5: Run Application

#### Visual Studio

Press F5 to start debugging, or Ctrl+F5 for release run

#### Command Line

```bash
dotnet run
```

### Step 6: Create Installer (Optional)

1. Install Inno Setup: http://www.jrsoftware.org/isinfo.php
2. Create setup.iss script:

```iss
[Setup]
AppName=Frequency Generator Control
AppVersion=1.0.0
DefaultDirName={pf}\FrequencyGenerator
DefaultGroupName=Frequency Generator
OutputDir=Output

[Files]
Source: "bin\Release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\Frequency Generator"; Filename: "{app}\FrequencyGeneratorApp.exe"
Name: "{commondesktop}\Frequency Generator"; Filename: "{app}\FrequencyGeneratorApp.exe"
```

3. Compile setup script to create installer

---

## Hardware Assembly

### PCB Layout Considerations

1. **Power Distribution:**
   - Use thick copper traces for 5V and GND
   - Add decoupling capacitors close to IC pins
   - Minimum 100µF bulk capacitor near power input

2. **RF Layout:**
   - Minimize trace lengths between MAX2871 and PE4259
   - Use 50Ω impedance matching for RF traces
   - Keep RF lines away from digital signals

3. **Clock Distribution:**
   - Keep 10MHz oscillator trace short
   - Add ferrite bead near oscillator output
   - Use ground plane under clock trace

4. **Component Placement:**
   ```
   [USB Port] ← [CH340G] ← [STM32H743]
                              ↓
                    [MAX2871] ← [TCXO 10MHz]
                              ↓
                          [PE4259]
                              ↓
                          [PE4314]
                              ↓
                        [SMA Output]
   ```

### Assembly Steps

1. **Solder Microcontroller:**
   - Use reflow oven or hot air station for BGA
   - Inspect solder joints with microscope
   - Apply flux as needed

2. **Solder RF Components:**
   - MAX2871 (QFN-20)
   - PE4259 (SOT-23)
   - PE4314 (QFN-16)

3. **Solder Support Components:**
   - FRAM (SOIC-8)
   - CH340G (SOIC-16)
   - Decoupling capacitors

4. **Install Connectors:**
   - USB Type-C connector
   - SMA connectors (RF output, reference clock)
   - Power header (if applicable)

5. **Inspection:**
   - Visual inspection for solder bridges
   - Continuity check for power/ground
   - Resistance check for RF traces (50Ω)

---

## Initial Setup

### First Power-On

1. **Prepare Device:**
   - Connect USB cable
   - Device should enumerate as Virtual COM Port
   - LED should blink (if implemented)

2. **Verify COM Port:**
   
   **Windows:**
   - Device Manager → Ports (COM & LPT)
   - Should show "USB Serial Port (COMx)"

   **Linux:**
   - `ls /dev/ttyUSB*`
   - Should show `/dev/ttyUSB0` or similar

3. **Test Connection:**
   
   ```bash
   # Using terminal
   screen /dev/ttyUSB0 115200
   
   # Send test command
   SYS:IDN?
   
   # Should respond with device info
   ```

### Calibration

1. **Frequency Calibration:**
   ```
   Connect frequency counter to RF output
   CAL:START
   Wait for completion (typically 30-60 seconds)
   CAL:SAVE
   ```

2. **Power Calibration:**
   ```
   Connect power meter to RF output
   RF:POWER 0
   CAL:POWER
   CAL:SAVE
   ```

### Desktop Application Setup

1. **First Launch:**
   - Application starts with no device connected
   - Status shows "Disconnected"

2. **Connect Device:**
   - Click "Refresh Ports"
   - Select COM port from dropdown
   - Click "Connect"
   - Status should change to "Connected"

3. **Verify Connection:**
   - System Status panel should show:
     - Firmware Version
     - Hardware Version
     - Temperature
     - Supply Voltage

---

## Troubleshooting

### Firmware Issues

#### Device not recognized as COM port

**Solution:**
```bash
# Windows: Reinstall CH340 drivers
# Download from: http://wch-ic.com/download/CH341SER_ZIP.html

# Linux: Check USB device
lsusb
# Should show: ID xxxx:xxxx ...

# Check dmesg
dmesg | tail -20
```

#### Firmware upload fails

**Solution:**
1. Check ST-Link connection
2. Verify device is in DFU mode
3. Try lower flash speed (openocd config)
4. Erase device completely:
   ```bash
   openocd -c "init; reset halt; flash erase_all; reset"
   ```

#### Device hangs after upload

**Solution:**
1. Check for infinite loops in main()
2. Verify FreeRTOS stack sizes
3. Check UART initialization
4. Use JTAG debugger to single-step

### Desktop Application Issues

#### Cannot connect to device

**Solution:**
1. Verify COM port is correct
2. Check baud rate (must be 115200)
3. Ensure no other application using port
4. Try different USB port
5. Update CH340 drivers

#### Application crashes on startup

**Solution:**
1. Ensure .NET Framework 4.7.2+ installed
2. Check Windows event log for errors
3. Run in Visual Studio debugger
4. Verify NuGet packages restored

---

**Last Updated:** 2026-01-21