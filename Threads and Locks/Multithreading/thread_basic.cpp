#include <iostream>
#include <string>
#include <thread>
using namespace std;

void f1(int n) {

}
void f2(int& n) {
}

int main() 
{
    int n = 0;
    thread t1;              // t1 is not a thread, it is an object
    thread t2(f1, n+1);     // pass by value
    thread t3(f2, std::ref(n));    // pass by ref
    thread t4(std::move(t3));  // t4 is now running f2(), t3 is no longer a thread
    t2.join();
    t4.join();
    return 0;
}