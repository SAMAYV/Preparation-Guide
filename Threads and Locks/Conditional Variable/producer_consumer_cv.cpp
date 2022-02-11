#include <iostream>           
#include <thread>             
#include <mutex>              
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;

int meal = 0;

/* Consumer */
void waiter(int ordernumber)
{
    unique_lock<mutex> lck(mtx);
    while(meal == 0){
        cv.wait(lck);
    } 
    cout << "Order: ";
    cout << ordernumber + 1 << " being taken care of with ";
    cout << meal - 1 << " meals also ready." << endl;
    meal--;
}

/* Producer */
void makeMeal(int ordernumber)
{
    unique_lock<mutex> lck(mtx);
    meal++;
    cv.notify_one();
}

int main()
{
    thread chefs[10];
    thread waiters[10];

    /* Initialize customers and cheifs */
    for(int order = 0; order < 10; order++){
        chefs[order] = thread(makeMeal, order);
        waiters[order] = thread(waiter, order);
    }

    /* Join the threads to the main threads */
    for(int order = 0; order < 10; order++) {
        waiters[order].join();   
        chefs[order].join(); 
    }
    return 0;
}

/* In the example above there clearly is a race, however this is not a race condition. 
In this case there are no errors due to the threads running out of order and thus there is no issue. 
All we are trying to achieve is getting the orders out as quickly as they are produced, to maximize throughput (not priority). */