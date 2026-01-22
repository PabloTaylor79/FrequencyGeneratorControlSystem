using System;
using System.Threading.Tasks;

namespace FrequencyGenerator.Services
{
    public interface IProgramManagerService
    {
        Task CreateProgramAsync(string name);
        Task DeleteProgramAsync(string name);
        Task SaveProgramAsync(string name);
        Task LoadProgramAsync(string name);
        Task RunProgramAsync();
        Task PauseProgramAsync();
        Task StopProgramAsync();
        Task<string> GetProgramStatusAsync();
    }

    public class ProgramManagerService : IProgramManagerService
    {
        private readonly IUSBCommunicationService _usbService;

        public ProgramManagerService(IUSBCommunicationService usbService)
        {
            _usbService = usbService ?? throw new ArgumentNullException(nameof(usbService));
        }

        public async Task CreateProgramAsync(string name)
        {
            string command = $"PROG:NEW {name}";
            await _usbService.SendCommandAsync(command);
        }

        public async Task DeleteProgramAsync(string name)
        {
            string command = $"PROG:DEL {name}";
            await _usbService.SendCommandAsync(command);
        }

        public async Task SaveProgramAsync(string name)
        {
            string command = $"PROG:SAVE {name}";
            await _usbService.SendCommandAsync(command);
        }

        public async Task LoadProgramAsync(string name)
        {
            string command = $"PROG:LOAD {name}";
            await _usbService.SendCommandAsync(command);
        }

        public async Task RunProgramAsync()
        {
            await _usbService.SendCommandAsync("PROG:RUN");
        }

        public async Task PauseProgramAsync()
        {
            await _usbService.SendCommandAsync("PROG:PAUSE");
        }

        public async Task StopProgramAsync()
        {
            await _usbService.SendCommandAsync("PROG:STOP");
        }

        public async Task<string> GetProgramStatusAsync()
        {
            return await _usbService.SendCommandAsync("PROG:STATUS?");
        }
    }
}