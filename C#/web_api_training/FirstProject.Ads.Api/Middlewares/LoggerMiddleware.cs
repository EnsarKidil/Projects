using FirstProject.Ads.Api.Exceptions;

namespace FirstProject.Ads.Api.Middlewares;

public class LoggerMiddleware
{
    private readonly RequestDelegate _next;
    private ILogger<LoggerMiddleware> _logger;

    public LoggerMiddleware(RequestDelegate next, ILogger<LoggerMiddleware> logger)
    {
        _next = next;
        _logger = logger;
    }

    public async Task InvokeAsync(HttpContext httpContext)
    {
        try
        {
            await _next(httpContext);
            var log = new LoggingDetails(httpContext.Response.StatusCode, "ok", httpContext.Request.Path).ToString();
            _logger.LogInformation(log);
        }
        catch (CustomError err)
        {
            var log = new LoggingDetails(err.StatusCode, err.Message, httpContext.Request.Path).ToString();
            _logger.LogWarning(log);
            throw;
        }
        catch (Exception ex)
        {
            var log = new LoggingDetails(httpContext.Response.StatusCode, ex.Message, httpContext.Request.Path).ToString();
            _logger.LogError(log);
            throw;
        }
    }
}