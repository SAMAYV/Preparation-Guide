#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std::chrono;
using namespace std;

void print_ten(char c, int ms) {
    for(int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(ms));
        cout << c;
    }
}
int main()
{
    cout << "with launch::async: ";
    future<void> foo = async(launch::async, print_ten, '*', 100);
    future<void> bar = async(launch::async, print_ten, '@', 200);
    
    // async "get" (wait for foo and bar to be ready):
    foo.get(); 
    bar.get();
    cout << "\n";

    cout << "with launch::deferred: ";
    foo = async(launch::deferred, print_ten, '*', 100);
    bar = async(launch::deferred, print_ten, '@', 200);
    
    // deferred "get" (perform the actual calls):
    foo.get(); 
    bar.get();
    cout << '\n';

    return 0;
}
// Automatic: launch::async|launch::deferred, the func chooses the policy auto (at some point).