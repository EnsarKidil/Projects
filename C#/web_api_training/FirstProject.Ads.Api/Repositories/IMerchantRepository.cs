using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.QueryParams;
using FirstProject.Ads.Api.V1.Models.RequestModels;

namespace FirstProject.Ads.Api.Repositories;

public interface IMerchantRepository
{
    Task<List<MerchantModel>?> GetAll(MerchantQueryParams merchantQueryParams);
    Task Create(MerchantModel merchantModel);
    Task<MerchantModel?> GetById(string id);
    Task UpdateNameAndSurnameById(string id, MerchantPatchRequestModel merchantPatchRequestModel);
    Task UpdateById(MerchantModel merchantModel);
    Task DeleteById(string id);
}