using System;

namespace FrequencyGenerator.Services
{
    public interface IMonitoringService
    {
        void StartMonitoring();
        void StopMonitoring();
        event EventHandler MonitoringDataReceived;
    }
}