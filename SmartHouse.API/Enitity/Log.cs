namespace SmartHouse.API.Enitity;

public class Log
{
    public String Id { get; set; } //GUID to String 
    public String LogLevel { get; set; }
    public String Timestamp { get; set; } //Timestamp to String
    public String Message { get; set; }

    public Log(String loglevel, String timestamp, String message)
    {
        Id = Guid.NewGuid().ToString();
        LogLevel = loglevel;
        Timestamp = timestamp;
        Message = message;
    }

    public static Log GetLogFromString(string logEntryString)
    {
        string[] parts = logEntryString.Split('|');

        if (parts.Length < 4)
            throw new ArgumentException("Invalid log entry format.");

        string timestamp = parts[0].Split(']')[0].Trim('[', ']');
        string logLevel = parts[0].Split(':')[1].Trim();
        string id = parts[1].Trim().Trim('$');
        string message = parts[2].Split(':')[1].Trim();

        Log log = new Log(logLevel, timestamp, message);
        log.Id = id;

        return log;
    }
}