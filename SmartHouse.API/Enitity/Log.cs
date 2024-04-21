using System.Runtime.InteropServices;
namespace SmartHouse.API.Enitity;

public class Log
{
    public String Id { get; set; } //GUID to String 
    public String LogLevel { get; set; }
    public String Timestamp { get; set; } //Timestamp to String
    public String Message { get; set; }
    public String LocalIP { get; set; }
    public String ExternalIP { get; set; }

    public Log(String loglevel, String timestamp, String message, String localIP, String externalIP)
    {
        Id = Guid.NewGuid().ToString();
        LogLevel = loglevel;
        Timestamp = timestamp;
        Message = message;
        LocalIP = localIP;
        ExternalIP = externalIP;
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
        string localIP = parts[3].Split(":")[1].Trim();
        string externalIP = parts[4].Split(":")[1].Trim();

        Log log = new Log(logLevel, timestamp, message, localIP, externalIP);
        log.Id = id;

        return log;
    }
}