using System;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Prism.Mvvm;
using Prism.Commands;

namespace FrequencyGenerator.ViewModels
{
    public class MainViewModel : BindableBase
    {
        private string _title = "Frequency Generator Control System";
        private ObservableCollection<string> _statusMessages;
        private string _connectionStatus;

        public string Title
        {
            get => _title;
            set => SetProperty(ref _title, value);
        }

        public ObservableCollection<string> StatusMessages
        {
            get => _statusMessages;
            set => SetProperty(ref _statusMessages, value);
        }

        public string ConnectionStatus
        {
            get => _connectionStatus;
            set => SetProperty(ref _connectionStatus, value);
        }

        public ICommand ConnectCommand { get; }
        public ICommand DisconnectCommand { get; }

        public MainViewModel()
        {
            _statusMessages = new ObservableCollection<string>();
            _connectionStatus = "Disconnected";
            
            ConnectCommand = new DelegateCommand(() => Connect());
            DisconnectCommand = new DelegateCommand(() => Disconnect());

            AddStatusMessage("Application started");
        }

        private void Connect()
        {
            ConnectionStatus = "Connected";
            AddStatusMessage("Device connected successfully");
        }

        private void Disconnect()
        {
            ConnectionStatus = "Disconnected";
            AddStatusMessage("Device disconnected");
        }

        public void AddStatusMessage(string message)
        {
            StatusMessages.Insert(0, $"[{DateTime.Now:HH:mm:ss}] {message}");
            if (StatusMessages.Count > 50)
                StatusMessages.RemoveAt(StatusMessages.Count - 1);
        }
    }
}