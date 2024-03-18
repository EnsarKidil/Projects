namespace FirstProject.Ads.Api.V1.Models.RequestModels;

public class MerchantPutRequestModel
{
    /// <summary>
    /// The desired name of the merchant to update.
    /// </summary>
    public string Name { get; set; }
    /// <summary>
    /// The desired surname of the merchant to update.
    /// </summary>
    public string Surname { get; set; }
    /// <summary>
    /// The desired fullname of the merchant's bank account to update.
    /// </summary>
    public string Fullname { get; set; }
    /// <summary>
    /// The desired iban of the merchant's bank account to update.
    /// </summary>
    public string Iban { get; set; }
    /// <summary>
    /// The desired store name of the merchant to update.
    /// </summary>
    public string Storename { get; set; }
}