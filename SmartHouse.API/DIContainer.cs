using SmartHouse.API.Services;

namespace SmartHouse.API;

public static class DIContainer
{
    public static IServiceCollection AddLoggerService(this IServiceCollection services)
        => services.AddTransient<ILoggerService, LoggerService>();

    public static IServiceCollection AddEmailService(this IServiceCollection services)
        => services.AddScoped<EmailService>();
}