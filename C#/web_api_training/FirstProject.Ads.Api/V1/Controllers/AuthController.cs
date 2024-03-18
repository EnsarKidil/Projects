using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Helpers;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.Services;
using FirstProject.Ads.Api.V1.Models.RequestModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;

namespace FirstProject.Ads.Api.V1.Controllers;


[ApiController]
[Route("[controller]")]
public class AuthController : ControllerBase
{
    private readonly ILogger<MerchantController> _logger;
    private readonly IAuthService _authService;

    public AuthController(ILogger<MerchantController> logger, IAuthService authService)
    {
        _logger = logger;
        _authService = authService;
    }

    [HttpPost("Login")]
    public async Task<IActionResult> Login(UserCredentialsRequestModel userCredentialsRequestModel)
    {
        var user = await _authService.Login(userCredentialsRequestModel);
        if (user == null)
        {
            throw new InvalidCredentials("Invalid Credentials");
        }
        //generating token
        var tokenHandler = new JwtSecurityTokenHandler();
        var key = Encoding.ASCII.GetBytes("1bf13957-0771-47fa-a3e7-1d0480bd27a3"); // Özel anahtar
        var tokenDescriptor = new SecurityTokenDescriptor
        {
            Subject = new ClaimsIdentity(new Claim[]
            {
                new(ClaimTypes.NameIdentifier, user.Id)
            }),
            Expires = DateTime.UtcNow.AddHours(1), // Token'in geçerlilik süresi
            SigningCredentials = new SigningCredentials(new SymmetricSecurityKey(key), SecurityAlgorithms.HmacSha256Signature),
            Issuer = "localhost:5030",
            Audience = "localhost:5030"
        };
        var token = tokenHandler.CreateToken(tokenDescriptor);
        var tokenString = tokenHandler.WriteToken(token);
        return Ok(new { Token = tokenString });
    }
    
    [HttpPost("SignUp")]
    public async Task<IActionResult> SignUp([FromBody] UserCredentialsRequestModel userCredentialsRequestModel)
    {
        var userCredentialsModel = UserCredentialsModelHelper.FromUserCredentialsRequestModelToDbModel(userCredentialsRequestModel);
        await _authService.SignUp(userCredentialsModel);
        return Created(nameof(SignUp), $"Created user with username: {userCredentialsModel.Username}. Please login now");
    }

    [HttpPost("Verify")]
    public async Task<IActionResult> Verify([FromBody] string token)
    {
        var tokenHandler = new JwtSecurityTokenHandler();
        var jwtToken = tokenHandler.ReadJwtToken(token);
        var idClaim = jwtToken.Claims.FirstOrDefault(c => c.Type == ClaimTypes.NameIdentifier);
        var userId = idClaim?.Value;
        if (string.IsNullOrWhiteSpace(userId))
        {
            throw new BadRequest("Not Valid");
        }
        var user = await _authService.Verify(userId);
        if (user == null)
        {
            throw new BadRequest("Not Valid");
        }

        return Ok(user.Id);
    }
}