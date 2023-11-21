namespace SmartHouse.API.Enitity;

public class Device
{
    public int Id { get; set; }
    public string Name { get; set; }
    public string Type { get; set; }
    public string UserId { get; set; } // Внешний ключ для привязки к пользователю
    public User User { get; set; } // Навигационное свойство
}