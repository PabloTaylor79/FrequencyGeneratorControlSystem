using System;

namespace FrequencyGenerator.Models
{
    public class ProgramStep
    {
        public double StartFrequency { get; set; }
        public double StopFrequency { get; set; }
        public double RampTime { get; set; }
        public double DwellTime { get; set; }
        public int Power { get; set; }

        public ProgramStep()
        {
            StartFrequency = 2400e6;
            StopFrequency = 2450e6;
            RampTime = 1.0;
            DwellTime = 0.5;
            Power = 0;
        }

        public string GetSummary()
        {
            return $"{FormatFreq(StartFrequency)} → {FormatFreq(StopFrequency)} @ {Power} dBm (Ramp: {RampTime}s)";
        }

        private string FormatFreq(double freq)
        {
            if (freq >= 1e9)
                return $"{freq / 1e9:F2} GHz";
            else if (freq >= 1e6)
                return $"{freq / 1e6:F1} MHz";
            else
                return $"{freq:F0} Hz";
        }
    }
}