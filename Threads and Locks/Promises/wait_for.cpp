#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
using namespace std;

int main()
{
    future<int> future = async(launch::async, [](){ 
        this_thread::sleep_for(chrono::seconds(3));
        return 8; 
    });

    cout << "waiting ...\n";
    future_status status;
    do {
        status = future.wait_for(chrono::seconds(1));
        if(status == future_status::deferred) {
            cout << "deferred\n";
        } 
        else if (status == future_status::timeout) {
            cout << "timeout\n";
        } 
        else if (status == future_status::ready) {
            cout << "ready!\n";
        }
    } 
    while(status != future_status::ready);

    cout << "result is " << future.get() << '\n';
    return 0;
}