#include <bits/stdc++.h>       
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
using namespace std;

int main()
{
    // instantiate a promise object to share an object of string type
    auto prom = std::promise<std::string>();
    
    // a sample producer thread which sets the shared object via set_value()
    auto producer = std::thread([&]{
        prom.set_value("Hello World");
    });
    
    // associate the shared object with a future that can retrieve a value from some provider object,
    // in this case, a promise
    auto future = prom.get_future();
    
    // retrieve the shared object from the future
    auto consumer = std::thread([&]{
        std::cout << future.get();
    });
    
    // join threads
    producer.join();
    consumer.join();
    return 0;
}