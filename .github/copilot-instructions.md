# GitHub Copilot Instructions - Frequency Generator Control System

This repository contains a dual-component RF frequency generator control system: embedded firmware (C/STM32) and desktop application (C#/WPF).

## Project Overview

**Purpose:** Open-source RF frequency generator control system (10 MHz - 6 GHz) with integrated power control, calibration, and real-time monitoring.

**Hardware:** STM32H743 microcontroller + MAX2871 RF synthesizer  
**License:** MIT  
**Version:** 1.0.0

## Repository Structure

```
FrequencyGeneratorControlSystem/
├── Firmware/          # STM32H743 embedded firmware (C)
├── Desktop/           # WPF desktop application (C#)
└── Documentation/     # User guides and API reference
```

## Tech Stack

### Firmware (Embedded)
- **Language:** C (C99 standard)
- **MCU:** STM32H743 (Cortex-M7, 480 MHz)
- **RTOS:** FreeRTOS
- **RF Chip:** MAX2871 PLL-based synthesizer
- **Build System:** CMake + GNU Make
- **Toolchain:** ARM GCC
- **HAL:** STM32 HAL Library
- **Peripherals:** UART (USB CDC), I2C (FRAM), ADC (monitoring), GPIO (RF control)

### Desktop (Application)
- **Language:** C# (.NET 6.0)
- **Framework:** WPF (Windows Presentation Foundation)
- **Architecture:** MVVM with Prism framework
- **UI Theme:** Material Design (MaterialDesignThemes)
- **Logging:** Serilog (file + console sinks)
- **Communication:** Serial port (USB CDC/ACM)
- **Build:** MSBuild / dotnet CLI

## Build & Test Commands

### Firmware
```bash
cd Firmware
make clean          # Clean build artifacts
make all            # Build firmware (produces .elf, .hex, .bin)
make flash          # Flash to device (requires ST-Link)
```

### Desktop Application
```bash
cd Desktop
dotnet restore      # Restore NuGet packages
dotnet build        # Build application
dotnet build -c Release  # Release build
dotnet run          # Run application
```

## Coding Conventions

### C Code (Firmware)

**Naming:**
- Functions: `lowercase_with_underscores()` (e.g., `motor_control_init()`)
- Variables: `lowercase_with_underscores` (e.g., `current_frequency`, `system_temperature`)
- Constants/Macros: `UPPERCASE_WITH_UNDERSCORES` (e.g., `MAX_FREQUENCY`, `DEFAULT_POWER`)
- Static functions: Prefix with `static` and use in implementation files only

**Style:**
- Max line length: 100 characters
- Indentation: 4 spaces (no tabs)
- Braces: K&R style (opening brace on same line)
- Documentation: Use Doxygen-style comments for public functions
```c
/**
 * @brief Initialize PWM for motor control
 * @param frequency PWM frequency in Hz
 * @return 0 on success, -1 on error
 */
int motor_pwm_init(uint32_t frequency);
```

**Practices:**
- Use STM32 HAL library functions (not direct register access unless necessary)
- Document register operations when used
- Avoid blocking delays in main loop or tasks
- Use `const` for read-only data
- Keep functions small (<50 lines preferred)
- Always check return values from HAL functions

### C# Code (Desktop)

**Naming:**
- Classes/Methods: `PascalCase` (e.g., `MainViewModel`, `InitializeMotor()`)
- Private fields: `_camelCaseWithUnderscore` (e.g., `_motorSpeed`)
- Properties: `PascalCase` (e.g., `MotorSpeed`)
- Local variables: `camelCase` (e.g., `motorSpeed`)

**Style:**
- Follow MVVM pattern strictly
- ViewModels implement `INotifyPropertyChanged` (via Prism's `BindableBase`)
- Use Prism's `SetProperty()` for property setters:
```csharp
private int _motorSpeed;
public int MotorSpeed
{
    get => _motorSpeed;
    set => SetProperty(ref _motorSpeed, value);
}
```

**Practices:**
- Use `async`/`await` for I/O operations (serial communication, file access)
- Validate user input before processing
- Handle exceptions gracefully with try-catch and user-friendly error messages
- Use dependency injection via Prism container
- Log important events using Serilog
- No business logic in Views (XAML code-behind should be minimal)
- Use Material Design components and styles

## Communication Protocol

The firmware and desktop app communicate via USB CDC serial with simple text-based commands:

**Command Format:** `COMMAND:PARAMETERS\r\n`

**Examples:**
- `FREQ:2400000000` - Set frequency to 2.4 GHz
- `POWER:5` - Set power to +5 dBm
- `RF:ON` - Enable RF output
- `STATUS:?` - Query system status

Always use `\r\n` line endings for commands.

## Important Constraints

### Do NOT:
- Remove or modify working code without good reason
- Use `any` type in TypeScript (not applicable - this is C/C# project)
- Add breaking changes to the communication protocol without versioning
- Commit sensitive data or hardware-specific calibration values to git
- Use blocking I/O in UI thread (desktop app)
- Use busy-wait loops in firmware tasks (use FreeRTOS delays)
- Directly manipulate registers unless HAL library is insufficient

### DO:
- Test firmware changes on actual hardware when possible
- Update documentation when adding new commands or features
- Follow existing architectural patterns (MVVM for desktop, task-based for firmware)
- Add comments for complex register configurations or RF calculations
- Update `CHANGELOG.md` for user-facing changes
- Validate frequency ranges (10 MHz - 6 GHz) and power ranges (-20 to +15 dBm)

## Testing Approach

### Firmware
- Manual testing on hardware is primary method
- Verify serial communication with terminal or desktop app
- Check RF output with spectrum analyzer when possible
- Monitor temperature, voltage, current readings for sanity

### Desktop
- Build and run application
- Test USB connection with firmware
- Verify UI responsiveness and error handling
- Test program creation and execution features
- No formal unit test framework currently exists (manual testing)

## Key Files to Understand

### Firmware
- `Firmware/src/main.c` - Main firmware with FreeRTOS tasks
- `Firmware/src/max2871.c` - MAX2871 RF synthesizer control
- `Firmware/src/calibration.c` - Calibration data management
- `Firmware/inc/` - Header files with function declarations

### Desktop
- `Desktop/MainWindow.xaml` - Main UI layout
- `Desktop/ViewModels/MainViewModel.cs` - Main view logic
- `Desktop/Services/UsbCommunicationService.cs` - Serial communication
- `Desktop/Models/` - Data models for frequency programs

## Documentation

When making changes:
- Update `Documentation/API_REFERENCE.md` for new commands
- Update `Documentation/USER_MANUAL.md` for new features
- Update `Documentation/TROUBLESHOOTING.md` for known issues
- Update `CHANGELOG.md` with user-facing changes

## Commit Message Format

Use conventional commits:
```
[Type] Brief description (50 chars max)

feat:     New feature
fix:      Bug fix
docs:     Documentation only
style:    Code style (formatting, no logic change)
refactor: Code refactoring
perf:     Performance improvement
test:     Add tests
```

Example: `feat: Add frequency sweep program feature`

## Questions?

- Architecture details: `Documentation/ARCHITECTURE.md`
- API commands: `Documentation/API_REFERENCE.md`
- Installation: `Documentation/INSTALLATION.md`
- Troubleshooting: `Documentation/TROUBLESHOOTING.md`

---

**Remember:** This is a dual-component system. Changes to firmware communication protocol require corresponding desktop app changes, and vice versa.
