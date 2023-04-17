namespace SmartHouse.API.Enitity;

public class TelegramBot
{
    private readonly string Token;
    public TelegramBot(IConfiguration config)
    {
        Token = config["BotToken"];
        System.Console.WriteLine(Token);
        new TelegramBot(config);
    }
}