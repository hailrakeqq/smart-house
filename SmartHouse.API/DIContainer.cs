using SmartHouse.API.Enitity;
using SmartHouse.API.Services;

public static class DIContainer
{
    public static IServiceCollection AddTokenService(this IServiceCollection services)
    {
        return services.AddTransient<ITokenService, TokenService>();
    }

    public static IServiceCollection AddLoginResponse(this IServiceCollection services)
    {
        return services.AddSingleton<LoginResponse>();
    }

    public static IServiceCollection AddUserService(this IServiceCollection services)
    {
        return services.AddTransient<IUserRepository, UserService>();
    }
}