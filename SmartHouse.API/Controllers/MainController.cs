using System.Net.Mail;
using System.Net.NetworkInformation;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
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

    [HttpGet]
    [Route("getstatemoq")]
    public async Task<IActionResult> RecieveStateFromMCUMOQ()
    {
        string Timestamp = DateTime.Now.ToString("ddd MMM dd HH:mm:ss yyyy");
        string pingResult = Toolchain.ExecutePingCommand("192.168.0.1");//"3 packets transmitted, 3 received, 0% packet loss, time 2033ms";
        var packetLoss = int.Parse(pingResult.Split(',')[2].Split('%')[0].Trim());
        State state = new State();


        state.LogLevel = "Info";
        state.UserEmail = "boklanura@gmail.com";
        state.ValveState = "Close";
        state.WaterLevel = "0 cm";
        state.Uptime = "1 day 5 hours 13 minutes 54 seconds";
        state.PingResult = pingResult;
        state.LocalIP = "192.168.0.14";
        state.ExternalIP = "154.12.23.51";

        if (packetLoss > 0)
        {
            string lvl = packetLoss == 100 ? "Critical" : "Warning";
            string subject = $"** {lvl} - {(lvl == "Critical" ? "Host is DOWN" : "Host have packet loss")}**";
            string message = $"Host: Local IP - {state.LocalIP}\tExternal IP - {state.ExternalIP}\nState: {(lvl == "Critical" ? "Down" : "UP")}\nInfo: {pingResult}\n{Timestamp}";

            await _email.SendEmailAsync(state.UserEmail, subject, message);

            _logger.AddLog(new Log(lvl, Timestamp, pingResult, state.LocalIP, state.ExternalIP));
        }

        return Ok(state);
    }

    [HttpGet]
    [Route("getstate")]
    public async Task<IActionResult> RecieveStateFromMCU()
    {
        State state = null;

        string Timestamp = DateTime.Now.ToString("ddd MMM dd HH:mm:ss yyyy");
        string pingResult = Toolchain.ExecutePingCommand(Storage.InternalIP);
        var packetLoss = Toolchain.ExtractPacketLossPercentage(pingResult);
        if (packetLoss > 0)
        {
            string lvl = packetLoss == 100 ? "Critical" : "Warning";
            string subject = $"** {lvl} - {(lvl == "Critical" ? "Host is DOWN" : "Host have packet loss")}**";
            string message = $"Host: Local IP - {Storage.InternalIP}\tExternal IP - {Storage.ExternalIP}\nState: {(lvl == "Critical" ? "Down" : "UP")}\nInfo: {pingResult}\n{Timestamp}";

            // Отправка электронного письма
            await _email.SendEmailAsync(Storage.UserEmail, subject, message);

            // Журналирование
            _logger.AddLog(new Log(lvl, Timestamp, pingResult, Storage.InternalIP, Storage.ExternalIP));
        }

        using (var httpClient = new HttpClient())
        {
            var response = await httpClient.GetAsync($"http://{Storage.InternalIP}:80/getState");
            string jsonResponse = await response.Content.ReadAsStringAsync();

            JObject jsonObject = JsonConvert.DeserializeObject<JObject>(jsonResponse);

            state = new State
            {
                LogLevel = (string)jsonObject["logLevel"],
                UserEmail = (string)jsonObject["userEmail"],
                ValveState = (string)jsonObject["valveState"],
                WaterLevel = (string)jsonObject["waterLevel"],
                Days = (string)jsonObject["days"],
                Hours = (string)jsonObject["hours"],
                Minutes = (string)jsonObject["minutes"],
                Seconds = (string)jsonObject["seconds"],
                Uptime = (string)jsonObject["uptime"],
                PingResult = pingResult,
                LocalIP = (string)jsonObject["localIP"],
                ExternalIP = (string)jsonObject["externalIP"]
            };
        }

        return Ok(state);
    }

    [HttpPost]
    [Route("senddeviceip")]
    public IActionResult GetInitialIPAddress([FromBody] InitialData initialData)
    {
        Storage.ExternalIP = initialData.ExternalIP;
        Storage.InternalIP = initialData.InternalIP;
        Storage.UserEmail = initialData.UserEmail;
        return Ok();
    }

    [HttpPost]
    [Route("waterdetect")]
    public async Task<IActionResult> RecieveWaterDetectMessageFromMCU([FromBody] WaterDetectRequestBody waterDetectRequestBody)
    {
        waterDetectRequestBody.Timestamp = DateTime.Now.ToString("hh:mm:ss tt");
        string Timestamp = DateTime.Now.ToString("ddd MMM dd HH:mm:ss yyyy");
        string logMessage = waterDetectRequestBody.Message;
        waterDetectRequestBody.Message += $"\n{Timestamp}";
        await _email.SendEmailAsync(waterDetectRequestBody.UserEmail, "SmartHouse: CRITICAL WATER DETECT", waterDetectRequestBody.Message);

        _logger.AddLog(new Log(waterDetectRequestBody.LogLevel, Timestamp, logMessage, waterDetectRequestBody.LocalIP, waterDetectRequestBody.ExternalIP));

        return Ok();
    }
}