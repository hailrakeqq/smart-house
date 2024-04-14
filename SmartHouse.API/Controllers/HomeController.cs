using System.Net;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using SmartHouse.API.Enitity;
using SmartHouse.API.Services;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class HomeController : Controller
{
    private readonly EmailService _email;
    public HomeController(EmailService email)
    {
        _email = email;
    }

    private string timestamp = DateTime.Now.ToString();

    [HttpPost]
    [Route("sendtestsmtp")]
    public async Task<IActionResult> Test([FromBody] MailModel mailModel)
    {
        await _email.SendEmailAsync(mailModel.ToAddress, mailModel.Subject, mailModel.Body);
        return Ok();
    }
}