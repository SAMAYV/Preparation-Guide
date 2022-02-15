#include <bits/stdc++.h>
#include <thread>
using namespace std;

class Wallet
{
    int mMoney;
    public:
    Wallet() : mMoney(0){}
    int getMoney() { 
        return mMoney; 
    }
    void addMoney(int money)
    {
        for(int i = 0; i < money; ++i)
        {
            mMoney++;
        }
    }
};
int testMultithreadedWallet()
{
    Wallet walletObject;
    vector<thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(thread(&Wallet::addMoney, &walletObject, 10000));
    }
    for(int i = 0; i < threads.size() ; i++)
    {
       threads[i].join();
    }
    return walletObject.getMoney();
}
int main()
{
    int val = 0;
    for(int k = 0; k < 10; k++)
    {
        val = testMultithreadedWallet();
        chrono::milliseconds dura(1000);
        this_thread::sleep_for(dura);
        if(val != 50000)
        {
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
    }
    return 0;
}