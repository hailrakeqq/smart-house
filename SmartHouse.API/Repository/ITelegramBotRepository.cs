using SmartHouse.API.Enitity;
namespace SmartHouse.API.Repository;

public interface ITelegramBotRepository
{
    void SendMessageToBot(MessageFromController message);
}