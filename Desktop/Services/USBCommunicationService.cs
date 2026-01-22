using System;
using System.IO.Ports;
using System.Threading.Tasks;

namespace FrequencyGenerator.Services
{
    public interface IUSBCommunicationService
    {
        bool IsConnected { get; }
        Task<bool> ConnectAsync(string portName);
        void Disconnect();
        Task<string> SendCommandAsync(string command);
        Task<byte[]> SendRawAsync(byte[] data);
        string[] GetAvailablePorts();
    }

    public class USBCommunicationService : IUSBCommunicationService
    {
        private SerialPort _serialPort;
        private const int BaudRate = 115200;
        private const int Timeout = 5000;

        public bool IsConnected => _serialPort?.IsOpen ?? false;

        /// <summary>
        /// Connect to device via USB/COM port
        /// </summary>
        public async Task<bool> ConnectAsync(string portName)
        {
            try
            {
                if (_serialPort != null && _serialPort.IsOpen)
                {
                    _serialPort.Close();
                }

                _serialPort = new SerialPort(portName, BaudRate)
                {
                    Parity = Parity.None,
                    DataBits = 8,
                    StopBits = StopBits.One,
                    ReadTimeout = Timeout,
                    WriteTimeout = Timeout,
                    Handshake = Handshake.None
                };

                _serialPort.Open();
                await Task.Delay(500); // Wait for device initialization
                
                System.Diagnostics.Debug.WriteLine($"Connected to {portName}");
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Connection error: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Disconnect from device
        /// </summary>
        public void Disconnect()
        {
            try
            {
                if (_serialPort != null && _serialPort.IsOpen)
                {
                    _serialPort.Close();
                    _serialPort.Dispose();
                    _serialPort = null;
                }
                System.Diagnostics.Debug.WriteLine("Disconnected");
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Disconnect error: {ex.Message}");
            }
        }

        /// <summary>
        /// Send command and receive response
        /// </summary>
        public async Task<string> SendCommandAsync(string command)
        {
            if (!IsConnected)
                throw new InvalidOperationException("Device not connected");

            try
            {
                // Send command
                await Task.Run(() =>
                {
                    _serialPort.WriteLine(command);
                    System.Threading.Thread.Sleep(100);
                });

                // Receive response
                string response = await Task.Run(() =>
                {
                    try
                    {
                        return _serialPort.ReadLine();
                    }
                    catch (TimeoutException)
                    {
                        return "TIMEOUT";
                    }
                });

                System.Diagnostics.Debug.WriteLine($"TX: {command} | RX: {response}");
                return response;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Command error: {ex.Message}");
                throw;
            }
        }

        /// <summary>
        /// Send raw binary data
        /// </summary>
        public async Task<byte[]> SendRawAsync(byte[] data)
        {
            if (!IsConnected)
                throw new InvalidOperationException("Device not connected");

            try
            {
                await Task.Run(() => _serialPort.Write(data, 0, data.Length));
                await Task.Delay(100);

                byte[] buffer = new byte[256];
                int bytesRead = await Task.Run(() => _serialPort.Read(buffer, 0, buffer.Length));
                Array.Resize(ref buffer, bytesRead);
                
                System.Diagnostics.Debug.WriteLine($"Sent {data.Length} bytes, received {bytesRead} bytes");
                return buffer;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Raw send error: {ex.Message}");
                throw;
            }
        }

        /// <summary>
        /// Get list of available COM ports
        /// </summary>
        public string[] GetAvailablePorts()
        {
            return SerialPort.GetPortNames();
        }
    }
}