using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace FirstProject.Ads.Api.Models;

public class MerchantModel 
{
    /// <summary>
    /// Guid Id of the merchant.
    /// </summary>
    [BsonId]
    //[BsonRepresentation(BsonType.String)]
    public string Id { get; set; }
    /// <summary>
    /// Name of the merchant.
    /// </summary>
    public string Name { get; set; }
    /// <summary>
    /// Surname of the merchant.
    /// </summary>
    public string Surname { get; set; }
    /// <summary>
    /// Fullname of the merchant's bank account.
    /// </summary>
    public string Fullname { get; set; }
    /// <summary>
    /// Iban of the merchant's bank account.
    /// </summary>
    public string Iban { get; set; }
    /// <summary>
    /// Store name of the merchant.
    /// </summary>
    public string Storename { get; set; }
    /// <summary>
    /// Date the seller's account was created
    /// </summary>
    public DateTime CreatedAt { get; set; }
    /// <summary>
    /// Date the seller's account was last updated
    /// </summary>
    public DateTime? UpdatedAt { get; set; }
}
