FROM mcr.microsoft.com/dotnet/sdk:8.0 AS dotnet-build
WORKDIR /src
COPY . /src
RUN dotnet restore "SmartHouse.API.csproj"
RUN dotnet build "SmartHouse.API.csproj" -c Release -o /app/build

FROM dotnet-build AS dotnet-publish
RUN dotnet publish "SmartHouse.API.csproj" -c Release -o /app/publish

FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS final
WORKDIR /app
COPY --from=dotnet-publish /app/publish .

ENTRYPOINT ["dotnet", "SmartHouse.API.dll"]