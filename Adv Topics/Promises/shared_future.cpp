#include <bits/stdc++.h>
#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <utility>
using namespace std;

mutex coutMutex;

struct Div 
{
    void operator()(promise<int>&& intPromise, int a, int b)
    {
        try {
            if(b == 0) throw runtime_error("illegal division by zero");
            intPromise.set_value(a / b);
        }
        catch(...){
            intPromise.set_exception(std::current_exception());
        }
    }
};

struct Requestor 
{
    void operator()(shared_future<int>& shaFut)
    {
        lock_guard<mutex> coutGuard(coutMutex);

        // get the thread id
        cout << "Thread Id(" << this_thread::get_id() << "): ";

        // get the result
        try {
            cout << "20/10 = " << shaFut.get() << endl;
        }
        catch(runtime_error& e){
            cout << e.what() << endl;
        }
    }
};

int main()
{
    // define the promises
    promise<int> divPromise;

    // get the futures
    shared_future<int> divResult = divPromise.get_future();

    // calculate the result in a separat thread
    Div div;
    thread divThread(div, move(divPromise), 20, 10);

    Requestor req;
    vector<thread> threads;
    for(int i = 0; i < 5; i++){
        threads.push_back(thread(req, ref(divResult)));
    }

    divThread.join();
    for(int i = 0; i < 5; i++){
        threads.at(i).join();
    }
    return 0;
}