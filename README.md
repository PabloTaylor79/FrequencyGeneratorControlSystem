# Frequency Generator Control System v1.0.0

A complete open-source RF frequency generator control system for generating signals from 10 MHz to 6 GHz with integrated power control, calibration, and real-time monitoring.

## Features

### Hardware Capabilities
- **Frequency Range:** 10 MHz - 6 GHz
- **Power Range:** -20 to +15 dBm
- **Synthesizer:** MAX2871 PLL-based RF generator
- **Microcontroller:** STM32H743 (480 MHz Cortex-M7)
- **Real-time Kernel:** FreeRTOS
- **Temperature Monitoring:** NTC thermistor
- **Power Monitoring:** Voltage and current measurement
- **Calibration Storage:** FRAM (Ferroelectric RAM)

### Software Features
- **Desktop Application:** WPF with modern Material Design UI
- **MVVM Architecture:** Prism framework for clean code
- **USB Communication:** Virtual COM port (CDC/ACM)
- **Program Management:** Create and run frequency sweep programs
- **Calibration System:** Automatic calibration with data storage
- **Real-time Monitoring:** Live temperature, voltage, and current display
- **Command Protocol:** Simple text-based commands over serial

### Developer Features
- **Complete Source Code:** Both firmware and desktop application
- **Comprehensive Documentation:** Installation, API, troubleshooting
- **Build System:** CMake for firmware, MSBuild for desktop
- **Open Source:** MIT License - free to use and modify
- **Well-Documented:** API reference and user manual included

## Project Structure

```
FrequencyGeneratorControlSystem/
├── Firmware/                    # STM32H743 Embedded Code
│   ├── inc/                    # Headers (8 files)
│   ├── src/                    # Source files (8 files)
│   ├── CMakeLists.txt         # CMake build config
│   ├── Makefile               # GNU Make build
│   └── README.md
│
├── Desktop/                     # WPF Desktop Application
│   ├── Services/              # USB communication, program management
│   ├── ViewModels/            # MVVM ViewModels
│   ├── Views/                 # WPF XAML windows
│   ├── Models/                # Data models
│   ├── FrequencyGeneratorApp.csproj
│   ├── App.xaml
│   └── README.md
│
├── Documentation/              # Complete Guides
│   ├── INSTALLATION.md        # Setup instructions
│   ├── USER_MANUAL.md         # Usage guide
│   ├── API_REFERENCE.md       # Command reference
│   ├── TROUBLESHOOTING.md     # Problem solving
│   └── ARCHITECTURE.md        # System design
│
├── README.md                  # This file
├── HOW_TO_DOWNLOAD.md
├── INSTALLATION.md
├── CHANGELOG.md
├── CONTRIBUTING.md
├── LICENSE                    # MIT License
└── .gitignore
```

## Quick Start

### Download
```bash
git clone https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem.git
cd FrequencyGeneratorControlSystem
```

### Build Firmware
```bash
cd Firmware
make all
make flash  # if ST-Link connected
```

### Build Desktop App
```bash
cd Desktop
dotnet build -c Release
dotnet run
```

## System Requirements

### Firmware Development
- ARM GCC Toolchain
- CMake 3.15+
- GNU Make
- ST-Link debugger

### Desktop Application
- Windows 10/11
- Visual Studio 2019+
- .NET Framework 4.7.2+

### Hardware
- STM32H743 microcontroller
- MAX2871 RF synthesizer
- USB interface (CH340G or similar)
- Supporting components

## Installation

See [INSTALLATION.md](Documentation/INSTALLATION.md) for detailed setup instructions.

## Usage

See [USER_MANUAL.md](Documentation/USER_MANUAL.md) for complete usage guide.

## API Reference

See [API_REFERENCE.md](Documentation/API_REFERENCE.md) for all commands.

## Troubleshooting

See [TROUBLESHOOTING.md](Documentation/TROUBLESHOOTING.md) for common issues and solutions.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines.

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

## Support

- **GitHub Issues:** https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/issues
- **GitHub Discussions:** https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/discussions
- **Documentation:** See Documentation/ folder

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history.

## Version

**Current Version:** 1.0.0  
**Release Date:** 2026-01-22  
**Status:** Stable

## Author

**PabloTaylor79** - Full-stack development, hardware design, documentation

## Acknowledgments

- Prism MVVM Framework
- STM32 HAL Library
- FreeRTOS Real-Time Kernel
- Material Design for WPF

## Keywords

RF Frequency Generator, STM32H743, MAX2871, WPF MVVM, Open Source, C, C#, Embedded Systems, USB Communication, Calibration System

---

**Ready to get started?** Read [README_FIRST.md](README_FIRST.md) for a quick introduction.