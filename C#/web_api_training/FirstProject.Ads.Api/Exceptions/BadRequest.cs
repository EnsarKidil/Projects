namespace FirstProject.Ads.Api.Exceptions;

public class BadRequest : CustomError
{
    public BadRequest(string message) : base(400,message)
    {
        
    }
}

public class NameNullInput : BadRequest
{
    public NameNullInput(string message) : base(message)
    {
        
    }
}

public class SurnameNullInput : BadRequest
{
    public SurnameNullInput(string message) : base(message)
    {
        
    }
}

public class FullnameNullInput : BadRequest
{
    public FullnameNullInput(string message) : base(message)
    {

    }
}

public class IbanNullInput : BadRequest
{
    public IbanNullInput(string message) : base(message)
    {

    }
}

public class StorenameNullInput : BadRequest
{
    public StorenameNullInput(string message) : base(message)
    {

    }
}

public class IdNullInput : BadRequest
{
    public IdNullInput(string message) : base(message)
    {

    }
}

public class NameLengthNotValid : BadRequest
{
    public NameLengthNotValid(string message) : base(message)
    {

    }
}

public class SurnameLengthNotValid : BadRequest
{
    public SurnameLengthNotValid(string message) : base(message)
    {

    }
}

public class FullnameLengthNotValid : BadRequest
{
    public FullnameLengthNotValid(string message) : base(message)
    {

    }
}

public class IbanLengthNotValid : BadRequest
{
    public IbanLengthNotValid(string message) : base(message)
    {

    }
}

public class StorenameLengthNotValid : BadRequest
{
    public StorenameLengthNotValid(string message) : base(message)
    {

    }
}

public class IdLengthNotValid : BadRequest
{
    public IdLengthNotValid(string message) : base(message)
    {

    }
}

public class IbanStartsWithNotValid : BadRequest
{
    public IbanStartsWithNotValid(string message) : base(message)
    {

    }
}

public class IbanEndsWithNotValid : BadRequest
{
    public IbanEndsWithNotValid(string message) : base(message)
    {

    }
}

public class InvalidCredentials : BadRequest
{
    public InvalidCredentials(string message) : base(message)
    {
        
    }
}

