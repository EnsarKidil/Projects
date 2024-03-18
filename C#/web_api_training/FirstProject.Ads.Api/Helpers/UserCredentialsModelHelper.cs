using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;

namespace FirstProject.Ads.Api.Helpers;

public class UserCredentialsModelHelper
{
    public static UserCredentialsModel FromUserCredentialsRequestModelToDbModel(UserCredentialsRequestModel userCredentialsRequestModel)
    {
        return new UserCredentialsModel
        {
            Password = userCredentialsRequestModel.Password,
            Username = userCredentialsRequestModel.Username,
            Id = Guid.NewGuid().ToString()
        };
    }
}