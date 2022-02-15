#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

bool readyFlag;         // a flag signaling the cond is indeed satisfied
mutex readyMutex;       // a mutex
condition_variable readyCondVar;   // a cond var

// locks the mutex, updates the cond, unlocks the mutex and notifies the cond var
void thread1() 
{
    // do sth thread2 needs as preparation
    cout << "<return>" << endl;
    cin.get();
    
    // signal that thread1 has prepared a cond
    {
        lock_guard<mutex> lg(readyMutex);
        readyFlag = true;
    }
    // release lock
    readyCondVar.notify_one();
}

void thread2() 
{
    // wait until thread1 is ready (readyFlag is true)
    {
        unique_lock<mutex> ul(readyMutex);
        readyCondVar.wait(ul, []{ 
            return readyFlag; 
        });
        // same as while (!readyFlag) { readyCondVar.wait(ul); }
    }
    // release lock
    
    // do whatever shall happen after thread1 has prepared things
    cout << "done" << endl;
}

int main() 
{
    auto f1 = async(launch::async, thread1);
    auto f2 = async(launch::async, thread2);
    return 0;
}

/* The waiting thread locks the mutex with a unique_lock, waits for the notification while checking the condition and releases the lock:
Here, a wait() member for cond vars is used as follow: pass the lock ul for the mutex readyMutex as 1st argument and a lambda as 
callable object double checking the cond as second argument. The effect is that wait() internally calls a loop until the passed 
callable returns true. Thus, the code has the same effect as the following code. */