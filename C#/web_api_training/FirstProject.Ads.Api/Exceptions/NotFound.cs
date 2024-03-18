namespace FirstProject.Ads.Api.Exceptions;

public class NotFound : CustomError
{
    public NotFound(string message) : base(404, message)
    {
        
    }
}

public class MerchantNotFound : NotFound
{
    public MerchantNotFound(string message) : base(message)
    {
        
    }
}