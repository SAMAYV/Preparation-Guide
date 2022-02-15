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
/* If std::promise object is destroyed before setting the value the calling get() function on associated std::future object 
will throw exception. A part from this, if you want your thread to return multiple values at different point of time then just 
pass multiple std::promise objects in thread  and fetch multiple return values from thier associated multiple std::future objects. */