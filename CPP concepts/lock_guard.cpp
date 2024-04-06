class Wallet
{
    int mMoney;
    std::mutex mutex;
public:
    Wallet() :mMoney(0){}
    int getMoney()   {     return mMoney; }
    void addMoney(int money)
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        // In constructor it locks the mutex

        for(int i = 0; i < money; ++i)
        {
            // If some exception occurs at this
            // poin then destructor of lockGuard
            // will be called due to stack unwinding.
            //
            mMoney++;
        }
        // Once function exits, then destructor
        // of lockGuard Object will be called.
        // In destructor it unlocks the mutex.
    }
 };