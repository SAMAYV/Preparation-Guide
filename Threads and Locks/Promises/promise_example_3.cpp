#include <iostream>
#include <thread>
#include <future>
using namespace std;

void initializer(promise<int>* promObj, promise<int>* promObj2, int x, int y)
{
    cout << "Inside Thread" << endl;     
    promObj->set_value(2*x);
    promObj2->set_value(3*y);
}
int main()
{
    promise<int> promiseObj;
    future<int> futureObj = promiseObj.get_future();

    promise<int> promiseObj2;
    future<int> futureObj2 = promiseObj2.get_future();

    thread th(initializer, &promiseObj, &promiseObj2, 20, 5);
    cout << futureObj.get() << endl;
    cout << futureObj2.get() << endl;

    th.join();
    return 0;
}