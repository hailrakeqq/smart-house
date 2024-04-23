public class State
{
    public string LogLevel { get; set; }
    public string UserEmail { get; set; }
    public string ValveState { get; set; }
    public string WaterLevel { get; set; }
    public string Days { get; set; }
    public string Hours { get; set; }
    public string Minutes { get; set; }
    public string Seconds { get; set; }
    public string Uptime { get; set; }
    public string PingResult { get; set; } = string.Empty;
    public string LocalIP { get; set; }
    public string ExternalIP { get; set; }
}