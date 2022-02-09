#include <iostream>       
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
using namespace std;

void print_int(future<int>& fut){
    int x = fut.get();
    cout << "Value: " << x << '\n';
}
int main()
{
    promise<int> prom;                      // create promise
    future<int> fut = prom.get_future();    // engagement with future
    thread th1(print_int, ref(fut));        // send future to new thread
    prom.set_value(10);                     // fulfill promise
    th1.join();                             // (synchronizes with getting the future)
    return 0;
}