#include <iostream>
#include <thread>
class ThreadRAII
{
    std::thread & m_thread;
    public:
        ThreadRAII(std::thread  & threadObj) : m_thread(threadObj)
        {

        }
        ~ThreadRAII()
        {
            // Check if thread is joinable then detach the thread
            if(m_thread.joinable())
            {
                m_thread.detach();
            }
        }
};

void thread_function()
{
    for(int i = 0; i < 5; i++)
    {
        std::cout<<"thread_function Executing"<<std::endl;
    }
}

int main()  
{
    std::thread threadObj(thread_function);

    // If we comment this Line, then program will crash
    ThreadRAII wrapperObj(threadObj);
    return 0;
}

// We should not forget call either join() or detach() in case of exceptions, otherwise it can terminate the program. To prevents with we should use RESOURCE ACQUISITION IS INITIALIZATION (RAII) i.e.
// To address this problem, we can leverage the RAII (Resource Acquisition Is Initialization) principle. By creating a wrapper around the std::thread class, we can ensure safe thread management. When the wrapper’s destructor is invoked, it will automatically check if the internal thread object is joinable. If it’s joinable, the wrapper will then invoke the detach() method. This approach provides a safeguard: even if the developer forgets to call join() or detach(), the application will not terminate unexpectedly.