#include <iostream>
#include <thread>

void thread_function()
{
    std::cout<<"Inside Thread :: ID  = "<<std::this_thread::get_id()<<std::endl;    
}

int main()  
{
    // Create two thread objects
    std::thread threadObj1(thread_function);
    std::thread threadObj2(thread_function);

    // Compare the Tead Id of two threads
    if(threadObj1.get_id() != threadObj2.get_id())
    {
        std::cout<<"Both Threads have different IDs"<<std::endl;
    }


    std::cout<<"From Main Thread :: ID of Thread 1 = "<<threadObj1.get_id()<<std::endl;    
    std::cout<<"From Main Thread :: ID of Thread 2 = "<<threadObj2.get_id()<<std::endl;    

    // Wait for both the thread to finish
    threadObj1.join();    
    threadObj2.join();    
    return 0;
}