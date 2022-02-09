#include <iostream>
#include <thread>
using namespace std;

class ThreadRAII
{
    thread &m_thread;
    public:
    ThreadRAII(thread& threadObj) : m_thread(threadObj)
    {
            
    }
    ~ThreadRAII()
    {
        // Check if thread is joinable then detach the thread
        if(m_thread.joinable()){
            m_thread.join();
        }
    }
};
void thread_function()
{
    for(int i = 0; i < 10000; i++);
    cout << "Thread function Executing\n";
}
int main()  
{
    thread threadObj(thread_function);
    
    // If we comment this Line, then program will crash
    ThreadRAII wrapperObj(threadObj);
    return 0;
}