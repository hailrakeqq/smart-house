using SmartHouse.API.Enitity;
using SmartHouse.API.Repository;

public interface IUserRepository : IRepository<User>
{
    void AddDevice(Device device);
    void RemoveDevice(Device device);
    List<Device> GetUserDevices();
}