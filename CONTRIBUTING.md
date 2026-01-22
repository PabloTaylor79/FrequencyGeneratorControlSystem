# Contributing Guidelines

Thank you for your interest in contributing to the Frequency Generator Control System project!

## How to Contribute

### 1. Report Issues

If you find a bug or have a feature request:

1. Check existing [GitHub Issues](https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/issues)
2. If not reported, create a new issue
3. Include:
   - Clear description
   - Steps to reproduce (for bugs)
   - Expected vs actual behavior
   - Screenshots (if applicable)
   - System information (OS, version)

### 2. Submit Code Changes

#### Fork Repository
```bash
# Fork on GitHub
git clone https://github.com/YOUR_USERNAME/FrequencyGeneratorControlSystem.git
cd FrequencyGeneratorControlSystem
git checkout -b feature/your-feature
```

#### Make Changes
- Follow code style guidelines
- Write clear commit messages
- Add comments for complex code
- Test your changes

#### Submit Pull Request
1. Push to your fork
2. Create pull request to main repo
3. Describe changes clearly
4. Reference related issues

### 3. Improve Documentation

- Fix typos and clarify wording
- Add examples
- Improve diagrams
- Translate documentation
- Add troubleshooting tips

### 4. Share Your Work

- Blog posts about the project
- Tutorials and guides
- Example projects
- Hardware designs
- Performance improvements

## Code Style Guidelines

### C Code (Firmware)
```c
// Use lowercase with underscores
void motor_control_init(void);

// Clear function documentation
/**
 * @brief Initialize PWM for motor control
 * @param frequency PWM frequency in Hz
 * @return 0 on success, -1 on error
 */
int motor_pwm_init(uint32_t frequency);

// Meaningful variable names
uint32_t motor_speed_rpm;
bool motor_is_running;
```

### C# Code (Desktop)
```csharp
// Use PascalCase for classes and methods
public class MotorController
{
    public void InitializeMotor()
    {
        // Implementation
    }
}

// Use camelCase for properties and variables
private int _motorSpeed;
public int MotorSpeed
{
    get => _motorSpeed;
    set => SetProperty(ref _motorSpeed, value);
}
```

## Commit Message Format

```
[Type] Brief description (50 chars max)

Longer description explaining the changes (72 chars max line length)

- Detail 1
- Detail 2

Fixes #123
```

**Types:**
- `feat:` New feature
- `fix:` Bug fix
- `docs:` Documentation
- `style:` Code style
- `refactor:` Code refactoring
- `perf:` Performance improvement
- `test:` Add tests

## Testing

### Firmware Tests
```bash
cd Firmware
make clean
make all
# Manual testing on hardware
```

### Desktop Tests
```bash
cd Desktop
dotnet build
dotnet test (if tests exist)
```

## Documentation

When adding features:
1. Update relevant documentation
2. Add API reference entries
3. Include usage examples
4. Update CHANGELOG.md
5. Add troubleshooting tips if applicable

## Project Structure

```
FrequencyGeneratorControlSystem/
├── Firmware/           - Embedded firmware
├── Desktop/            - WPF application
├── Documentation/      - All guides
├── .gitignore
├── LICENSE
└── README.md
```

## Coding Standards

### General
- Use meaningful names
- Keep functions small (<50 lines)
- Add comments for complex logic
- Remove dead code
- Follow DRY principle

### C Firmware
- Max line length: 100 characters
- Use HAL library functions
- Avoid blocking delays in main loop
- Use const for constants
- Document register operations

### C# Desktop
- Use MVVM pattern
- Implement INotifyPropertyChanged
- Use async/await for long operations
- Validate user input
- Handle exceptions gracefully

## Before Submitting

1. **Run tests**
   ```bash
   make clean && make all    # Firmware
   dotnet build              # Desktop
   ```

2. **Check code style**
   - No trailing whitespace
   - Consistent indentation
   - Clear comments

3. **Update documentation**
   - README.md if needed
   - API reference if new commands
   - CHANGELOG.md for changes

4. **Create meaningful commit**
   - Clear message
   - Reference issues
   - Document changes

## Pull Request Checklist

- [ ] Code follows project style
- [ ] Comments added for complex logic
- [ ] Documentation updated
- [ ] No breaking changes (or documented)
- [ ] Tested on Windows/Linux/Mac (if applicable)
- [ ] Commit messages are clear
- [ ] CHANGELOG.md updated

## Review Process

1. Maintainer reviews code
2. Feedback provided if needed
3. Changes requested? Update PR
4. Approved? PR merged
5. Celebrate! 🎉

## Community Guidelines

- Be respectful and constructive
- Assume good intentions
- Welcome diverse perspectives
- Help newcomers
- Share knowledge
- Give credit

## Questions?

- Read [ARCHITECTURE.md](Documentation/ARCHITECTURE.md) for design
- Check [API_REFERENCE.md](Documentation/API_REFERENCE.md) for commands
- Open a discussion: https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/discussions

## Recognition

Contributors will be:
- Listed in README.md
- Mentioned in CHANGELOG.md
- Credited in releases
- Thanked in documentation

## License

By contributing, you agree your code will be licensed under MIT License.

---

Thank you for making this project better! 🚀