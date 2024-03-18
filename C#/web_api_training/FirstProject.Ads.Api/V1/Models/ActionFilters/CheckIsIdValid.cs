using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using MongoDB.Bson.Serialization.IdGenerators;

namespace FirstProject.Ads.Api.V1.Models.ActionFilters;

public class CheckIsIdValid : IActionFilter
{
    public void OnActionExecuting(ActionExecutingContext context)
    {
        if (!context.ActionArguments.ContainsKey("id"))
        {
            return;
        }

        var id = context.ActionArguments["id"] as string;

        if (string.IsNullOrWhiteSpace(id))
        {
            throw new IdNullInput("Id cannot be null or whitespace");
        }
        
        if (id.Length != 36)
        {
            throw new IdLengthNotValid("Id has to be 36 characters");
        }
    }

    public void OnActionExecuted(ActionExecutedContext context)
    {
        
    }
}