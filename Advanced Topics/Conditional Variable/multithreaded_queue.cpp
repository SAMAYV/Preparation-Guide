#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

queue<int> q;
mutex queueMutex;
condition_variable queueCondVar;

void provider(int val)
{
    // push different vals
    for(int i = 0; i < 6; ++i) 
    {
        {
            lock_guard<mutex> lg(queueMutex);
            q.push(val+i);
        }
        // release lock
        queueCondVar.notify_one();
        this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}
void consumer(int num) 
{
    // pop vals if available (num identifies the consumer)
    while(true) 
    {
        int val;
        {
            unique_lock<mutex> ul(queueMutex);
            queueCondVar.wait(ul, []{ 
                return !q.empty(); 
            });
            val = q.front();
            q.pop();
        }
        // release lock
        cout << "consumer " << num << ": " << val << endl;
    }
}
int main() 
{
    // start three providers for values 100+, 300+, 500+
    auto p1 = async(launch::async, provider, 100);
    auto p2 = async(launch::async, provider, 300);
    auto p3 = async(launch::async, provider, 500);

    // start two consumers printing the vals
    auto c1 = async(launch::async, consumer, 1);
    auto c2 = async(launch::async, consumer, 2);
    return 0;
}