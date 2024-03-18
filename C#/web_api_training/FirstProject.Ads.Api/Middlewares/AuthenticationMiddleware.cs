using System.Security.Claims;
using FirstProject.Ads.Api.Exceptions;

namespace FirstProject.Ads.Api.Middlewares;

public class AuthenticationMiddleware
{
    private readonly RequestDelegate _next;

    public AuthenticationMiddleware(RequestDelegate next)
    {
        _next = next;
    }

    public async Task InvokeAsync(HttpContext context)
    {
        var requestMethod = context.Request.Method;
        
        if ((requestMethod.Equals("POST", StringComparison.OrdinalIgnoreCase) &&
             context.Request.Path.Equals("/Auth/Login")) ||
            (requestMethod.Equals("POST", StringComparison.OrdinalIgnoreCase) &&
             context.Request.Path.Equals("/Auth/SignUp")))
        {
            await _next(context);
        }

        else
        {
            var jwtToken = context.Request.Headers["Authorization"].FirstOrDefault()?.Replace("Bearer ", "");
            if (!string.IsNullOrWhiteSpace(jwtToken))
            {
                using (var httpClient = new HttpClient())
                {
                    var verifyUrl = "http://localhost:5030/Auth/Verify";
                    var content = new StringContent(jwtToken, System.Text.Encoding.UTF8, "application/json");
                    var response = await httpClient.PostAsync(verifyUrl, content);
                    await _next(context);
                }
            }
            else
            { 
                throw new BadRequest("not valid");
            }
        }
    }
}
