using Microsoft.AspNetCore.Mvc;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class HomeController : Controller
{
    [HttpGet]
    public IActionResult GetData([FromQuery] string data)
    {
        System.Console.WriteLine("Recieved data: " + data);
        return Ok(data);
    }
}