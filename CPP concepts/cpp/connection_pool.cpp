#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
using namespace std;

/*
For interview questions about connection pools or thread pools where the scarce resource has state, 
use a blocking queue. "I'll maintain a BlockingQueue of available connections. Threads call take to 
acquire one and put to return it. The queue handles blocking and waking automatically." This shows you 
understand both the resource management and the concurrency coordination.

If an interviewer asks "Should we create connections upfront or lazily?", go with upfront unless they 
specifically say startup time matters. Say: "I'll create all connections in the constructor. It's simpler, 
avoids race conditions, and ensures predictable performance once the pool is running." Don't overcomplicate it.

This pattern appears when you have expensive, stateful objects that must be shared across threads.
*/

class ConnectionPool {
private:
    queue<Connection*> availableConnections;
    mutex mtx;
    condition_variable cv;
    chrono::milliseconds timeout;

    // RAII guard to ensure connection is always released
    class ConnectionGuard {
    private:
        ConnectionPool& pool;
        Connection* conn;
    public:
        ConnectionGuard(ConnectionPool& p) : pool(p), conn(pool.acquire()) {}
        ~ConnectionGuard() {
            if (conn) {
                pool.release(conn);
            }
        }
        Connection* get() const { return conn; }
        // Prevent copying
        ConnectionGuard(const ConnectionGuard&) = delete;
        ConnectionGuard& operator=(const ConnectionGuard&) = delete;
    };

public:
    ConnectionPool(int poolSize, chrono::milliseconds timeout) {
        for (int i = 0; i < poolSize; i++) {
            availableConnections.push(createNewConnection());
        }
        this->timeout = timeout;
    }

    Connection* acquire() {
        unique_lock<mutex> lock(mtx);
        if (!cv.wait_for(lock, timeout, [this] { return !availableConnections.empty(); })) {
            throw runtime_error("No connection available within timeout");
        }
        Connection* conn = availableConnections.front();
        availableConnections.pop();
        return conn;
    }

    void release(Connection* conn) {
        lock_guard<mutex> lock(mtx);
        availableConnections.push(conn);
        cv.notify_one();
    }

    // Method 1: Using RAII ConnectionGuard (Recommended)
    void executeQuery(const string& query) {
        ConnectionGuard guard(*this);  // Acquires connection
        Connection* conn = guard.get();
        conn->execute(query);
        // Connection automatically released when guard goes out of scope
        // This works even if execute() throws an exception!
    }

    // Method 3: Original approach with try-catch (Not recommended)
    void executeQueryOriginal(const string& query) {
        Connection* conn = acquire();
        try {
            conn->execute(query);
            release(conn);
        } catch (...) {
            release(conn);  // Code duplication
            throw;
        }
    }
};

/*
Database Connection Pool: Your service handles 1,000 requests per second but only has 10 database connections. 
Creating a new connection for every request would overwhelm the database. Use a BlockingQueue holding 10 connection objects. 
Threads take a connection, execute their query, and return it. If all connections are in use, requests wait. 
This reuses connections across thousands of requests while capping the load on the database.
*/