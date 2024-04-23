using System.Net.NetworkInformation;
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
    public MainController(EmailService email, ILoggerService logger)
    {
        _email = email;
        _logger = logger;
    }

    [HttpPost]
    [Route("sendstate")]
    public async Task<IActionResult> RecieveStateFromMCU([FromBody] State state)
    {

        string pingResult = Toolchain.ExecutePingCommand("8.8.8.8");
        // 3 packets transmitted, 3 received, 0% packet loss, time 2002ms
        // if(pingResult.Split(',')[2] == "0")//TODO:дописати if packet lost > 0% send message to mail
        state.PingResult = pingResult;
        return Ok(state);
    }

    [HttpPost]
    [Route("sendinitialrequest")]
    public IActionResult GetInitialIPAddress([FromBody] IP ip)
    {
        DeviceIPStorage.ExternalIP = ip.ExternalIP;
        DeviceIPStorage.InternalIP = ip.InternalIP;
        return Ok();
    }

    [HttpPost]
    [Route("waterdetect")]
    public async Task<IActionResult> RecieveWaterDetectMessageFromMCU([FromBody] WaterDetectRequestBody waterDetectRequestBody)
    {
        waterDetectRequestBody.Timestamp = DateTime.Now.ToString("hh:mm:ss tt"); ;
        string logMessage = waterDetectRequestBody.Message;
        waterDetectRequestBody.Message += $"\n{waterDetectRequestBody.Timestamp}";
        await _email.SendEmailAsync(waterDetectRequestBody.UserEmail, "SmartHouse: CRITICAL WATER DETECT", waterDetectRequestBody.Message);

        //LOG 
        Log log = new Log(waterDetectRequestBody.LogLevel, waterDetectRequestBody.Timestamp, logMessage, waterDetectRequestBody.LocalIP, waterDetectRequestBody.ExternalIP);
        String currentDay = DateTime.Now.ToString("dd-MM-yyyy");

        if (!_logger.IsLogForCurrentDayExist(currentDay))
            _logger.CreateLogFileForCurrentDayAndAddLog(log);
        else
            _logger.AddLogToLogFile($"{currentDay}.log", log);

        return Ok();
    }
}