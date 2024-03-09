namespace SmartHouse.API.Enitity;

public class Log
{
    public string Id { get; set; } //GUID to String 
    public string logLevel { get; set; }
    public string Timestamp { get; set; } //Timestamp to String
    public string Message { get; set; }

}