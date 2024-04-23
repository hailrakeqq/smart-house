using System.Diagnostics;
using System.Text;

namespace SmartHouse.API;
public static class Toolchain
{

    public static string ExecutePingCommand(string host)
    {
        var processStartInfo = new ProcessStartInfo
        {
            FileName = "ping",
            Arguments = $"-c 4 -W 0.5 {host}",
            RedirectStandardOutput = true,
            UseShellExecute = false,
            CreateNoWindow = true
        };

        using (var process = new Process { StartInfo = processStartInfo })
        {
            process.Start();
            var output = new StringBuilder();

            while (!process.StandardOutput.EndOfStream)
            {
                output.AppendLine(process.StandardOutput.ReadLine());
            }

            process.WaitForExit();

            return output.ToString().Split('\n')[7];
        }
    }
}
