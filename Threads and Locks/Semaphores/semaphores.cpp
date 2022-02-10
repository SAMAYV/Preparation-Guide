#include <bits/stdc++.h>
#include <mutex>
#include <condition_variable>
using namespace std;
        
class Semaphore 
{
private:
    mutex mtx;
    condition_variable cv;
    int count;
public:
    Semaphore (int count_ = 0) : count(count_) {}
    inline void notify(int tid)
    {
        unique_lock<mutex> lock(mtx);
        count++;
        cout << "thread " << tid << " notify" << endl;
        cv.notify_one();        // notify the waiting thread
    }
    inline void wait(int tid)
    {
        unique_lock<mutex> lock(mtx);
        while(count == 0){
            cout << "thread " << tid << " wait" << endl;
            cv.wait(lock);      // wait on the mutex until notify is called
        }
        cout << "thread " << tid << " run" << endl;
        count--;
    }
};

int main()
{
    Semaphore sem(1);
    thread s1([&]() {
        this_thread::sleep_for(std::chrono::seconds(5));
        sem.wait(1);           
    });
    thread s2([&]() {
        sem.wait(2);
    });
    thread s3([&]() {
        while(true) {
            this_thread::sleep_for(std::chrono::milliseconds(600));
            sem.wait(3);
        }
    });
    thread s4([&]() {
        while(true) {
            this_thread::sleep_for(std::chrono::seconds(5));
            sem.notify(4);
        }
    });
    thread s5([&]() {
        this_thread::sleep_for(std::chrono::seconds(5));
        sem.notify(5);
    });
    s1.join();
    s2.join();
    s3.join();
    s4.join();
    s5.join();
    return 0;
}

/* The following function adds four threads. Three threads compete for the semaphore, 
which is set to a count of one. A slower thread calls notify_one(), allowing one of the waiting threads to proceed.

The result is that s1 immediately starts spinning, causing the Semaphore's usage count to remain below 1. 
The other threads wait in turn on the condition variable until notify() is called. */