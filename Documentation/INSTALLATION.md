# Installation Guide

## Prerequisites

### For Firmware Development
- ARM GCC Toolchain (arm-none-eabi-gcc)
- CMake 3.15+
- GNU Make
- ST-Link Debugger and Drivers
- STM32CubeIDE (optional)

### For Desktop Application
- Windows 10/11
- Visual Studio 2019+
- .NET Framework 4.7.2+
- Git

## Installation Steps

### Firmware Setup (Linux/Mac/Windows)

1. **Install ARM GCC Toolchain**
   ```bash
   # Linux (Ubuntu/Debian)
   sudo apt-get install build-essential gcc-arm-none-eabi

   # macOS
   brew install gcc-arm-embedded

   # Windows
   # Download from: https://developer.arm.com/downloads/-/gnu-rm
   ```

2. **Install CMake and Make**
   ```bash
   # Linux
   sudo apt-get install cmake make

   # macOS
   brew install cmake make

   # Windows
   # Download from https://cmake.org and https://www.gnu.org/software/make/
   ```

3. **Clone Repository**
   ```bash
   git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
   cd FrequencyGeneratorControlSystem
   ```

4. **Build Firmware**
   ```bash
   cd Firmware
   mkdir build
   cd build
   cmake ..
   make
   ```

5. **Flash to Device**
   ```bash
   make flash
   # or use st-flash directly
   st-flash write firmware.bin 0x08000000
   ```

### Desktop Application Setup (Windows)

1. **Clone Repository**
   ```bash
   git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
   cd FrequencyGeneratorControlSystem
   ```

2. **Open in Visual Studio**
   - File → Open → Folder
   - Navigate to Desktop folder
   - Select FrequencyGeneratorApp.csproj

3. **Restore NuGet Packages**
   ```bash
   cd Desktop
   dotnet restore
   ```

4. **Build Application**
   ```bash
   dotnet build -c Release
   ```

5. **Run Application**
   ```bash
   dotnet run
   ```

## Troubleshooting

See [TROUBLESHOOTING.md](TROUBLESHOOTING.md) for common issues.