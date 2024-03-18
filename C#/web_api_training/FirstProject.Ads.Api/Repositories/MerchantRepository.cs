using System.Linq.Expressions;
using FirstProject.Ads.Api.Configs;
using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Helpers;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.QueryParams;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using Microsoft.Extensions.Options;
using MongoDB.Driver;
using MongoDB.Bson;
using MongoDB.Driver.Linq;
using MongoDB.Driver.Search;
using SharpCompress.Compressors.Xz;

namespace FirstProject.Ads.Api.Repositories;

public class MerchantRepository : IMerchantRepository
{
    private readonly IMongoCollection<MerchantModel> _collection;
    private readonly ILogger<MerchantRepository> _logger;
    public MerchantRepository(ILogger<MerchantRepository> logger,IOptions<MongoDbSettings> mongodbSettings)
    {
        _logger = logger;
        var client = new MongoClient(mongodbSettings.Value.connectionUri);
        var database = client.GetDatabase(mongodbSettings.Value.databaseName);
        _collection = database.GetCollection<MerchantModel>(mongodbSettings.Value.collectionName);
    }

    public async Task Create(MerchantModel merchantModel)
    {
        await _collection.InsertOneAsync(merchantModel);
    }

    public async Task<List<MerchantModel>?> GetAll(MerchantQueryParams merchantQueryParams)
    {
        //pagination
        var limit = merchantQueryParams.Limit;
        var offset = limit * (merchantQueryParams.PageNumber - 1);
        //sorting
        var sortDefinition = FilteringAndSortingHelper.SortBySelection(merchantQueryParams);
        //filtering
        var filterBuilder = Builders<MerchantModel>.Filter;
        var filterDefinitions = FilteringAndSortingHelper.GetFilters(merchantQueryParams);
        //searching
        var searchDefinition = FilteringAndSortingHelper.SearchDefinition(merchantQueryParams);
        filterDefinitions.Add(searchDefinition);
        
        var filteredResults = await _collection.Find(filterBuilder.And(filterDefinitions))
                .Skip(offset)
                .Limit(limit)
                .Sort(sortDefinition)
                .ToListAsync();

        return filteredResults;
    }
    
    public async Task<MerchantModel?> GetById(string id)
    {
        var filter = Builders<MerchantModel>.Filter.Eq(merchant => merchant.Id, id);
        return await _collection.Find(filter).FirstOrDefaultAsync();
    }

    public async Task UpdateNameAndSurnameById(string id, MerchantPatchRequestModel merchantPatchRequestModel)
    {
        var update = Builders<MerchantModel>.Update
            .Set(merchant => merchant.Name, merchantPatchRequestModel.Name)
            .Set(merchant => merchant.Surname, merchantPatchRequestModel.Surname)
            .Set(merchant => merchant.UpdatedAt, DateTime.UtcNow);
        await _collection.UpdateOneAsync(merchant => merchant.Id == id, update);
    }
    
    public async Task UpdateById(MerchantModel merchantModel)
    {
        await _collection.ReplaceOneAsync(merchant => merchant.Id == merchantModel.Id, merchantModel);
    }
    
    public async Task DeleteById(string id)
    {
        await _collection.DeleteOneAsync(merchant => merchant.Id == id);
    }
}