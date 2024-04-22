using Microsoft.AspNetCore.Mvc;
using SmartHouse.API.Enitity;
using SmartHouse.API.Services;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class LogController : Controller
{
    private readonly ILoggerService _logger;
    public LogController(EmailService email, ILoggerService logger)
    {
        _logger = logger;
    }

    [HttpGet]
    [Route("getlogs")]
    public IActionResult GetLogs()
    {
        return Ok(_logger.GetAllLogs());
    }

    [HttpGet]
    [Route("getlogbyid")]
    public IActionResult GetLogById([FromBody] string Id)
    {
        return Ok(_logger.GetLogById(Id));
    }
}