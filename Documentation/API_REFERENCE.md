# API Reference

## Command Protocol

### Format
```
COMMAND:SUBCOMMAND [parameters]
```

### Response
```
OK                          - Command successful
<data>                      - Query response
ERROR: <message>            - Command failed
```

## System Commands

### SYS:IDN?
**Get system identification**

Request: `SYS:IDN?`
Response: `FrequencyGenerator,FG-STM32H743,SN123456,1.0.0`

### SYS:STAT?
**Get system status**

Request: `SYS:STAT?`
Response: `TEMP:45.5,VOLT:5.00,CURR:0.85`

### SYS:RESET
**Reset system**

Request: `SYS:RESET`
Response: `OK`

## RF Commands

### RF:FREQ
**Set RF frequency**

Request: `RF:FREQ 2400000000`
Response: `OK`

### RF:FREQ?
**Query RF frequency**

Request: `RF:FREQ?`
Response: `2400000000`

### RF:POWER
**Set RF power**

Request: `RF:POWER 10`
Response: `OK`

### RF:POWER?
**Query RF power**

Request: `RF:POWER?`
Response: `10`

### RF:OUTPUT ON/OFF
**Enable/disable RF output**

Request: `RF:OUTPUT ON`
Response: `OK`

### RF:OUTPUT?
**Query RF output status**

Request: `RF:OUTPUT?`
Response: `ON` or `OFF`

## Program Commands

### PROG:NEW
**Create new program**

Request: `PROG:NEW MyProgram`
Response: `OK`

### PROG:DEL
**Delete program**

Request: `PROG:DEL MyProgram`
Response: `OK`

### PROG:SAVE
**Save program**

Request: `PROG:SAVE MyProgram`
Response: `OK`

### PROG:LOAD
**Load program**

Request: `PROG:LOAD MyProgram`
Response: `OK`

### PROG:RUN
**Run loaded program**

Request: `PROG:RUN`
Response: `OK`

### PROG:PAUSE
**Pause running program**

Request: `PROG:PAUSE`
Response: `OK`

### PROG:STOP
**Stop running program**

Request: `PROG:STOP`
Response: `OK`

### PROG:STATUS?
**Query program status**

Request: `PROG:STATUS?`
Response: `RUNNING` or `IDLE`

## Calibration Commands

### CAL:START
**Start calibration**

Request: `CAL:START`
Response: `OK`

### CAL:SAVE
**Save calibration data**

Request: `CAL:SAVE`
Response: `OK`

### CAL:LOAD
**Load calibration data**

Request: `CAL:LOAD`
Response: `OK`