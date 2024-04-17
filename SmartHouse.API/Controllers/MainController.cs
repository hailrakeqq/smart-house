using Microsoft.AspNetCore.Mvc;
using SmartHouse.API.Enitity;
using SmartHouse.API.Services;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class MainController : Controller
{
    private readonly EmailService _email;
    private readonly ILoggerService _logger;
    public MainController(EmailService email, LoggerService logger)
    {
        _email = email;
        _logger = logger;
    }

    // [HttpPost] //TODO: перенести на фронтенд (запит + обробку)
    // [Route("sendstate")]
    // public async Task<IActionResult> RecieveStateFromMCU([FromBody] RequestBody requestBody)
    // {

    //     return Ok();
    // }

    [HttpPost]
    [Route("waterdetect")]
    public async Task<IActionResult> RecieveWaterDetectMessageFromMCU([FromBody] WaterDetectRequestBody waterDetectRequestBody)
    {
        waterDetectRequestBody.Timestamp = DateTime.Now.ToString("hh:mm:ss tt"); ;

        waterDetectRequestBody.Message += $"\n{waterDetectRequestBody.Timestamp}";
        await _email.SendEmailAsync(waterDetectRequestBody.UserEmail, "SmartHouse: CRITICAL WATER DETECT", waterDetectRequestBody.Message);

        //LOG 
        Log log = new Log(waterDetectRequestBody.LogLevel, waterDetectRequestBody.Timestamp, waterDetectRequestBody.Message);
        String currentDay = DateTime.Now.ToString("dd-MM-yyyy");

        if (!_logger.IsLogForCurrentDayExist(currentDay))
            _logger.CreateLogFileForCurrentDayAndAddLog(log);
        else
            _logger.AddLogToLogFile($"{currentDay}.log", log);

        return Ok();
    }
}