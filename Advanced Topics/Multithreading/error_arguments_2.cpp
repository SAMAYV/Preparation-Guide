#include <iostream>
#include <thread>
using namespace std;

void newThreadCallback(int* p)
{
    cout << "Inside Thread :  "" : p = " << p << endl;
    chrono::milliseconds dura(1000);
    this_thread::sleep_for(dura);
    *p = 19;
}
void startNewThread()
{
    int * p = new int();
    *p = 10;
    cout << "Inside Main Thread :  "" : *p = " << *p << endl;
    thread t(newThreadCallback,p);
    t.detach();
    delete p;
    p = NULL;
}
int main()
{
    startNewThread();
    chrono::milliseconds dura(2000);
    this_thread::sleep_for(dura);
    return 0;
}

/* Similarly be careful while passing pointer to memory located on heap to thread. Because it might be possible that some thread 
deletes that memory before new thread tries to access it.
In such scenario accessing invalid address can cause unexpected behaviour. */