# Frequency Generator Control System

A comprehensive open-source project for controlling a wideband frequency generator (10 MHz - 6 GHz) based on STM32H743 microcontroller with WPF desktop application.

## 🎯 Project Overview

This project provides a complete solution for generating and controlling RF frequencies across a wide range (10 MHz to 6 GHz) with the following capabilities:

- **RF Frequency Generation:** Covers 10 MHz to 6 GHz range
- **Power Control:** Adjustable output power (-20 to +15 dBm)
- **Frequency Sweep:** Programmable linear frequency sweeps
- **Audio Integration:** Built-in audio feedback system
- **Real-time Monitoring:** Temperature, voltage, and current monitoring
- **Calibration System:** Automated device calibration
- **Desktop Application:** User-friendly WPF interface

## 📋 System Architecture

### Hardware Components

- **Microcontroller:** STM32H743ZI (Arm Cortex-M7)
- **RF Generator:** MAX2871 Frequency Synthesizer
- **Power Amplifier:** PE4259 CMOS Switch
- **Output Switch:** PE4314 Attenuator
- **Audio Output:** MAX98357A Class D Amplifier
- **Memory:** FRAM (Ferroelectric RAM) for calibration data
- **Interface:** USB Type-C with CDC/ACM support

### Software Components

1. **Firmware (C):** STM32H743 bare-metal with FreeRTOS
2. **Desktop App (C#):** WPF application with MVVM pattern
3. **Communication:** USB CDC (Virtual COM Port)

## 🚀 Quick Start

### Prerequisites

**Firmware Development:**
- ARM GCC Toolchain (arm-none-eabi-gcc)
- STM32CubeIDE
- CMake or Make
- ST-Link debugger

**Desktop Application:**
- Visual Studio 2019+
- .NET Framework 4.7.2+
- Windows 10 or later

### Building the Firmware

```bash
cd Firmware
make clean all
make flash
```

### Building the Desktop Application

```bash
cd Desktop
dotnet build
dotnet run
```

## 📁 Repository Structure

```
FrequencyGeneratorControlSystem/
├── Firmware/                    # STM32H743 firmware
│   ├── src/                    # Source files
│   ├── inc/                    # Header files
│   ├── drivers/                # Device drivers
│   ├── CMakeLists.txt
│   └── Makefile
├── Desktop/                    # WPF Desktop Application
│   ├── ViewModels/
│   ├── Views/
│   ├── Services/
│   ├── Models/
│   └── *.csproj
├── Documentation/              # Project documentation
│   ├── README.md
│   ├── INSTALLATION.md
│   ├── USER_MANUAL.md
│   ├── API_REFERENCE.md
│   ├── TROUBLESHOOTING.md
│   └── ARCHITECTURE.md
├── LICENSE
├── CONTRIBUTING.md
└── .gitignore
```

## 📚 Documentation

- **[Installation Guide](Documentation/INSTALLATION.md)** - Setup and hardware assembly
- **[User Manual](Documentation/USER_MANUAL.md)** - Complete usage guide
- **[API Reference](Documentation/API_REFERENCE.md)** - Command protocol documentation
- **[Troubleshooting](Documentation/TROUBLESHOOTING.md)** - Common issues and solutions
- **[Architecture](Documentation/ARCHITECTURE.md)** - System design details
- **[Contributing](CONTRIBUTING.md)** - Contribution guidelines

## 🎮 Features

### Frequency Control
- Precise frequency setting from 10 MHz to 6 GHz
- Real-time frequency adjustment
- Frequency sweep with configurable ramp time

### Program Management
- Create and save frequency sweep programs
- Multi-step program execution
- Program parameters: start frequency, stop frequency, ramp time, dwell time

### Monitoring & Safety
- Real-time temperature monitoring
- Voltage and current measurement
- Automatic thermal shutdown
- PLL lock detection
- Over-current protection

### Calibration
- Automated frequency calibration
- Power level calibration
- Calibration data storage in FRAM
- Factory reset capability

### Desktop Application
- Intuitive MVVM architecture
- Program editor with visual timeline
- Real-time system monitoring dashboard
- Settings and configuration panel
- Firmware update utility

## 🔧 Technology Stack

**Firmware:**
- C (ISO C11)
- FreeRTOS real-time kernel
- STM32 Hardware Abstraction Layer (HAL)

**Desktop Application:**
- C# (.NET Framework 4.7.2)
- WPF (Windows Presentation Foundation)
- Prism MVVM framework
- Material Design themes

## 📡 Communication Protocol

The device uses a simple text-based command protocol over USB CDC:

```
Command Format: COMMAND:SUBCOMMAND <parameters>
Response Format: OK or ERROR: <message>

Example:
  → RF:FREQ 2400000000
  ← OK

  → RF:FREQ?
  ← 2400000000
```

See [API Reference](Documentation/API_REFERENCE.md) for complete command documentation.

## 🧪 Testing

### Firmware Tests
```bash
cd Firmware
make test
```

### Desktop Application Tests
```bash
cd Desktop
dotnet test
```

## 🐛 Known Issues

- Initial connection may require 500ms delay for device initialization
- Large program files (>1000 steps) may require extended USB timeout
- Some COM port drivers may conflict with legacy serial software

See [Troubleshooting](Documentation/TROUBLESHOOTING.md) for more details.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for:
- Code style guidelines
- Commit conventions
- Pull request process
- Testing requirements

## 📬 Support

- 📖 Check the [Documentation](Documentation/) folder
- 🐛 Report issues on [GitHub Issues](https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/issues)
- 💬 Use [GitHub Discussions](https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/discussions)

## ✨ Roadmap

- [ ] Web-based interface
- [ ] Linux/macOS application
- [ ] Advanced signal analysis features
- [ ] Firmware OTA updates
- [ ] Extended frequency range support

## 🎓 Learning Resources

This project demonstrates:
- Embedded systems programming (STM32, FreeRTOS)
- USB device communication
- RF/microwave system design
- Desktop application development (WPF, MVVM)
- Cross-platform communication protocols

## 📊 Project Statistics

- **Firmware Size:** ~150 KB
- **Supported Frequencies:** 10 MHz - 6 GHz
- **Power Range:** -20 to +15 dBm
- **Frequency Resolution:** 1 Hz
- **Sweep Time:** 0.1 - 3600 seconds
- **Calibration Points:** 256

## ⭐ Acknowledgments

- STMicroelectronics for STM32 platform
- FreeRTOS for real-time kernel
- Prism framework for MVVM support
- Material Design for UI themes

---

**Status:** Active Development  
**Last Updated:** 2026-01-21 19:06:49  
**Version:** 1.0.0