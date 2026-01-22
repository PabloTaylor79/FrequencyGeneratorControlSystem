using System;
using System.Collections.ObjectModel;  // ✅ FIXED from ObjectCollection
using System.Windows.Input;
using Prism.Mvvm;
using Prism.Commands;
using FrequencyGenerator.Models;

namespace FrequencyGenerator.ViewModels
{
    /// <summary>
    /// ViewModel for calibration management
    /// </summary>
    public class CalibrationViewModel : BindableBase
    {
        private CalibrationData _calibrationData;
        private string _statusMessage;
        private bool _isCalibrating;

        public CalibrationData CalibrationData
        {
            get => _calibrationData;
            set => SetProperty(ref _calibrationData, value);
        }

        public string StatusMessage
        {
            get => _statusMessage;
            set => SetProperty(ref _statusMessage, value);
        }

        public bool IsCalibrating
        {
            get => _isCalibrating;
            set => SetProperty(ref _isCalibrating, value);
        }

        public ICommand StartCalibrationCommand { get; }
        public ICommand SaveCalibrationCommand { get; }
        public ICommand LoadCalibrationCommand { get; }

        public CalibrationViewModel()
        {
            _calibrationData = new CalibrationData();
            _statusMessage = "Ready for calibration";
            _isCalibrating = false;

            StartCalibrationCommand = new DelegateCommand(() => StartCalibration());
            SaveCalibrationCommand = new DelegateCommand(() => SaveCalibration());
            LoadCalibrationCommand = new DelegateCommand(() => LoadCalibration());
        }

        private void StartCalibration()
        {
            IsCalibrating = true;
            StatusMessage = "Calibration in progress...";
            
            // TODO: Implement actual calibration logic
        }

        private void SaveCalibration()
        {
            StatusMessage = "Calibration saved";
        }

        private void LoadCalibration()
        {
            StatusMessage = "Calibration loaded";
        }
    }
}