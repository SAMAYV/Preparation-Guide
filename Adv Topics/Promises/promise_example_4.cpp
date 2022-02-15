#include <bits/stdc++.h>
#include <thread>
#include <future>
using namespace std;

void initializer(promise<int>&& promObj, int x)
{
    cout << "Inside Thread with ID: " << this_thread::get_id() << endl;     
    promObj.set_value(2*x);
}
int main()
{
    vector<thread> threads;
    vector<future<int>> futures;
    for(int i = 0; i < 2; i++){
        promise<int> promiseObj;
        futures.push_back(promiseObj.get_future());
        threads.push_back(thread(initializer, move(promiseObj), i + rand() % 6));
    }
    for(int i = 0; i < 2; i++){
        threads[i].join();
    }
    for(int i = 0; i < 2; i++){
        cout << futures[i].get() << " ";
    }
    return 0;
}