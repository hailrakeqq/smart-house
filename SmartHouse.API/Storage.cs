namespace SmartHouse.API;

public class InitialData
{
    public string InternalIP { get; set; }
    public string ExternalIP { get; set; }
    public string UserEmail { get; set; }
}

public static class Storage
{
    public static string InternalIP { get; set; }
    public static string ExternalIP { get; set; }
    public static string UserEmail { get; set; }
}