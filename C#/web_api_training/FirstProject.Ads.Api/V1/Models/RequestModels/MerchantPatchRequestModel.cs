using FirstProject.Ads.Api.Models;

namespace FirstProject.Ads.Api.V1.Models.RequestModels;

public class MerchantPatchRequestModel
{
    /// <summary>
    /// The desired name of the merchant to update.
    /// </summary>
    public string Name { get; set; }
    /// <summary>
    /// The desired surname of the merchant to update.
    /// </summary>
    public string Surname { get; set; }
}