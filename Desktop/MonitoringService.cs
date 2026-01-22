using System;
using System.Threading.Tasks;

namespace FrequencyGenerator.Services
{
    public class MonitoringService : IMonitoringService
    {
        private readonly IUSBCommunicationService _usbService;
        private bool _isMonitoring;

        public event EventHandler MonitoringDataReceived;

        public MonitoringService(IUSBCommunicationService usbService)
        {
            _usbService = usbService ?? throw new ArgumentNullException(nameof(usbService));
            _isMonitoring = false;
        }

        public void StartMonitoring()
        {
            if (_isMonitoring)
                return;

            _isMonitoring = true;
            MonitoringLoop();
        }

        public void StopMonitoring()
        {
            _isMonitoring = false;
        }

        private async void MonitoringLoop()
        {
            while (_isMonitoring)
            {
                try
                {
                    string status = await _usbService.SendCommandAsync("SYS:STAT?");
                    MonitoringDataReceived?.Invoke(this, EventArgs.Empty);
                    await Task.Delay(1000);
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine($"Monitoring error: {ex.Message}");
                }
            }
        }
    }
}