using System;
using System.Collections.ObjectModel;

namespace FrequencyGenerator.Models
{
    public class Program
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public DateTime CreatedDate { get; set; }
        public DateTime ModifiedDate { get; set; }
        public ObservableCollection<ProgramStep> Steps { get; set; }

        public Program(string name = "New Program")
        {
            Name = name;
            Description = string.Empty;
            CreatedDate = DateTime.Now;
            ModifiedDate = DateTime.Now;
            Steps = new ObservableCollection<ProgramStep>();
        }

        public void AddStep(ProgramStep step)
        {
            Steps.Add(step);
        }

        public void RemoveStep(ProgramStep step)
        {
            Steps.Remove(step);
        }

        public TimeSpan GetTotalDuration()
        {
            TimeSpan total = TimeSpan.Zero;
            foreach (var step in Steps)
            {
                total += TimeSpan.FromSeconds(step.RampTime + step.DwellTime);
            }
            return total;
        }
    }
}