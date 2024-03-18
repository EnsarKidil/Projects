using MongoDB.Bson.Serialization.Attributes;

namespace FirstProject.Ads.Api.Models;

public class UserCredentialsModel
{
    [BsonId]
    public string Id { get; set; }
    public string Password { get; set; }
    public string Username { get; set; }
}