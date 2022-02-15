#include <iostream>
#include <string>
using namespace std;

class User
{
    int id;
    string name;
public:
    User(int userId, string userName) : id(userId), name(userName) {}
    
    // Copy Constructor is deleted
    User(const User& obj) = delete;
    
    // Assignment operator is deleted
    User& operator=(const User& obj) = delete;
    
    void display() {
        cout << id << " ::: " << name << endl;
    }
    
    // Deleting a constructor that accepts a double as ID to prevent narrowing conversion
    User(double userId, string userName) = delete;
    
    // Deleting a constructor that accepts a double as ID to prevent invalid type conversion
    User(char userId, string userName) = delete;
    
    // Delete the new function to prevent object creation on heap
    void* operator new(size_t) = delete;
};
int main()
{
    User userObj(3, "John");
    // Can not copy User object as copy constructor is deleted
    // User obj = userObj;
    
    // Creating User objects with double or char as ID will cause compile time error
    // User obj4(5.5, "Riti");
    // User obj5('a', "Riti");

    // Can not create object on heap as new operater is deleted
    // User* ptr = new User(1, "Riti");
    return 0;
}