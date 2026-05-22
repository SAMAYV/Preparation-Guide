#include <iostream>
#include <mutex>
#include <string>

using namespace std;

// The Database class defines the `getInstance` method that lets
// clients access the same instance of a database connection throughout the program.
class Database {
private:
    // The field for storing the singleton instance should be declared static and volatile.
    // volatile ensures that the variable is always read from main memory
    // and not from CPU cache, preventing issues in multi-threaded environments.
    static volatile Database* instance;
    
    // Mutex for thread-safe initialization
    static mutex mutex_;
    
    // The singleton's constructor should always be private to
    // prevent direct construction calls with the `new` operator.
    Database() {
        // Some initialization code, such as the actual connection to a database server.
        cout << "Database instance created" << endl;
    }
    
    // Delete copy constructor and assignment operator
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

public:
    // The static method that controls access to the singleton
    // instance using Double-Checked Locking Pattern (DCLP).
    static Database* getInstance() {
        // First check (without locking) - for performance
        if (instance == nullptr) {
            // Acquire lock
            lock_guard<mutex> lock(mutex_);
            
            // Second check (with locking) - for thread safety
            // Ensure that the instance hasn't yet been initialized by another thread while this one
            // has been waiting for the lock's release.
            if (instance == nullptr) {
                instance = new Database();
            }
        }
        return const_cast<Database*>(instance);
    }
    
    // Finally, any singleton should define some business logic
    // which can be executed on its instance.
    void query(const string& sql) {
        // For instance, all database queries of an app go
        // through this method. Therefore, you can place
        // throttling or caching logic here.
        cout << "Executing query: " << sql << endl;
    }
};

// Initialize static members
volatile Database* Database::instance = nullptr;
mutex Database::mutex_;

class Application {
public:
    void main() {
        Database* foo = Database::getInstance();
        foo->query("SELECT * FROM users");
        
        Database* bar = Database::getInstance();
        bar->query("SELECT * FROM orders");
        
        // The variable `bar` will contain the same object as the variable `foo`.
        cout << "foo and bar are same instance: " << (foo == bar ? "true" : "false") << endl;
    }
};

int main() {
    Application app;
    app.main();
    return 0;
}

