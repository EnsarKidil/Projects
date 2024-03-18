using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Helpers;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.QueryParams;
using FirstProject.Ads.Api.Services;
using FirstProject.Ads.Api.V1.Models.ActionFilters;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using FirstProject.Ads.Api.V1.Models.ResponseModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace FirstProject.Ads.Api.V1.Controllers;

//[Authorize]
[ApiController]
[Route("[controller]")]

public class MerchantController : ControllerBase
{
    private readonly IMerchantService _merchantService;
    private readonly ILogger<MerchantController> _logger;

    public MerchantController(ILogger<MerchantController> logger,IMerchantService merchantService)
    {
        _merchantService = merchantService;
        _logger = logger;
    }
    
    /// <summary>
    /// Retrieves all merchants based on the provided query parameters.
    /// </summary>
    /// <remarks>
    /// Throws 404 Not Found if any merchants are not registered to the database.
    /// </remarks>
    [HttpGet("")]
    public async Task<IActionResult> GetAll([FromQuery] MerchantQueryParams merchantQueryParams)
    {
        var merchantList = await _merchantService.GetAll(merchantQueryParams);
        if (merchantList == null)
        {
            throw new MerchantNotFound("Merchants not found");
        }
        return Ok(merchantList);
    }
    
    /// <summary>
    /// Creates a new merchant.
    /// </summary>
    /// <param name="merchantCreateRequestModel">Data required to create a new merchant.</param>
    [HttpPost("")]
    public async Task<IActionResult> Create([FromBody] MerchantCreateRequestModel merchantCreateRequestModel) //birden fazla merchant tek istekte kaydedilecekse bu ne olur
    {
        var merchantModel = MerchantModelHelper.FromCreateRequestModelToDbModel(merchantCreateRequestModel); //extensions içinde yer alacak. fromrequesttodto db model
        await _merchantService.Create(merchantModel);
        return Created(nameof(Create), $"Created ID: {merchantModel.Id}");
    }
    
    /// <summary>
    /// Retrieves a merchant by its unique identifier.
    /// </summary>
    /// <param name="id">The unique identifier of the merchant.</param>
    [HttpGet("{id}")]
    public async Task<IActionResult> GetById([FromRoute] string id)
    {
        var merchantModel = await _merchantService.GetById(id);
        if (merchantModel == null)
        {
            throw new MerchantNotFound("Merchant not found");
        }
        var merchantResponseModel = MerchantModelHelper.FromDbModelToResponseModel(merchantModel); //dto to response db model
        return Ok(merchantResponseModel);
    }
    
    /// <summary>
    /// Updates the name and surname of a merchant by its unique identifier.
    /// </summary>
    /// <param name="id">The unique identifier of the merchant.</param>
    /// <param name="merchantPatchRequestModel">Data required to update the name and surname of a merchant.</param>
    [HttpPatch("{id}")]
    public async Task<IActionResult> UpdateNameAndSurnameById([FromRoute] string id, [FromBody] MerchantPatchRequestModel merchantPatchRequestModel)
    {
        var merchantModel = await _merchantService.GetById(id);
        if (merchantModel == null)
        {
            throw new MerchantNotFound("Merchant not found");
        }
        await _merchantService.UpdateNameAndSurnameById(id, merchantPatchRequestModel);
        return Ok($"Updated the name and surname of the merchant with ID: {merchantModel.Id}");
    }
    
    /// <summary>
    /// Updates a merchant by its unique identifier.
    /// </summary>
    /// <param name="id">The unique identifier of the merchant.</param>
    /// <param name="merchantPutRequestModel">Data required to update a merchant.</param>
    [HttpPut("{id}")]
    public async Task<IActionResult> UpdateById([FromRoute] string id, [FromBody] MerchantPutRequestModel merchantPutRequestModel) //updatebyid
    {
        var merchantModel = await _merchantService.GetById(id); //burada getbyid kullan ve null check yap
        if (merchantModel == null)
        {
            throw new MerchantNotFound("Merchant not found");
        }
        var updatedMerchantModel = MerchantModelHelper.FromPutRequestModelToDbModel(id, merchantPutRequestModel, merchantModel);
        await _merchantService.UpdateById(updatedMerchantModel);
        return Ok($"Updated the merchant with ID: {id}");
    }

    /// <summary>
    /// Deletes a merchant by its unique identifier.
    /// </summary>
    /// <param name="id">The unique identifier of the merchant.</param>
    [HttpDelete("{id}")] //id guid değil string olacak
    public async Task<IActionResult> DeleteById([FromRoute] string id) //buolabilir + from route ve frombody beraber kullanılabilir
    {
        var merchantModel = await _merchantService.GetById(id);
        if (merchantModel == null)
        {
            throw new MerchantNotFound("Merchant not found");
        }
        await _merchantService.DeleteById(id);
        return Ok($"Deleted the merchant with ID: {merchantModel.Id}");
    }
}
