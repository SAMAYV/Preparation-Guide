#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;

class FizzBuzz {
public:
    mutex m;
    int st, ed;
    FizzBuzz(int st, int ed) : st(st), ed(ed) {}
    
    void Fizz() 
    {
        while(st <= ed)
        {
            unique_lock<mutex> ul(m, adopt_lock);
            if(st % 3 == 0 && st % 5 != 0){
                cout << "Count: " << st << " Fizz\n";
                st += 1;
            }
            ul.unlock();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    void Buzz() 
    {
        while(st <= ed)
        {
            unique_lock<mutex> ul(m, adopt_lock);
            if(st % 3 != 0 && st % 5 == 0){
                cout << "Count: " << st << " Buzz\n";
                st += 1;
            }
            ul.unlock();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    void Fizz_Buzz() 
    {
        while(st <= ed)
        {
            unique_lock<mutex> ul(m, adopt_lock);
            if(st % 3 == 0 && st % 5 == 0){
                st += 1;
                cout << "Count: " << st - 1 << " FizzBuzz\n";
            }
            ul.unlock();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    void Number() 
    {
        while(st <= ed)
        {
            unique_lock<mutex> ul(m, adopt_lock);
            if(st % 3 != 0 && st % 5 != 0){
                st += 1;
                cout << "Count: " << st - 1 << " None\n";
            }
            ul.unlock();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
};

int main()
{
    system_clock::time_point start = system_clock::now();

    FizzBuzz f(1, 100);
    thread th1(&FizzBuzz::Fizz, &f);
    thread th2(&FizzBuzz::Buzz, &f);
    thread th3(&FizzBuzz::Fizz_Buzz, &f);
    thread th4(&FizzBuzz::Number, &f);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    
    auto end = system_clock::now();
    
    auto diff = duration_cast<chrono::seconds>(end - start).count();
    
    cout << "Total Time Taken = " << diff << " Seconds" << endl;

    return 0;
}