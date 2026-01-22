# Troubleshooting Guide

## Common Issues

### Device Not Recognized

**Symptom:** COM port doesn't appear in Device Manager

**Solutions:**
1. Check USB cable connection
2. Install CH340 drivers if needed
3. Restart computer
4. Try different USB port
5. Check Device Manager for unknown devices

### Connection Failed

**Symptom:** "Cannot open COM port" error

**Solutions:**
1. Verify correct COM port selected
2. Close other serial applications
3. Check baud rate is 115200
4. Ensure device is powered

### Frequency Not Changing

**Symptom:** Frequency command sent but not applied

**Solutions:**
1. Check PLL lock status
2. Verify frequency in valid range
3. Check RF output is enabled
4. Try calibration

### Temperature Warning

**Symptom:** System shows temperature > 70°C

**Solutions:**
1. Reduce output power
2. Reduce update rate
3. Check cooling
4. Wait for cooldown

### Build Fails

**Symptom:** Compilation errors

**Solutions:**
1. Verify ARM GCC installed: `arm-none-eabi-gcc --version`
2. Check CMake installed: `cmake --version`
3. Clean build directory: `rm -rf build && mkdir build`
4. Retry build

## Getting Help

1. Check [API_REFERENCE.md](API_REFERENCE.md) for command syntax
2. Check [USER_MANUAL.md](USER_MANUAL.md) for features
3. Open GitHub Issue: https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/issues
4. Join GitHub Discussions: https://github.com/PabloTaylor79/FrequencyGeneratorControlSystem/discussions