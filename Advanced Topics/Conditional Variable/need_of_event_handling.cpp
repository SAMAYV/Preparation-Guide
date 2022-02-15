#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class Application
{
    mutex m_mutex;
    bool m_bDataLoaded;
public:
    Application(){
        m_bDataLoaded = false;
    }
    void loadData()
    {
        this_thread::sleep_for(chrono::milliseconds(1000)); // Make This Thread sleep for 1 Second
        cout << "Loading Data from XML\n";
        lock_guard<mutex> guard(m_mutex);   // Lock The Data structure
        m_bDataLoaded = true;               // Set the flag to true, means data is loaded
    }
    void mainTask()
    {
        cout << "Do Some Handshaking\n";
        m_mutex.lock();                 // Acquire the Lock
        while(m_bDataLoaded != true)    // Check if flag is set to true or not
        {
            m_mutex.unlock();           // Release the lock
            this_thread::sleep_for(std::chrono::milliseconds(100));     // sleep for 100 milli seconds
            m_mutex.lock();             // Acquire the lock
        }
        m_mutex.unlock();               // Release the lock
        cout << "Do Processing On loaded Data\n";     // Doc processing on loaded Data
    }
};
int main()
{
    Application app;
    thread thread_1(&Application::mainTask, &app);
    thread thread_2(&Application::loadData, &app);
    thread_2.join();
    thread_1.join();
    return 0;
}
/* Make a Boolean global variable with default value false. Set its value to true in Thread 2 and Thread 1 will keep on checking 
its value in loop and as soon as it becomes true Thread 1 will continue with processing of data.  
But as it’s a global variable shared by both of the Threads it needs synchronization with mutex. */

/* Thread will keep on acquiring the lock and release it just to check the value, therefore it will consume CPU cycles and will also make 
Thread 1 slow, because it needs to acquire same lock to update the bool flag.

So obviously we need a better mechanism to achieve this, like if somehow Thread 1 could just block by waiting for an Event to get signaled 
and another Thread could signal that Event and make Thread 1 continue. It would have save many CPU cycles and gave better performance. */