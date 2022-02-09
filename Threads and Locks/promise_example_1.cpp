#include <iostream>
#include <thread>
#include <future>
using namespace std;

void initializer(promise<int>* promObj, int x)
{
    cout << "Inside Thread" << endl;     
    promObj->set_value(2*x);
}
int main()
{
    promise<int> promiseObj;
    future<int> futureObj = promiseObj.get_future();
    thread th(initializer, &promiseObj, 20);
    cout << futureObj.get() << endl;
    th.join();
    return 0;
}