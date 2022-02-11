#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class Wallet
{
    int mMoney;
    mutex mutex;
public:
    Wallet() : mMoney(0) {}
    int getMoney(){     
        return mMoney; 
    }
    void addMoney(int money){
        lock_guard<std::mutex> lockGuard(mutex);    // In constructor it locks the mutex
        for(int i = 0; i < money; i++)
        {
            // If some exception occurs at this point then destructor of lockGuard will be called due to stack unwinding.
            mMoney++;
        }
        // Once function exits, then destructor of lockGuard Object will be called. In destructor it unlocks the mutex.
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
        if((val = testMultithreadedWallet()) != 50000){
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
    }
    return 0;
}

/* To deal with exceptions (guarnatee exception safety), we shoud not lock and unlock by ourselves; 
instead, we should use the RAII principle (Resource Acquisition Is Initialization) */