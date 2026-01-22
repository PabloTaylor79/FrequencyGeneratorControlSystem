using System;
using System.Threading.Tasks;

namespace FrequencyGenerator.Services
{
    /// <summary>
    /// Service for real-time system monitoring
    /// </summary>
    public class MonitoringService : IMonitoringService
    {
        private readonly IUSBCommunicationService _usbService;
        private bool _isMonitoring;
        private string _latestData;

        public event EventHandler MonitoringDataReceived;

        public bool IsMonitoring => _isMonitoring;

        public MonitoringService(IUSBCommunicationService usbService)
        {
            _usbService = usbService ?? throw new ArgumentNullException(nameof(usbService));
            _isMonitoring = false;
            _latestData = string.Empty;
        }

        /// <summary>
        /// Start monitoring loop
        /// </summary>
        public void StartMonitoring()
        {
            if (_isMonitoring)
                return;

            _isMonitoring = true;
            MonitoringLoop();
        }

        /// <summary>
        /// Stop monitoring loop
        /// </summary>
        public void StopMonitoring()
        {
            _isMonitoring = false;
        }

        /// <summary>
        /// Get latest monitoring data
        /// </summary>
        public string GetLatestData()
        {
            return _latestData;
        }

        /// <summary>
        /// Main monitoring loop
        /// </summary>
        private async void MonitoringLoop()
        {
            while (_isMonitoring)
            {
                try
                {
                    if (!_usbService.IsConnected)
                    {
                        await Task.Delay(1000);
                        continue;
                    }

                    // Request system status
                    string status = await _usbService.SendCommandAsync("SYS:STAT?");
                    _latestData = status;

                    // Raise event to notify listeners
                    MonitoringDataReceived?.Invoke(this, EventArgs.Empty);

                    // Wait before next update
                    await Task.Delay(1000);
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine($"Monitoring error: {ex.Message}");
                    await Task.Delay(1000);
                }
            }
        }

        /// <summary>
        /// Query single status reading
        /// </summary>
        public async Task<string> QueryStatusAsync()
        {
            try
            {
                if (!_usbService.IsConnected)
                    throw new InvalidOperationException("Device not connected");

                return await _usbService.SendCommandAsync("SYS:STAT?");
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Status query error: {ex.Message}");
                throw;
            }
        }

        /// <summary>
        /// Query temperature
        /// </summary>
        public async Task<double> QueryTemperatureAsync()
        {
            try
            {
                string response = await _usbService.SendCommandAsync("TEMP?");
                if (double.TryParse(response, out double temp))
                    return temp;
                return 0.0;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Temperature query error: {ex.Message}");
                return 0.0;
            }
        }

        /// <summary>
        /// Query voltage
        /// </summary>
        public async Task<double> QueryVoltageAsync()
        {
            try
            {
                string response = await _usbService.SendCommandAsync("VOLT?");
                if (double.TryParse(response, out double voltage))
                    return voltage;
                return 0.0;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Voltage query error: {ex.Message}");
                return 0.0;
            }
        }

        /// <summary>
        /// Query current
        /// </summary>
        public async Task<double> QueryCurrentAsync()
        {
            try
            {
                string response = await _usbService.SendCommandAsync("CURR?");
                if (double.TryParse(response, out double current))
                    return current;
                return 0.0;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Current query error: {ex.Message}");
                return 0.0;
            }
        }
    }
}