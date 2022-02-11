#include <atomic> 
#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

atomic<bool> readyFlag(false);

void thread1() {
    // do something thread2 needs as preparation ...
    readyFlag.store(true);
}
void thread2() {
    // wait until readyFlag is true (thread1 is done) 
    while(!readyFlag.load()){
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // do whatever shall happen after thread1 has prepared things
}