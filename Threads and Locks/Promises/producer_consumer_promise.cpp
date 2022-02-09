#include <bits/stdc++.h>       
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
using namespace std;

void produce_item(promise<string>& prom)
{
    cout << "Producer is producing item\n";
    
    this_thread::sleep_for(chrono::milliseconds(1000));
    
    prom.set_value("Producer produced item");
}
void consume_item(future<string>& fut, int id)
{
    cout << "Consumer " << id << " is consuming item" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << fut.get() << endl;
}

int main()
{
    promise<string> prom;
    future<string> future = prom.get_future();
    
    thread producer(produce_item, ref(prom));
    thread consumer(consume_item, ref(future), 0);
    
    producer.join();
    consumer.join();
    return 0;
}