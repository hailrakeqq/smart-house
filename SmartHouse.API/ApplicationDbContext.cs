using Microsoft.EntityFrameworkCore;

using SmartHouse.API.Enitity;

namespace SmartHouse.API;

public class ApplicationDbContext : DbContext
{
    public ApplicationDbContext(DbContextOptions options) : base(options)
    {
    }

    public DbSet<User> users { get; set; }
    public DbSet<AuthRefreshToken> refreshtokens { get; set; }
    public DbSet<Device> devices { get; set; }
}