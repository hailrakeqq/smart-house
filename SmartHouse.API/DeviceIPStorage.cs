namespace SmartHouse.API;

public class IP
{
    public string InternalIP { get; set; }
    public string ExternalIP { get; set; }
}
public static class DeviceIPStorage
{
    public static string InternalIP { get; set; }
    public static string ExternalIP { get; set; }
}