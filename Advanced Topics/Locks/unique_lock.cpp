#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

int main()
{
    int counter = 0;
    mutex counter_mutex;
    vector<thread> threads;

    auto worker_task = [&](int id) {
        unique_lock<mutex> lock(counter_mutex);
        ++counter;
        cout << id << ", initial counter: " << counter << '\n';
        lock.unlock();

        // don't hold the lock while we simulate an expensive operation
        this_thread::sleep_for(std::chrono::seconds(1));

        lock.lock();
        ++counter;
        cout << id << ", final counter: " << counter << '\n';
    };

    for(int i = 0; i < 10; ++i) threads.emplace_back(worker_task, i);

    for(auto &thread : threads) thread.join();
    
    return 0;
}

/* std::lock_guard keeps its associated mutex locked during the entire life time by acquiring the lock on construction and 
releasing the lock on destruction.

std::unique_lock is a lot more flexible when dealing with mutex locks. It has the same interface as std::lock_guard but provide 
extra abilities to program explicitly when and how to lock or unlock its mutex. 
Thus, this lock obj may or may not have a mutex locked (also known as owning a mutex). */