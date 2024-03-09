using System.Net;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace SmartHouse.API.Controllers;

[ApiController]
[Route("api/[controller]")]
public class HomeController : Controller
{
    private string timestamp = DateTime.Now.ToString();
}
