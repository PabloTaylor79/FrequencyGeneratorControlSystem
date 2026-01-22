# User Manual

## Overview

The Frequency Generator Control System allows you to control an RF frequency generator from 10 MHz to 6 GHz with power control from -20 to +15 dBm.

## Getting Started

1. **Connect Device**
   - Connect STM32H743 device via USB
   - Device appears as COM port
   - Note the COM port number

2. **Launch Application**
   ```bash
   dotnet run
   ```

3. **Select COM Port and Connect**
   - Click "Connect" button
   - Select appropriate COM port
   - Device should show as "Connected"

## Features

### RF Control Tab

**Set Frequency:**
1. Enter frequency in Hz (10 MHz = 10000000)
2. Click "Set Frequency"
3. Frequency displayed in real-time

**Set Power:**
1. Use slider to adjust power (-20 to +15 dBm)
2. Click "Set Power"
3. Power level updated

**RF Output:**
1. Check "RF Output" to enable
2. Uncheck to disable
3. Status shown in status bar

### Program Editor Tab

**Create Program:**
1. Enter program name
2. Click "Create Program"
3. Program appears in list

**Add Steps:**
1. Select program
2. Click "Add Step"
3. Configure step parameters
4. Save program

**Run Program:**
1. Select program
2. Click "Run"
3. Program executes steps sequentially

### Monitoring Tab

**View Status:**
- Temperature: Device temperature
- Voltage: Power supply voltage
- Current: Power consumption

**Status Log:**
- Real-time status updates
- Timestamp for each entry

### Settings Tab

**Configure:**
- Auto Connect: Automatically connect on startup
- Dark Theme: Switch UI theme
- Update Interval: Status update frequency

### Calibration Tab

**Calibration Process:**
1. Click "Start Calibration"
2. Device performs frequency calibration
3. Click "Save Calibration"
4. Calibration stored in FRAM

## Command Reference

See [API_REFERENCE.md](API_REFERENCE.md) for complete command list.

## Troubleshooting

See [TROUBLESHOOTING.md](TROUBLESHOOTING.md) for help.