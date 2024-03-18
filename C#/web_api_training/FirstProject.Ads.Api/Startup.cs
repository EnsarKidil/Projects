using System.Reflection;
using System.Text;
using FirstProject.Ads.Api.Configs;
using FirstProject.Ads.Api.Exceptions;
using FirstProject.Ads.Api.Middlewares;
using FirstProject.Ads.Api.Models;
using FirstProject.Ads.Api.Repositories;
using FirstProject.Ads.Api.Services;
using FirstProject.Ads.Api.V1.Models.ActionFilters;
using FirstProject.Ads.Api.V1.Models.Validators;
using FluentValidation;
using FluentValidation.AspNetCore;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using Microsoft.IdentityModel.Tokens;
using Microsoft.OpenApi.Models;

namespace FirstProject.Ads.Api;

public class Startup
{
    private readonly string _environment;
    private readonly MongoDbSettings _mongoDbSettings;
     
    public Startup(IWebHostEnvironment env)
    {
        Console.WriteLine($"Environment: {env.EnvironmentName}");
        var builder = new ConfigurationBuilder()
            .SetBasePath(env.ContentRootPath)
            .AddEnvironmentVariables()
            .AddJsonFile("configs/appsettings.json", optional: false, reloadOnChange: true)
            .AddJsonFile("configs/appsettings.Development.json", optional: true, reloadOnChange: true)
            .AddJsonFile("configs/MongoDbSettings.json");
            
        Configuration = builder.Build();
        var envVariables = Environment.GetEnvironmentVariables();
        if (string.IsNullOrWhiteSpace(envVariables["ASPNETCORE_ENVIRONMENT"]?.ToString())) 
            throw new ArgumentNullException("ASPNETCORE_ENVIRONMENT");
        _environment = envVariables["ASPNETCORE_ENVIRONMENT"].ToString();
    }

    public IConfiguration Configuration { get; }

    // This method gets called by the runtime. Use this method to add services to the container.
    
    [Obsolete("Obsolete")]
    public void ConfigureServices(IServiceCollection services)
    {
        services.AddCors(options => // Cross Origin Source
        {
            options.AddPolicy("AllowAll", builder =>
            {
                builder
                    .WithOrigins("*")
                    .AllowAnyMethod()
                    .AllowAnyHeader();
                //.AllowCredentials();
            });
        });
        services.Configure<MongoDbSettings>(Configuration.GetSection("MongoDbSettings"));
        services.AddAuthentication(options =>
            {
                options.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
                options.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
            })
            .AddJwtBearer(options =>
            {
                options.TokenValidationParameters = new TokenValidationParameters
                {
                    ValidateIssuer = true,
                    ValidateAudience = true,
                    ValidateLifetime = true,
                    ValidateIssuerSigningKey = true,
                    ValidIssuer = "localhost:5030",
                    ValidAudience = "localhost:5030",
                    IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes("1bf13957-0771-47fa-a3e7-1d0480bd27a3"))
                };
            });
        
        services.AddControllers()
            .AddFluentValidation(s =>
        {
            s.RegisterValidatorsFromAssemblyContaining<Startup>();
        });
        
        services.AddSwaggerGen(c =>
        {
            c.SwaggerDoc("v1", new OpenApiInfo { Title = "Ads.Merchant.API", Version = "v1" });
            var xmlFile = $"{Assembly.GetExecutingAssembly().GetName().Name}.xml";
            var xmlPath = Path.Combine(AppContext.BaseDirectory, xmlFile);
            c.IncludeXmlComments(xmlPath,true);
        });
        
        services.AddResponseCompression();
        services.AddSingleton<IMerchantService, MerchantService>();
        services.AddSingleton<IMerchantRepository,MerchantRepository>();
        services.AddSingleton<IAuthService, AuthService>();
        services.AddSingleton<IAuthRepository,AuthRepository>();
    }

    // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {
        app.UseMiddleware<ExceptionMiddleware>();
        app.UseMiddleware<LoggerMiddleware>();
        

        if (env.IsDevelopment())
        {
            app.UseSwagger();
            app.UseSwaggerUI();
            //app.UseDeveloperExceptionPage();
        }
        
        app.UseCors("AllowAll");
        app.UseResponseCompression();
        app.UseRouting();
        //app.UseMiddleware<AuthenticationMiddleware>();
        //app.UseAuthentication();
        //app.UseAuthorization();
        app.UseEndpoints(endpoints => { endpoints.MapControllers(); });
    }
}