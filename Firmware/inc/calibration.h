#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <stdint.h>

/**
 * Calibration Data Management
 */

typedef struct {
    uint32_t frequency;
    int8_t power_correction;
    double temp_coefficient;
} CalibrationPoint_t;

#define CALIBRATION_POINTS 256

typedef struct {
    CalibrationPoint_t points[CALIBRATION_POINTS];
    uint32_t count;
    uint32_t timestamp;
} CalibrationData_t;

void Calibration_Init(void);
void Calibration_LoadFromFRAM(void);
void Calibration_SaveToFRAM(void);
void Calibration_AddPoint(uint32_t freq, int8_t power, double temp);
int8_t Calibration_GetPowerCorrection(uint32_t freq);
CalibrationData_t* Calibration_GetData(void);

#endif