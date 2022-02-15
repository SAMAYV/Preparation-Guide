#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;
   
bool readyFlag;
mutex readyFlagMutex;

void thread1() {
    // do something thread2 needs as preparation
    lock_guard<mutex> lg(readyFlagMutex); 
    readyFlag = true;
}
void thread2() {
    // wait until readyFlag is true (thread1 is done) 
    {
        unique_lock<mutex> ul(readyFlagMutex);
        while(!readyFlag) {
            ul.unlock();
            this_thread::yield(); // hint to reschedule to the next thread 
            this_thread::sleep_for(std::chrono::milliseconds(100)); 
            ul.lock();
        }
    } // release lock

    // do whatever shall happen after thread1 has prepared things
}