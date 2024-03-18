using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using FluentValidation;
using SharpCompress.Archives;

namespace FirstProject.Ads.Api.V1.Models.Validators;

public class MerchantPatchRequestValidator : AbstractValidator<MerchantPatchRequestModel>
{
    public MerchantPatchRequestValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithState(x => throw new NameNullInput("Name cannot be null"))
            .Length(2, 20).WithState(x => throw new NameLengthNotValid("Name has to be between 2 and 20 characters"));
        RuleFor(x => x.Surname)
            .NotEmpty().WithState(x => throw new SurnameNullInput("Surname cannot be null"))
            .Length(2, 20).WithState(x => throw new SurnameLengthNotValid("Surname has to be between 2 and 20 characters"));
    }
}