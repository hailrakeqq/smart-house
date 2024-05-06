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

            var lines = output.ToString().Split('\n');
            foreach (var line in lines)
            {
                if (line.Contains("packets transmitted"))
                    return line.Trim();
            }

            return "Information not found";
        }
    }

    public static int ExtractPacketLossPercentage(string pingOutput)
    {
        var parts = pingOutput.Split(' ');

        foreach (var part in parts)
        {
            if (part.Contains("%"))
            {
                var percentageString = part.Trim('%');
                return int.TryParse(percentageString, out int percentage) ? percentage : 404;
            }
        }

        return 404;
    }
}
