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
        Task AddStepAsync(string programName, double startFreq, double stopFreq, double rampTime, double dwellTime, int power);
        Task ClearStepsAsync(string programName);
        Task<string> ListProgramsAsync();
    }
}