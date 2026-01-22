using System;
using System.Threading.Tasks;

namespace FrequencyGenerator.Services
{
    /// <summary>
    /// Service for managing RF frequency generator programs
    /// </summary>
    public class ProgramManagerService : IProgramManagerService
    {
        private readonly IUSBCommunicationService _usbService;

        public ProgramManagerService(IUSBCommunicationService usbService)
        {
            _usbService = usbService ?? throw new ArgumentNullException(nameof(usbService));
        }

        /// <summary>
        /// Create new program on device
        /// </summary>
        public async Task CreateProgramAsync(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException("Program name cannot be empty", nameof(name));

            string command = $"PROG:NEW {name}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to create program: {response}");
        }

        /// <summary>
        /// Delete program from device
        /// </summary>
        public async Task DeleteProgramAsync(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException("Program name cannot be empty", nameof(name));

            string command = $"PROG:DEL {name}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to delete program: {response}");
        }

        /// <summary>
        /// Save program to device storage
        /// </summary>
        public async Task SaveProgramAsync(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException("Program name cannot be empty", nameof(name));

            string command = $"PROG:SAVE {name}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to save program: {response}");
        }

        /// <summary>
        /// Load program from device storage
        /// </summary>
        public async Task LoadProgramAsync(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException("Program name cannot be empty", nameof(name));

            string command = $"PROG:LOAD {name}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to load program: {response}");
        }

        /// <summary>
        /// Start program execution
        /// </summary>
        public async Task RunProgramAsync()
        {
            string response = await _usbService.SendCommandAsync("PROG:RUN");
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to run program: {response}");
        }

        /// <summary>
        /// Pause program execution
        /// </summary>
        public async Task PauseProgramAsync()
        {
            string response = await _usbService.SendCommandAsync("PROG:PAUSE");
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to pause program: {response}");
        }

        /// <summary>
        /// Stop program execution
        /// </summary>
        public async Task StopProgramAsync()
        {
            string response = await _usbService.SendCommandAsync("PROG:STOP");
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to stop program: {response}");
        }

        /// <summary>
        /// Get current program execution status
        /// </summary>
        public async Task<string> GetProgramStatusAsync()
        {
            return await _usbService.SendCommandAsync("PROG:STATUS?");
        }

        /// <summary>
        /// Add step to current program
        /// </summary>
        public async Task AddStepAsync(string programName, double startFreq, double stopFreq, double rampTime, double dwellTime, int power)
        {
            string command = $"PROG:STEP {programName} {(long)startFreq} {(long)stopFreq} {rampTime} {dwellTime} {power}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to add step: {response}");
        }

        /// <summary>
        /// Clear all steps from program
        /// </summary>
        public async Task ClearStepsAsync(string programName)
        {
            string command = $"PROG:CLEAR {programName}";
            string response = await _usbService.SendCommandAsync(command);
            
            if (response != "OK")
                throw new InvalidOperationException($"Failed to clear steps: {response}");
        }

        /// <summary>
        /// List all programs on device
        /// </summary>
        public async Task<string> ListProgramsAsync()
        {
            return await _usbService.SendCommandAsync("PROG:LIST?");
        }
    }
}