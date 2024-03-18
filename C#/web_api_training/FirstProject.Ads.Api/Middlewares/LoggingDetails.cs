using System.Text.Json;

namespace FirstProject.Ads.Api.Middlewares;

public class LoggingDetails
{
    public int StatusCode { get; set; }
    public string? Message { get; set; }
    public string? Path { get; set; }
    public string TimeStamp { get; set; }

    public LoggingDetails(int statusCode, string message, string path)
    {
        StatusCode = statusCode;
        Message = message;
        Path = path;
        TimeStamp = DateTime.UtcNow.ToString("yyyy-MM-dd HH:mm:ss.fff");
    }

    public override string ToString()
    {
        return JsonSerializer.Serialize(this);
    }
    
}