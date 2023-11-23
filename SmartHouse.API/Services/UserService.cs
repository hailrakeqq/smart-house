
using Microsoft.EntityFrameworkCore;
using SmartHouse.API.Enitity;
using SmartHouse.API.Repository;

namespace SmartHouse.API.Services;

public class UserService : IUserRepository
{

    private readonly ApplicationDbContext _context;

    public UserService(ApplicationDbContext context)
    {
        _context = context;
    }

    public void AddDevice(Device device)
    {

    }

    public List<User> GetList()
    {
        return _context.users.ToList();
    }

    public async Task<User> GetItemById(string id)
    {
        return await _context.users.FirstOrDefaultAsync(u => u.Id == id);
    }

    public async Task<User> GetUserByEmail(string email)
    {
        return await _context.users.FirstOrDefaultAsync(u => u.Email == email);
    }

    public async Task<User> ValidateUserLoginModel(UserLoginModel model)
    {
        var currentUser = await _context.users.FirstOrDefaultAsync(u =>
            u.Email == model.Email &&
            u.Password == Tool.GenerateHash(model.Password));

        return currentUser;
    }

    public async Task Create(User item)
    {
        await _context.AddAsync(item);
    }

    public async Task Update(User item)
    {
        await Delete(item.Id);
        await Create(item);
        Save();
    }

    public async Task Delete(string id)
    {
        var user = await GetItemById(id);
        if (user != null)
        {
            _context.users.Remove(user);
            Save();
        }
    }

    public void Save()
    {
        _context.SaveChanges();
    }

    public void Dispose()
    {
    }

    public void RemoveDevice(Device device)
    {
        throw new NotImplementedException();
    }

    public List<Device> GetUserDevices()
    {
        throw new NotImplementedException();
    }


    public User GetItem(string id)
    {
        throw new NotImplementedException();
    }
}
