using System.Security.Cryptography;
using System.Text;

namespace SmartHouse.API;

public static class Tool
{
    public static string GenerateHash(string password)
    {
        using (var sha256 = SHA256.Create())
        {
            var hashedBytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(password));
            var hash = BitConverter.ToString(hashedBytes).Replace("-", "").ToLower();

            return hash;
        }
    }
}