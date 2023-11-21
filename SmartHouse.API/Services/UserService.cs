
using SmartHouse.API.Enitity;

namespace SmartHouse.API.Services;

public class UserService : IUserRepository
{
    public void AddDevice(Device device)
    {

    }

    public void Create(User item)
    {

    }

    public void Delete(string id)
    {

    }

    public void Dispose()
    {

    }

    public User GetItem(string id)
    {
        return new User();
    }

    public IEnumerable<User> GetList()
    {
        return new List<User>();
    }

    public List<Device> GetUserDevices()
    {
        return new List<Device>();
    }

    public void RemoveDevice(Device device)
    {

    }

    public void Save()
    {

    }

    public void Update(User item)
    {

    }
}
