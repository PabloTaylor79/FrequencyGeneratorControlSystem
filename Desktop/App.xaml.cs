using System;
using System.Windows;
using Prism.Ioc;
using Prism.Modularity;
using Serilog;
using FrequencyGenerator.Services;
using FrequencyGenerator.ViewModels;
using FrequencyGenerator.Views;
using FrequencyGenerator.Converters;

namespace FrequencyGenerator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : PrismApplication
    {
        protected override Window CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            Log.Information("Registering types in DI container");

            // Register Services (Singletons for shared state)
            containerRegistry.RegisterSingleton<IUSBCommunicationService, USBCommunicationService>();
            containerRegistry.RegisterSingleton<IProgramManagerService, ProgramManagerService>();
            containerRegistry.RegisterSingleton<IMonitoringService, MonitoringService>();

            // Register ViewModels (Transient for fresh instances)
            containerRegistry.Register<MainViewModel>();
            containerRegistry.Register<RFControlViewModel>();
            containerRegistry.Register<ProgramEditorViewModel>();
            containerRegistry.Register<MonitoringViewModel>();
            containerRegistry.Register<SettingsViewModel>();
            containerRegistry.Register<CalibrationViewModel>();

            // Register Views
            containerRegistry.Register<MainWindow>();

            Log.Information("Type registration completed");
        }

        protected override void ConfigureModuleCatalog(IModuleCatalog moduleCatalog)
        {
            // Add modules if needed
            // moduleCatalog.AddModule<MyModule>();
        }

        /// <summary>
        /// Handle application startup
        /// </summary>
        protected override void OnStartup(StartupEventArgs e)
        {
            Log.Information("Application startup");
            
            // Wire exception handler
            this.DispatcherUnhandledException += Application_DispatcherUnhandledException;
            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;
            
            base.OnStartup(e);
        }

        /// <summary>
        /// Handle application exit
        /// </summary>
        protected override void OnExit(ExitEventArgs e)
        {
            Log.Information("Application exit");
            base.OnExit(e);
        }

        /// <summary>
        /// Handle unhandled exceptions from dispatcher
        /// </summary>
        private void Application_DispatcherUnhandledException(object sender, System.Windows.Threading.DispatcherUnhandledExceptionEventArgs e)
        {
            Log.Error(e.Exception, "Unhandled dispatcher exception");
            MessageBox.Show($"An error occurred: {e.Exception.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            e.Handled = true;
        }

        /// <summary>
        /// Handle unhandled exceptions from current domain
        /// </summary>
        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            Exception ex = e.ExceptionObject as Exception;
            if (ex != null)
            {
                Log.Fatal(ex, "Unhandled domain exception");
                MessageBox.Show($"A fatal error occurred: {ex.Message}", "Fatal Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}