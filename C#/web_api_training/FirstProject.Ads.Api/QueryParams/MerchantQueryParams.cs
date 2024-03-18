namespace FirstProject.Ads.Api.QueryParams;

public class MerchantQueryParams
{
    //filtering
    /// <summary>
    /// The name of the merchant to filter by.
    /// </summary>
    public string? Name { get; set; } = string.Empty;
    /// <summary>
    /// The Surname of the merchant to filter by.
    /// </summary>
    public string? Surname { get; set; } = string.Empty;
    //pagination
    /// <summary>
    /// The value of the max data on a page.
    /// </summary>
    public int Limit { get; set; } = 5;
    /// <summary>
    /// The value of the page number.
    /// </summary>
    public int PageNumber { get; set; } = 1;
    //searching
    /// <summary>
    /// The term to search by.
    /// </summary>
    public string? SearchTerm { get; set; } = string.Empty;
    //sorting
    /// <summary>
    /// The column of the merchant model to sort.
    /// </summary>
    public string? SortColumn { get; set; } = "CreatedAt";
    /// <summary>
    /// The order type to sort.
    /// </summary>
    public string? SortOrder { get; set; } = "desc";
}
    