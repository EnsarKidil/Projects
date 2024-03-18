using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using FluentValidation;

namespace FirstProject.Ads.Api.V1.Models.Validators;

public class MerchantCreateRequestValidator : AbstractValidator<MerchantCreateRequestModel>
{
    public MerchantCreateRequestValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithState(x => throw new NameNullInput("Name cannot be null"))
            .Must(name => ValidLength(name.Length)).WithState(x => throw new NameLengthNotValid("Name has to be between 2 and 20 characters"));//WithMessage("Name has to be between 2 and 20 characters");
        RuleFor(x => x.Surname)
            .NotEmpty().WithState(x => throw new SurnameNullInput("Surname cannot be null"))
            .Must(surname => ValidLength(surname.Length)).WithState(x => throw new SurnameLengthNotValid("Surname has to be between 2 and 20 characters"));
        RuleFor(x => x.Storename)
            .NotEmpty().WithState(x => throw new StorenameNullInput("Store name cannot be null"))
            .Must(storeName => ValidLength(storeName.Length)).WithState(x => throw new StorenameLengthNotValid("Store name has to be between 2 and 20 characters"));
        RuleFor(x => x.Fullname)
            .NotEmpty().WithState(x => throw new FullnameNullInput("Fullname cannot be null"))
            .Must(fullName => FullNameValidLength(fullName.Length)).WithState(x => throw new FullnameLengthNotValid("Fullname has to be between 4 and 40 characters"));
        RuleFor(x => x.Iban)
            .NotEmpty().WithState(x => throw new IbanNullInput("Iban cannot be null"))
            .Must(iban => IbanLength(iban)).WithState(x => throw new IbanLengthNotValid("Iban must be 26 characters"))
            .Must(iban => IbanStartsWith(iban)).WithState(x => throw new IbanStartsWithNotValid("Iban must start with TR"))
            .Must(iban => IbanDigitParts(iban)).WithState(x => throw new IbanEndsWithNotValid("Iban must contain numerical values after TR"));
    }

    public bool ValidLength(int length)
    {
        return length >= 2 && length <= 20;
    }

    public bool FullNameValidLength(int length)
    {
        return length >= 4 && length <= 20;
    }

    public bool IbanLength(string iban)
    {
        return iban.Length == 26;
    }

    public bool IbanStartsWith(string iban)
    {
        return iban.StartsWith("TR");
    }

    public bool IbanDigitParts(string iban)
    {
        var digitparts = iban[2..];
        return digitparts.All(char.IsDigit);
    }
}