using FirstProject.Ads.Api.Models;

namespace FirstProject.Ads.Api.V1.Models.RequestModels;

public class MerchantCreateRequestModel
{
    /// <summary>
    /// The name of the merchant.
    /// </summary>
    public string Name { get; set; }
    /// <summary>
    /// The Surname of the merchant.
    /// </summary>
    public string Surname { get; set; }
    /// <summary>
    /// The Fullname of the merchant's bank account.
    /// </summary>
    public string Fullname { get; set; }
    /// <summary>
    /// The iban of the merchant's bank account.
    /// </summary>
    public string Iban { get; set; }
    /// <summary>
    /// The Storename of the merchant.
    /// </summary>
    public string Storename { get; set; }
}