using System;
using System.Collections.ObjectModel;
using Prism.Mvvm;
using FrequencyGenerator.Models;

namespace FrequencyGenerator.ViewModels
{
    public class MonitoringViewModel : BindableBase
    {
        private SystemStatus _systemStatus;
        private ObservableCollection<string> _statusLog;
        private string _temperatureStatus;
        private string _voltageStatus;
        private string _healthStatus;

        public SystemStatus SystemStatus
        {
            get => _systemStatus;
            set => SetProperty(ref _systemStatus, value);
        }

        public ObservableCollection<string> StatusLog
        {
            get => _statusLog;
            set => SetProperty(ref _statusLog, value);
        }

        public string TemperatureStatus
        {
            get => _temperatureStatus;
            set => SetProperty(ref _temperatureStatus, value);
        }

        public string VoltageStatus
        {
            get => _voltageStatus;
            set => SetProperty(ref _voltageStatus, value);
        }

        public string HealthStatus
        {
            get => _healthStatus;
            set => SetProperty(ref _healthStatus, value);
        }

        public MonitoringViewModel()
        {
            _systemStatus = new SystemStatus();
            _statusLog = new ObservableCollection<string>();
            UpdateStatus();
        }

        public void UpdateStatus()
        {
            TemperatureStatus = SystemStatus.GetTemperatureStatus().ToString();
            VoltageStatus = SystemStatus.GetVoltageStatus().ToString();
            HealthStatus = SystemStatus.IsHealthy() ? "HEALTHY" : "WARNING";

            AddLog($"[{DateTime.Now:HH:mm:ss}] {SystemStatus.GetSummary()}");
        }

        public void AddLog(string message)
        {
            StatusLog.Insert(0, message);
            if (StatusLog.Count > 100)
                StatusLog.RemoveAt(StatusLog.Count - 1);
        }

        public void ClearLog()
        {
            StatusLog.Clear();
        }
    }
}