using System;
using System.Collections.ObjectModel;

namespace FrequencyGenerator.Models
{
    /// <summary>
    /// Represents calibration data for the system
    /// </summary>
    public class CalibrationData
    {
        public DateTime CalibrationDate { get; set; }
        public string CalibrationNotes { get; set; }
        public ObservableCollection<FrequencyPoint> FrequencyCalibration { get; set; }
        public ObservableCollection<PowerPoint> PowerCalibration { get; set; }

        public CalibrationData()
        {
            CalibrationDate = DateTime.Now;
            CalibrationNotes = string.Empty;
            FrequencyCalibration = new ObservableCollection<FrequencyPoint>();
            PowerCalibration = new ObservableCollection<PowerPoint>();
        }
    }

    public class FrequencyPoint
    {
        public double NominalFrequency { get; set; }
        public double MeasuredFrequency { get; set; }
        public double CorrectionFactor { get; set; }
    }

    public class PowerPoint
    {
        public int NominalPower { get; set; }
        public double MeasuredPower { get; set; }
        public double CorrectionFactor { get; set; }
    }
}