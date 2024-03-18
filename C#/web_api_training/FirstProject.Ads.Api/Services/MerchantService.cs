using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.QueryParams;
using FirstProject.Ads.Api.Repositories;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using Microsoft.Extensions.Options;

namespace FirstProject.Ads.Api.Services;

public class MerchantService : IMerchantService 
{
    private readonly IMerchantRepository _merchantRepository;
    private readonly ILogger<MerchantService> _logger;

    public MerchantService(ILogger<MerchantService> logger, IMerchantRepository merchantRepository)
    {
        _merchantRepository = merchantRepository;
        _logger = logger;
    }

    public async Task Create(MerchantModel merchantModel)
    {
        await _merchantRepository.Create(merchantModel);
    }

    public async Task<List<MerchantModel>?> GetAll(MerchantQueryParams merchantQueryParams)
    {
        return await _merchantRepository.GetAll(merchantQueryParams);
    }

    public async Task<MerchantModel?> GetById(string id)
    {
        return await _merchantRepository.GetById(id);
    }

    public async Task UpdateNameAndSurnameById(string id, MerchantPatchRequestModel merchantPatchRequestModel)
    {
        await _merchantRepository.UpdateNameAndSurnameById(id, merchantPatchRequestModel);
    }

    public async Task UpdateById(MerchantModel merchantModel)
    {
        await _merchantRepository.UpdateById(merchantModel);
    }

    public async Task DeleteById(string id)
    {
        await _merchantRepository.DeleteById(id);
    }
}