#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class DatabaseAccess 
{
private:
    recursive_mutex dbMutex;
    //state of database access
public:
    void createTable(...) {
        lock_guard<recursive_mutex> lg(dbMutex);
    }
    void insertData(...) {
        lock_guard<recursive_mutex> lg(dbMutex);
    }
    void createTableAndInsertData(...) {
        lock_guard<recursive_mutex> lg(dbMutex);
        createTable();   // OK: no deadlock
    }
};
/* A recursive mutex is a lockable object, just like mutex, but allows the same thread to acquire multi levels of ownership over the mutex obj. 
The lock is released when the last crspding unlock() is called. */

void doSomeOtherStuff(){

}
void couldNotGetTheLock(){

}
int main()
{
    mutex m;
    // try to acquire a lock and do other stuff if not psbl
    while (m.try_lock() == false) {
        doSomeOtherStuff();
    }

    // To wait only for a particular amount of time, we can use a timed mutex
    timed_mutex tm;
    if(tm.try_lock_for(chrono::seconds(1))) {
        lock_guard<timed_mutex> lg(tm, adopt_lock);
    } 
    else {
        couldNotGetTheLock();
    }
    return 0;
}