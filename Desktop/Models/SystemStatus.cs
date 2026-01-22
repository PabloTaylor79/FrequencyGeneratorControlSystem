using System;

namespace FrequencyGenerator.Models
{
    public class SystemStatus
    {
        public double Temperature { get; set; }
        public double Voltage { get; set; }
        public double Current { get; set; }
        public string FirmwareVersion { get; set; }
        public string HardwareVersion { get; set; }
        public DateTime UpdateTime { get; set; }
        public bool IsHealthy { get; set; }

        public SystemStatus()
        {
            Temperature = 25.0;
            Voltage = 5.0;
            Current = 0.0;
            FirmwareVersion = "1.0.0";
            HardwareVersion = "1.0";
            UpdateTime = DateTime.Now;
            IsHealthy = true;
        }

        public string GetTemperatureStatus()
        {
            if (Temperature < 50)
                return "NORMAL";
            else if (Temperature < 70)
                return "WARM";
            else
                return "HOT";
        }

        public string GetVoltageStatus()
        {
            if (Voltage >= 4.5 && Voltage <= 5.5)
                return "OK";
            else if (Voltage < 4.0)
                return "CRITICAL";
            else
                return "WARNING";
        }

        public bool IsHealthy()
        {
            return Temperature < 85 && Voltage >= 4.0 && Voltage <= 5.5;
        }

        public string GetSummary()
        {
            return $"Temp: {Temperature:F1}°C, Volt: {Voltage:F2}V, Current: {Current:F2}A";
        }
    }
}