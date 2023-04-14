using Microsoft.AspNetCore.Mvc;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class HomeController : Controller
{
    [HttpGet]
    public IActionResult GetData()
    {
        System.Console.WriteLine("request work!");
        return Ok("test");
    }
}