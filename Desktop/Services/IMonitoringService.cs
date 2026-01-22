using System;

namespace FrequencyGenerator.Services
{
    public interface IMonitoringService
    {
        /// <summary>
        /// Start real-time monitoring
        /// </summary>
        void StartMonitoring();

        /// <summary>
        /// Stop real-time monitoring
        /// </summary>
        void StopMonitoring();

        /// <summary>
        /// Event raised when monitoring data received
        /// </summary>
        event EventHandler MonitoringDataReceived;

        /// <summary>
        /// Get latest monitoring data
        /// </summary>
        string GetLatestData();

        /// <summary>
        /// Check if currently monitoring
        /// </summary>
        bool IsMonitoring { get; }
    }
}