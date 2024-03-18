using FirstProject.Ads.Api.Configs;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using Microsoft.Extensions.Options;
using MongoDB.Driver;

namespace FirstProject.Ads.Api.Repositories;

public class AuthRepository : IAuthRepository
{
    private readonly IMongoCollection<UserCredentialsModel> _collection;
    private readonly ILogger<MerchantRepository> _logger;
    public AuthRepository(ILogger<MerchantRepository> logger,IOptions<MongoDbSettings> mongodbSettings)
    {
        _logger = logger;
        var client = new MongoClient(mongodbSettings.Value.connectionUri);
        var database = client.GetDatabase(mongodbSettings.Value.databaseName);
        _collection = database.GetCollection<UserCredentialsModel>("User");
    }

    public async Task SignUp(UserCredentialsModel userCredentialsModel)
    {
        await _collection.InsertOneAsync(userCredentialsModel);
    }
    
    public async Task<UserCredentialsModel?> Login(UserCredentialsRequestModel userCredentialsRequestModel)
    {
        var filterBuilder = Builders<UserCredentialsModel>.Filter;
        var filter = filterBuilder.And(
            filterBuilder.Eq(x => x.Username, userCredentialsRequestModel.Username), 
                        filterBuilder.Eq(x => x.Password, userCredentialsRequestModel.Password));
        return await _collection.Find(filter).FirstOrDefaultAsync();
    }
    
    public async Task<UserCredentialsModel?> Verify(string id)
    {
        var filterBuilder = Builders<UserCredentialsModel>.Filter;
        var filter = filterBuilder.Eq(x => x.Id, id);
        return await _collection.Find(filter).FirstOrDefaultAsync();
    }
}