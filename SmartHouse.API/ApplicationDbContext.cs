using Microsoft.EntityFrameworkCore;
using SmartHouse.API.Enitity;

namespace SmartHouse.API;

public class ApplicationDbContext : DbContext
{
    public ApplicationDbContext(DbContextOptions options) : base(options)
    {
    }

    public DbSet<Log> logs { get; set; }
}