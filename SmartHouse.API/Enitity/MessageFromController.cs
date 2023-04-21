namespace SmartHouse.API.Enitity;

public class MessageFromController
{
    public string Type { get; set; }
    public string Timestamp { get; set; }
    public string Message { get; set; } = string.Empty;
}