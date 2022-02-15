#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std::chrono;
using namespace std;

int doSomething(char c) {
    //...
    return c;
}
int func1() {
    return doSomething('.');
}
int func2() {
    return doSomething('+');
}
int main() 
{
    // start func1 asynchronously (now or later or never)
    future<int> result1(async(func1));

    // call func2 synchronously (here and now)
    int result2 = func2();

    // print result (wait for func1() to finish and add its result to result2
    int result = result1.get() + result2;
    cout << result << endl;
    return 0;
}

/* With the call of get(), one of the three things might happen:

if func1() was started with async() in a separate thread and has already finished, we immediately get its result;
if func1() was started but has not finished yet, get() blocks and waits for its end and yields the result;
if func1() was not started yet, it will be forced to start now and, like a synchronous func call, get() will block until it yields the result.

Without calling get(), there is no guarantee that func1() will ever be called. We have to ensure that we ask for the result of a 
functionality started with async() no earlier than necessary. 

To have the best effect, in general, we should maximize the distance between calling async() and calling get, i.e., call early and return late.
*/