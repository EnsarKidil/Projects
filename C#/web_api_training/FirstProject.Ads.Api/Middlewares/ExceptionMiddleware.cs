using System.Net;
using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Models;
using HttpContext = Microsoft.AspNetCore.Http.HttpContext;

namespace FirstProject.Ads.Api.Middlewares;

public class ExceptionMiddleware
{
    private readonly RequestDelegate _next;
    private readonly ILogger<ExceptionMiddleware> _logger;

    public ExceptionMiddleware(RequestDelegate next, ILogger<ExceptionMiddleware> logger)
    {
        _next = next;
        _logger = logger;
    }
    
    public async Task InvokeAsync(HttpContext httpContext)
    {
        try
        {
            await _next(httpContext);
        }
        catch (CustomError err)
        {
            await HandleCustomExceptionAsync(httpContext, err);
        }
        catch (Exception ex)
        {
            _logger.LogError($"Something went wrong: {ex}");
            await HandleExceptionAsync(httpContext, ex);
        }
    }
    
    private async Task HandleExceptionAsync(HttpContext context, Exception exception)
    {
        _logger.LogInformation("HandleAsync Method is called");
        context.Response.ContentType = "application/json";
        context.Response.StatusCode = (int)HttpStatusCode.InternalServerError;
        await context.Response.WriteAsync(new ErrorResponseModel
        {
            StatusCode = context.Response.StatusCode,
            Message = "Internal Server Error"
        }.ToString());
    }
    
    private async Task HandleCustomExceptionAsync(HttpContext context, CustomError err)
    {
        context.Response.ContentType = "application/json";
        context.Response.StatusCode = err.StatusCode;
        await context.Response.WriteAsync(new ErrorResponseModel
        {
            StatusCode = context.Response.StatusCode,
            Message = err.Message
        }.ToString());
    }
}