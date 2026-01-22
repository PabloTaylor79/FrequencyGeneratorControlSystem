using System;
using System.Windows;
using Prism.Ioc;
using Prism.Modularity;
using Serilog;
using FrequencyGenerator.Services;
using FrequencyGenerator.ViewModels;
using FrequencyGenerator.Views;

namespace FrequencyGenerator
{
    public static class Program
    {
        [STAThread]
        public static void Main()
        {
            // Configure Serilog logging
            Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Debug()
                .WriteTo.File("logs/app-.txt", rollingInterval: RollingInterval.Day)
                .WriteTo.Console()
                .CreateLogger();

            try
            {
                Log.Information("Application starting");
                
                var app = new App();
                app.InitializeComponent();
                app.Run();
            }
            catch (Exception ex)
            {
                Log.Fatal(ex, "Application terminated unexpectedly");
            }
            finally
            {
                Log.CloseAndFlush();
            }
        }
    }
}