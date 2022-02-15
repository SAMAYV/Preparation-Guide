#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class Wallet
{
    int mMoney;
    mutex mutex;
public:
    Wallet() : mMoney(0){}
    int getMoney(){
        return mMoney; 
    }
    void addMoney(int money){
        mutex.lock();
        for(int i = 0; i < money; ++i){
            mMoney++;
        }
        mutex.unlock();
    }
};
int testMultithreadedWallet()
{
    Wallet walletObject;
    vector<thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(thread(&Wallet::addMoney, &walletObject, 10000));
    }
    for(int i = 0; i < threads.size() ; i++){
        threads.at(i).join();
    }
    return walletObject.getMoney();
}
int main()
{
    int val = 0;
    for(int k = 0; k < 100; k++)
    {
        if((val = testMultithreadedWallet()) != 50000)
        {
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
    }
    return 0;
}
/* But what if we forgot to unlock the mutex at the end of function. 
In such scenario, one thread will exit without releasing the lock and other threads will remain in waiting.
This kind of scenario can happen in case some exception came after locking the mutex. To avoid such scenarios we should use std::lock_guard. 
std::unique_lock and std::lock_guard are used to manage locking in exception-safe manner.
*/