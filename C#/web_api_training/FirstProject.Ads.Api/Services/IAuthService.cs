using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.V1.Models.RequestModels;

namespace FirstProject.Ads.Api.Services;

public interface IAuthService
{
    Task SignUp(UserCredentialsModel userCredentialsModel);
    Task<UserCredentialsModel?> Login(UserCredentialsRequestModel userCredentialsRequestModel);
    Task<UserCredentialsModel?> Verify(string id);
}