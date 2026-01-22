using System;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Prism.Mvvm;
using Prism.Commands;
using FrequencyGenerator.Models;

namespace FrequencyGenerator.ViewModels
{
    /// <summary>
    /// View model for RF control tab
    /// </summary>
    public class RFControlViewModel : BindableBase
    {
        private double _currentFrequency;
        private int _currentPower;
        private bool _rfOutputEnabled;
        private string _frequencyInput;
        private string _statusMessage;

        public double CurrentFrequency
        {
            get => _currentFrequency;
            set => SetProperty(ref _currentFrequency, value);
        }

        public int CurrentPower
        {
            get => _currentPower;
            set => SetProperty(ref _currentPower, value);
        }

        public bool RfOutputEnabled
        {
            get => _rfOutputEnabled;
            set => SetProperty(ref _rfOutputEnabled, value);
        }

        public string FrequencyInput
        {
            get => _frequencyInput;
            set => SetProperty(ref _frequencyInput, value);
        }

        public string StatusMessage
        {
            get => _statusMessage;
            set => SetProperty(ref _statusMessage, value);
        }

        public ICommand SetFrequencyCommand { get; }
        public ICommand SetPowerCommand { get; }
        public ICommand ToggleRfOutputCommand { get; }

        public RFControlViewModel()
        {
            _currentFrequency = 2400e6; // 2400 MHz
            _currentPower = 0; // 0 dBm
            _rfOutputEnabled = false;
            _frequencyInput = "2400000000";
            _statusMessage = "Ready";

            SetFrequencyCommand = new DelegateCommand(() => SetFrequency());
            SetPowerCommand = new DelegateCommand(() => SetPower());
            ToggleRfOutputCommand = new DelegateCommand(() => ToggleRfOutput());
        }

        private void SetFrequency()
        {
            // Parse frequency input
            if (double.TryParse(FrequencyInput, out var freq))
            {
                if (freq >= 10e6 && freq <= 6e9)
                {
                    CurrentFrequency = freq;
                    StatusMessage = $"Frequency set to {FormatFrequency(freq)}";
                }
                else
                {
                    StatusMessage = "Frequency out of range (10 MHz - 6 GHz)";
                }
            }
            else
            {
                StatusMessage = "Invalid frequency format";
            }
        }

        private void SetPower()
        {
            StatusMessage = $"Power set to {CurrentPower} dBm";
        }

        private void ToggleRfOutput()
        {
            RfOutputEnabled = !RfOutputEnabled;
            StatusMessage = RfOutputEnabled ? "RF Output: ON" : "RF Output: OFF";
        }

        private string FormatFrequency(double frequency)
        {
            if (frequency >= 1e9)
                return $"{frequency / 1e9:F3} GHz";
            else if (frequency >= 1e6)
                return $"{frequency / 1e6:F1} MHz";
            else
                return $"{frequency:F0} Hz";
        }
    }
}