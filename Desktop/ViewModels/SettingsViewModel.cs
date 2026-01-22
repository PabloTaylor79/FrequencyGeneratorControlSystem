using System;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Prism.Mvvm;
using Prism.Commands;
using FrequencyGenerator.Models;

namespace FrequencyGenerator.ViewModels
{
    public class SettingsViewModel : BindableBase
    {
        private bool _autoConnectEnabled;
        private int _updateInterval;
        private bool _darkThemeEnabled;
        private string _firmwareVersion;
        private string _statusMessage;

        public bool AutoConnectEnabled
        {
            get => _autoConnectEnabled;
            set => SetProperty(ref _autoConnectEnabled, value);
        }

        public int UpdateInterval
        {
            get => _updateInterval;
            set => SetProperty(ref _updateInterval, value);
        }

        public bool DarkThemeEnabled
        {
            get => _darkThemeEnabled;
            set => SetProperty(ref _darkThemeEnabled, value);
        }

        public string FirmwareVersion
        {
            get => _firmwareVersion;
            set => SetProperty(ref _firmwareVersion, value);
        }

        public string StatusMessage
        {
            get => _statusMessage;
            set => SetProperty(ref _statusMessage, value);
        }

        public ICommand SaveSettingsCommand { get; }
        public ICommand ResetSettingsCommand { get; }
        public ICommand StartCalibrationCommand { get; }

        public SettingsViewModel()
        {
            _autoConnectEnabled = false;
            _updateInterval = 1000;
            _darkThemeEnabled = false;
            _firmwareVersion = "Unknown";
            _statusMessage = "Ready";

            SaveSettingsCommand = new DelegateCommand(() => SaveSettings());
            ResetSettingsCommand = new DelegateCommand(() => ResetSettings());
            StartCalibrationCommand = new DelegateCommand(() => StartCalibration());

            LoadSettings();
        }

        private void SaveSettings()
        {
            // Save settings to configuration
            StatusMessage = "Settings saved successfully";
        }

        private void ResetSettings()
        {
            AutoConnectEnabled = false;
            UpdateInterval = 1000;
            DarkThemeEnabled = false;
            StatusMessage = "Settings reset to defaults";
        }

        private void StartCalibration()
        {
            StatusMessage = "Calibration started...";
        }

        private void LoadSettings()
        {
            // Load settings from configuration file
            StatusMessage = "Settings loaded";
        }
    }
}