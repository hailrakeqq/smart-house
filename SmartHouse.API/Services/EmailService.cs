using System.Net;
using System.Net.Mail;

namespace SmartHouse.API.Services;

public class EmailService
{
    private readonly IConfiguration _configuration;
    private readonly string _smtpHost;
    private readonly int _smtpPort;
    private readonly string _smtpUsername;
    private readonly string _smtpPassword;

    public EmailService(IConfiguration configuration)
    {
        _configuration = configuration;
        _smtpHost = _configuration["SmtpSettings:Host"]!;
        _smtpPort = int.Parse(_configuration["SmtpSettings:Port"]!);
        _smtpUsername = _configuration["SmtpSettings:Username"]!;
        _smtpPassword = _configuration["SmtpSettings:Password"]!;
    }

    public async Task SendEmailAsync(string toAddress, string subject, string body)
    {
        using (MailMessage mail = new MailMessage(_smtpUsername, toAddress, subject, body))
        {
            using (SmtpClient smtp = new SmtpClient
            {
                Host = _smtpHost,
                Port = _smtpPort,
                EnableSsl = true,
                DeliveryMethod = SmtpDeliveryMethod.Network,
                UseDefaultCredentials = false,
                Credentials = new NetworkCredential(_smtpUsername, _smtpPassword)
            })
            {
                await smtp.SendMailAsync(mail);
            }
        }
    }
}