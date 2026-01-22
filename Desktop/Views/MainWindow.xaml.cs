using System;
using System.Windows;
using System.IO.Ports;
using System.Linq;
using Prism.Mvvm;
using FrequencyGenerator.ViewModels;

namespace FrequencyGenerator.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
            // Set window properties
            this.Title = "Frequency Generator Control System v1.0.0";
            this.Width = 1200;
            this.Height = 800;
            
            // Populate COM port selector
            RefreshComPorts();
            
            // Set up window closed event
            this.Closed += MainWindow_Closed;
            this.Loaded += MainWindow_Loaded;
            
            System.Diagnostics.Debug.WriteLine("MainWindow initialized");
        }

        /// <summary>
        /// Refresh available COM ports in selector
        /// </summary>
        private void RefreshComPorts()
        {
            try
            {
                var ports = SerialPort.GetPortNames();
                
                if (ComPortSelector != null)
                {
                    ComPortSelector.ItemsSource = ports;
                    
                    // Select first port by default
                    if (ports.Length > 0)
                    {
                        ComPortSelector.SelectedIndex = 0;
                    }
                    else
                    {
                        ComPortSelector.SelectedIndex = -1;
                    }
                }
                
                System.Diagnostics.Debug.WriteLine($"Found {ports.Length} COM ports: {string.Join(", ", ports)}");
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Error refreshing COM ports: {ex.Message}");
                MessageBox.Show($"Error reading COM ports: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// Handle window closing
        /// </summary>
        private void MainWindow_Closed(object sender, EventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("MainWindow closed");
            
            // Clean up any resources
            var viewModel = this.DataContext as MainViewModel;
            if (viewModel != null)
            {
                // Disconnect from device
                if (viewModel.MainViewModel != null && viewModel.MainViewModel.DisconnectCommand.CanExecute(null))
                {
                    viewModel.MainViewModel.DisconnectCommand.Execute(null);
                }
            }
        }

        /// <summary>
        /// Handle window loaded event
        /// </summary>
        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("MainWindow loaded");
            
            // Refresh COM ports when window loads
            RefreshComPorts();
        }
    }

    /// <summary>
    /// Value converter for status color
    /// </summary>
    public class StatusColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (value is string status)
            {
                switch (status)
                {
                    case "Connected":
                        return new System.Windows.Media.SolidColorBrush(System.Windows.Media.Colors.Green);
                    case "Disconnected":
                        return new System.Windows.Media.SolidColorBrush(System.Windows.Media.Colors.Red);
                    case "Connecting...":
                        return new System.Windows.Media.SolidColorBrush(System.Windows.Media.Colors.Orange);
                    default:
                        return new System.Windows.Media.SolidColorBrush(System.Windows.Media.Colors.Black);
                }
            }
            return new System.Windows.Media.SolidColorBrush(System.Windows.Media.Colors.Black);
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}