namespace FirstProject.Ads.Api.Exceptions;

public class CustomError : Exception
{
    public int StatusCode { get; set; }
    public string Message { get; set; }

    public CustomError(int statusCode, string message) : base(message)
    {
        StatusCode = statusCode;
        Message = message;
    }
}