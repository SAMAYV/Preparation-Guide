#include <bits/stdc++.h>       
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
using namespace std;

mutex locks;

void produce_item(promise<string>& prom)
{
    cout << "Producer is producing item\n";
    
    this_thread::sleep_for(chrono::milliseconds(1000));
    
    prom.set_value("Item consumed");
}
void consume_item(shared_future<string>& fut)
{
    lock_guard<mutex> coutGuard(locks);

    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << fut.get() << " by " << this_thread::get_id() << endl;
}
int main()
{
    promise<string> prom;
    shared_future<string> future = prom.get_future();
    
    thread producer(produce_item, ref(prom));

    vector<thread> threads;
    for(int i = 0; i < 5; i++){
        threads.push_back(thread(consume_item, ref(future)));
    }
    
    producer.join();
    for(int i = 0; i < 5; i++){
        threads.at(i).join();
    }
    return 0;
}