using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.Repositories;
using FirstProject.Ads.Api.V1.Models.RequestModels;

namespace FirstProject.Ads.Api.Services;

public class AuthService : IAuthService
{
    private readonly IAuthRepository _authRepository;

    public AuthService(IAuthRepository authRepository)
    {
        _authRepository = authRepository;
    }

    public async Task SignUp(UserCredentialsModel userCredentialsModel)
    {
        await _authRepository.SignUp(userCredentialsModel);
    }

    public async Task<UserCredentialsModel?> Login(UserCredentialsRequestModel userCredentialsRequestModel)
    {
        return await _authRepository.Login(userCredentialsRequestModel);
    }

    public async Task<UserCredentialsModel?> Verify(string id)
    {
        return await _authRepository.Verify(id);
    }
}