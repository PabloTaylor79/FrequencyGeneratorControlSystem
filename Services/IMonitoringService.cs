// IMonitoringService.cs

namespace FrequencyGeneratorControlSystem.Services
{
    public interface IMonitoringService
    {
        void StartMonitoring();
        void StopMonitoring();
        event EventHandler MonitoringDataReceived;
    }
}