#include <iostream>
#include <thread>
#include <future>

void initiazer(std::promise<int> * promObj)
{
    std::cout<<"Inside Thread"<<std::endl;     promObj->set_value(35);
}

int main()
{
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread th(initiazer, &promiseObj);
    std::cout<<futureObj.get()<<std::endl;
    th.join();
    return 0;
}