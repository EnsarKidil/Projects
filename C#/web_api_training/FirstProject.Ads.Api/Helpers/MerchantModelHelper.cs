using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using FirstProject.Ads.Api.V1.Models.ResponseModels;

namespace FirstProject.Ads.Api.Helpers;

public class MerchantModelHelper
{
    public static MerchantModel FromCreateRequestModelToDbModel(MerchantCreateRequestModel merchantCreateRequestModel)
    {
        return new MerchantModel
        {
            Id = Guid.NewGuid().ToString(),
            Name = merchantCreateRequestModel.Name,
            Surname = merchantCreateRequestModel.Surname,
            Fullname = merchantCreateRequestModel.Fullname,
            Iban = merchantCreateRequestModel.Iban,
            Storename = merchantCreateRequestModel.Storename,
            CreatedAt = DateTime.UtcNow,
            UpdatedAt = DateTime.UtcNow
        };
    }
    
    public static MerchantModel FromPutRequestModelToDbModel(string id, MerchantPutRequestModel merchantPutRequestModel, MerchantModel merchantModel)
    {
        return new MerchantModel
        {
            Id = id,
            Name = merchantPutRequestModel.Name,
            Surname = merchantPutRequestModel.Surname,
            Fullname = merchantPutRequestModel.Fullname,
            Iban = merchantPutRequestModel.Iban,
            Storename = merchantPutRequestModel.Storename,
            CreatedAt = merchantModel.CreatedAt,
            UpdatedAt = DateTime.UtcNow
        };
    } 
    
    public static MerchantResponseModel FromDbModelToResponseModel(MerchantModel merchantModel)
    {
        return new MerchantResponseModel
        {
            Id = merchantModel.Id,
            Name = merchantModel.Name,
            Surname = merchantModel.Surname
        };
    }
}