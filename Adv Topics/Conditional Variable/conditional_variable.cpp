#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

class Application
{
    mutex m_mutex;
    condition_variable m_condVar;
    bool m_bDataLoaded;
public:
    Application(){
        m_bDataLoaded = false;
    }
    void loadData()
    {
        this_thread::sleep_for(chrono::milliseconds(1000));     // Make This Thread sleep for 1 Second
        cout << "Loading Data from XML" << endl;
   
        lock_guard<std::mutex> guard(m_mutex);                  // Lock The Data structure
        m_bDataLoaded = true;                                   // Set the flag to true, means data is loaded 
        m_condVar.notify_one();                                 // Notify the condition variable
    }
    bool isDataLoaded()
    {
        return m_bDataLoaded;
    }
    void mainTask()
    {
        cout << "Do Some Handshaking" << endl;
        
        // Acquire the lock
        unique_lock<std::mutex> mlock(m_mutex);
    
        // Start waiting for the Condition Variable to get signaled. Wait() will internally release the lock and make the thread to block
        // As soon as condition variable get signaled, resume the thread and again acquire the lock. Then check if condition is met or not
        // If condition is met then continue else again go in wait.
        m_condVar.wait(mlock, bind(&Application::isDataLoaded, this));
        cout << "Do Processing On loaded Data" << endl;
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

