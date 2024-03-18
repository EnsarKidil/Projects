using System.Linq.Expressions;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.QueryParams;
using MongoDB.Bson;
using MongoDB.Driver;

namespace FirstProject.Ads.Api.Helpers;

public static class FilteringAndSortingHelper
{
    public static SortDefinition<MerchantModel> SortBySelection(MerchantQueryParams merchantQueryParams)
    {
        var sortBuilder = Builders<MerchantModel>.Sort;
        if (string.Equals(merchantQueryParams.SortOrder, "asc", StringComparison.OrdinalIgnoreCase))
        {
            return sortBuilder.Ascending(merchantQueryParams.SortColumn);
        }

        // Diğer durumlarda varsayılan olarak ASC olarak sırala
        return sortBuilder.Descending(merchantQueryParams.SortColumn);
    }

    public static List<FilterDefinition<MerchantModel>> GetFilters(MerchantQueryParams merchantQueryParams)
    {
        var filterBuilder = Builders<MerchantModel>.Filter;
        var filters = new List<FilterDefinition<MerchantModel>>();

        var filterDict = new Dictionary<Expression<Func<MerchantModel, string>>, string>
        {
            { m => m.Name, merchantQueryParams.Name },
            { m => m.Surname, merchantQueryParams.Surname }
        };

        filters.Add(filterBuilder.Empty);

        foreach (var filter in filterDict)
        {
            if (!string.IsNullOrWhiteSpace(filter.Value))
            {
                filters.Add(filterBuilder.Eq(filter.Key, filter.Value));
            }
        }

        return filters;
    }

    public static FilterDefinition<MerchantModel> SearchDefinition(MerchantQueryParams merchantQueryParams)
    {
        var filterBuilder = Builders<MerchantModel>.Filter;
        var searchKeyList = new List<FilterDefinition<MerchantModel>>();
        var searchKeys = new List<Expression<Func<MerchantModel, object>>>()
        {
            m => m.Name,
            m => m.Surname,
            m => m.Storename
        };

        foreach (var term in searchKeys)
        {
            searchKeyList.Add(filterBuilder.Regex(term, merchantQueryParams.SearchTerm));
        }

        var searchDefinition = filterBuilder.Or(searchKeyList);
        return searchDefinition;
    }
}