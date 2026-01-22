Build with Make
bash
cd Firmware
make all
make flash
Build with CMake
bash
cd Firmware
mkdir build
cd build
cmake ..
make
Flashing
bash
st-flash write firmware.bin 0x08000000
Command Protocol
Format: COMMAND:SUBCOMMAND [parameters]\n

Examples:

Code
RF:FREQ 2400000000      › Set frequency to 2400 MHz
RF:FREQ?                › Query current frequency
RF:POWER 10             › Set power to 10 dBm
RF:OUTPUT ON            › Enable RF output
SYS:STAT?               › Get system status
See API_REFERENCE.md for complete list.

File Structure
Code
Firmware/
+¦¦ inc/
-   +¦¦ main.h          # Main header
-   +¦¦ max2871.h       # RF synthesizer
-   +¦¦ hal_uart.h      # UART/USB CDC
-   +¦¦ hal_gpio.h      # GPIO control
-   +¦¦ hal_adc.h       # ADC monitoring
-   +¦¦ hal_i2c.h       # I2C for FRAM
-   L¦¦ calibration.h   # Calibration
+¦¦ src/
-   +¦¦ main.c          # Main implementation
-   +¦¦ max2871.c
-   +¦¦ hal_uart.c
-   +¦¦ hal_gpio.c
-   +¦¦ hal_adc.c
-   +¦¦ hal_i2c.c
-   L¦¦ calibration.c
+¦¦ CMakeLists.txt      # CMake config
+¦¦ Makefile            # Make config
L¦¦ README.md           # This file
Troubleshooting
Build fails: Check ARM GCC installed
Flash fails: Check ST-Link connection
Device not responding: Check UART baudrate (115200)
Frequency wrong: Run calibration
See TROUBLESHOOTING.md for more.

More info: See INSTALLATION.md

Code

---

## **DESKTOP DODATKOWE:**

```markdown name=README.md url=https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/blob/main/Desktop/README.md
# Desktop Application

WPF desktop application for controlling the Frequency Generator.

## Overview

Modern Windows application with Material Design UI for controlling RF frequency generator via USB.

## Features

- **RF Control:** Frequency and power adjustment
- **Program Editor:** Create and run sweep programs
- **Real-time Monitoring:** Temperature, voltage, current
- **Calibration:** Automatic and manual calibration
- **Settings:** Application configuration
- **Modern UI:** Material Design theme

## Building

### Prerequisites
- Windows 10/11
- Visual Studio 2019+
- .NET Framework 4.7.2+

### Build with Visual Studio
1. File › Open › Folder
2. Navigate to Desktop folder
3. Select FrequencyGeneratorApp.csproj
4. Build Solution

### Build with Command Line
```bash
cd Desktop
dotnet restore
dotnet build -c Release
Run Application
bash
dotnet run
Project Structure
Code
Desktop/
+¦¦ Services/           # Business logic
-   +¦¦ IUSBCommunicationService.cs
-   +¦¦ USBCommunicationService.cs
-   +¦¦ IProgramManagerService.cs
-   +¦¦ ProgramManagerService.cs
-   +¦¦ IMonitoringService.cs
-   L¦¦ MonitoringService.cs
+¦¦ ViewModels/         # MVVM logic
-   +¦¦ MainViewModel.cs
-   +¦¦ RFControlViewModel.cs
-   +¦¦ ProgramEditorViewModel.cs
-   +¦¦ MonitoringViewModel.cs
-   +¦¦ SettingsViewModel.cs
-   L¦¦ CalibrationViewModel.cs
+¦¦ Views/              # WPF Windows
-   +¦¦ MainWindow.xaml
-   L¦¦ MainWindow.xaml.cs
+¦¦ Models/             # Data models
-   +¦¦ Program.cs
-   +¦¦ ProgramStep.cs
-   +¦¦ SystemStatus.cs
-   L¦¦ CalibrationData.cs
+¦¦ App.xaml            # Application XAML
+¦¦ App.xaml.cs         # Application code
+¦¦ App.config          # Configuration
L¦¦ FrequencyGeneratorApp.csproj  # Project file
Dependencies
XML
<PackageReference Include="Prism.Wpf" Version="8.1.97" />
<PackageReference Include="MaterialDesignThemes" Version="4.3.0" />
<PackageReference Include="Serilog" Version="2.10.0" />
<PackageReference Include="Serilog.Sinks.File" Version="5.0.0" />
Usage
Launch application
Select COM port
Click "Connect"
Use tabs for different functions
See USER_MANUAL.md for details.

Troubleshooting
Build fails: Check .NET installed
Cannot connect: Check COM port and baud rate
UI issues: Check MaterialDesignThemes installed
See TROUBLESHOOTING.md for more.

More info: See INSTALLATION.md

Code

---

## ? **TO WSZYSTKIE PLIKI!**

Podsumowanie:

**Firmware (C):** 7 Headers + 7 Implementacji + CMake + Makefile + README = **17 plików**

**Desktop (C#):** 4 Models + 6 ViewModels + 5 Services + 2 Views + 4 Config + README = **22 pliki**

**Dokumentacja:** 5 plików (INSTALLATION, USER_MANUAL, API_REFERENCE, TROUBLESHOOTING, ARCHITECTURE)

**Root:** 10 plików (README_FIRST, README, HOW_TO_DOWNLOAD, CHANGELOG, CONTRIBUTING, LICENSE, INDEX, .gitignore, etc.)

**RAZEM: 52+ KOMPLETNYCH PLIKÓW!**

Wszystkie pliki maj¹ kompletny kod, dokumentacjê i s¹ gotowe do u¿ytku.