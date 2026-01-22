using System;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Prism.Mvvm;
using Prism.Commands;
using FrequencyGenerator.Models;

namespace FrequencyGenerator.ViewModels
{
    public class ProgramEditorViewModel : BindableBase
    {
        private ObservableCollection<Program> _programs;
        private Program _currentProgram;
        private string _newProgramName;
        private string _statusMessage;

        public ObservableCollection<Program> Programs
        {
            get => _programs;
            set => SetProperty(ref _programs, value);
        }

        public Program CurrentProgram
        {
            get => _currentProgram;
            set => SetProperty(ref _currentProgram, value);
        }

        public string NewProgramName
        {
            get => _newProgramName;
            set => SetProperty(ref _newProgramName, value);
        }

        public string StatusMessage
        {
            get => _statusMessage;
            set => SetProperty(ref _statusMessage, value);
        }

        public ICommand CreateProgramCommand { get; }
        public ICommand DeleteProgramCommand { get; }
        public ICommand SaveProgramCommand { get; }
        public ICommand AddStepCommand { get; }

        public ProgramEditorViewModel()
        {
            _programs = new ObservableCollection<Program>();
            _statusMessage = "Ready";

            CreateProgramCommand = new DelegateCommand(() => CreateProgram());
            DeleteProgramCommand = new DelegateCommand(() => DeleteProgram());
            SaveProgramCommand = new DelegateCommand(() => SaveProgram());
            AddStepCommand = new DelegateCommand(() => AddStep());

            LoadPrograms();
        }

        private void CreateProgram()
        {
            if (string.IsNullOrWhiteSpace(NewProgramName))
            {
                StatusMessage = "Program name cannot be empty";
                return;
            }

            var program = new Program(NewProgramName);
            Programs.Add(program);
            CurrentProgram = program;
            NewProgramName = string.Empty;
            StatusMessage = $"Program '{NewProgramName}' created";
        }

        private void DeleteProgram()
        {
            if (CurrentProgram != null && Programs.Contains(CurrentProgram))
            {
                Programs.Remove(CurrentProgram);
                StatusMessage = "Program deleted";
                CurrentProgram = null;
            }
        }

        private void SaveProgram()
        {
            if (CurrentProgram != null)
            {
                CurrentProgram.ModifiedDate = DateTime.Now;
                StatusMessage = "Program saved";
            }
        }

        private void AddStep()
        {
            if (CurrentProgram != null)
            {
                var step = new ProgramStep();
                CurrentProgram.AddStep(step);
                StatusMessage = "Step added";
            }
            else
            {
                StatusMessage = "Please select or create a program first";
            }
        }

        private void LoadPrograms()
        {
            // Load programs from device
            StatusMessage = "Programs loaded";
        }
    }
}