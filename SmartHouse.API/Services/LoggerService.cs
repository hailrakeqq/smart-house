namespace SmartHouse.API.Services;

public interface ILoggerService
{
    //ADD LOG
    //GET LOGS
    //GET LOG BY ID
    // AUTO DELETE LOG AFTER SOME TIME
}

public class LoggerService : ILoggerService
{
    private readonly ApplicationDbContext _context;
    public LoggerService(ApplicationDbContext context)
    {
        _context = context;
    }
}
