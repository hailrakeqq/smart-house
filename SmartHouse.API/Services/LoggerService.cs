using Microsoft.IdentityModel.Tokens;
using Microsoft.OpenApi.Extensions;
using SmartHouse.API.Enitity;

namespace SmartHouse.API.Services;

public interface ILoggerService
{
    List<Log> GetLogsByDate(String date); //get logs by log file name, example: 10042024.log
    List<Log> GetAllLogs();
    Log GetLogById(String Id);
    Log GetLogById(String logName, String Id);
    void CreateLogFileForCurrentDayAndAddLog(Log log);
    void AddLogToLogFile(String LogFileName, Log log);
    bool IsLogForCurrentDayExist(String CurrentDay);
}

public class LoggerService : ILoggerService
{
    private const string logs_dir = "logs/";

    List<Log> ILoggerService.GetLogsByDate(string date)
    {
        var logPath = Path.Combine(logs_dir, $"{date}.log");
        if (!File.Exists(logPath))
            throw new Exception($"Файл {logPath} не найден.");

        List<Log> logs = new List<Log>();

        string[] lines = File.ReadAllLines(Path.Combine(logs_dir, $"{date}.log"));

        foreach (var line in lines)
        {
            if (!line.IsNullOrEmpty())
                logs.Add(Log.GetLogFromString(line));
        }
        return logs;
    }

    public List<Log> GetAllLogs()
    {
        List<Log> logs = new List<Log>();

        // Получаем путь к директории логов относительно текущей рабочей директории
        string logs_dir = Path.Combine(Directory.GetCurrentDirectory(), "logs");

        // Проверяем существование директории
        if (Directory.Exists(logs_dir))
        {
            string[] files = Directory.GetFiles(logs_dir);

            foreach (var file in files)
            {
                string[] lines = File.ReadAllLines(file);

                foreach (var line in lines)
                {
                    if (!string.IsNullOrEmpty(line))
                        logs.Add(Log.GetLogFromString(line));
                }
            }
        }

        return logs;
    }

    Log ILoggerService.GetLogById(string Id)
    {
        string[] files = Directory.GetFiles(logs_dir);

        foreach (var file in files)
        {
            string[] lines = File.ReadAllLines(Path.Combine(logs_dir, file));

            foreach (var line in lines)
            {
                if (!line.IsNullOrEmpty())
                {
                    string extractedId = line.Split('|')[1].Trim();
                    if (extractedId == Id)
                        return Log.GetLogFromString(line);
                }
            }
        }

        return null;
    }

    Log ILoggerService.GetLogById(string LogPath, string Id)
    {
        string[] lines = File.ReadAllLines(Path.Combine(logs_dir, LogPath));

        foreach (var line in lines)
        {
            if (!line.IsNullOrEmpty())
            {
                string extractedId = line.Split('|')[1].Trim();
                if (extractedId == Id)
                    return Log.GetLogFromString(line);
            }
        }

        return null;
    }

    void ILoggerService.CreateLogFileForCurrentDayAndAddLog(Log log)
    {
        string currentDate = DateTime.Now.ToString("yyyy-MM-dd");
        string filePath = Path.Combine(logs_dir, $"{currentDate}.log");

        Directory.CreateDirectory(logs_dir);

        using (StreamWriter writer = new StreamWriter(filePath, true)) // 'true' for append mode
            writer.WriteLine($"\n[{log.Timestamp}] Log Level: {log.LogLevel} | ${log.Id} | Message: {log.Message} | Local IP: {log.LocalIP} | External IP: {log.ExternalIP}\n");
    }

    public bool IsLogForCurrentDayExist(string CurrentDay)
        => File.Exists(Path.Combine(logs_dir, CurrentDay));


    public void AddLogToLogFile(string LogFileName, Log log)
    {
        using (StreamWriter writer = new StreamWriter(Path.Combine(logs_dir, LogFileName), true))
            writer.WriteLine($"\n[{log.Timestamp}] Log Level: {log.LogLevel} | ${log.Id} | Message: {log.Message} | Local IP: {log.LocalIP} | External IP: {log.ExternalIP}\n");
    }
}
