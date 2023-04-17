using System.Net;
using System.Reflection;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using SmartHouse.API.Enitity;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class HomeController : Controller
{
    [HttpPost]
    public IActionResult GetData([FromBody] MessageFromController json)
    {
        return Ok(json);
    }
    [HttpPost("GetMessageIfWaterWasDetected")]
    public IActionResult GetWaterLevel([FromBody] MessageFromController message)
    {
        DateTime timestamp = DateTime.Now;
        message.Timestamp = timestamp.ToString();
        System.Console.WriteLine("==============================================================");
        System.Console.WriteLine($"Timestamp: {message.Timestamp}");
        System.Console.WriteLine($"Message: {message.Message}");
        System.Console.WriteLine("==============================================================");

        using (var client = new WebClient())
        {
            string messageToSend = $"Timestamp: {message.Timestamp}|Message: {message.Message}"; // Замените на своё сообщение
            string url = $"http://localhost:3000/?message={Uri.EscapeDataString(messageToSend)}";
            string response = client.DownloadString(url);
            Console.WriteLine(response);
        }

        return Ok(message.Message);
    }
}