namespace SmartHouse.API.Enitity;

public class WaterDetectRequestBody
{
    public String Timestamp { get; set; }
    public String LogLevel { get; set; }
    public String UserEmail { get; set; }
    public String Message { get; set; }
}