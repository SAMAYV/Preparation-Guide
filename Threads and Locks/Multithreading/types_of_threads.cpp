#include <bits/stdc++.h>
#include <thread>
using namespace std;

class DisplayThread
{
    public:
    void operator()()     
    {
        cout << "Thread ID: " << this_thread::get_id() << "\n";
        for(int i = 0; i < 10000; i++);
        cout << "Display using function object\n";
    }
};
void thread_function()
{
    cout << "Thread ID: " << this_thread::get_id() << "\n";
    for(int i = 0; i < 10000; i++);
    cout << "Display using function pointers\n";
}
int main()  
{
    int n;
    cin >> n;
    vector<thread> threads;
    cout << "Entry of main function\n";
    for(int i = 0; i < n; i++){
        if(i % 3 == 0){
            threads.push_back(thread(thread_function));
        }
        else if(i % 3 == 1){
            threads.push_back(thread(DisplayThread()));
        }
        else {
            threads.push_back(thread([]{
                cout << "Thread ID: " << this_thread::get_id() << " ";
                for(int i = 0; i < 10000; i++);
                cout << "Display using lambda expressions\n";        
            }));
        }
    }
    for(int i = 0; i < n; i++){
        if(threads[i].joinable()){
            threads[i].join();
        }
    }
    for(int i = 0; i < n; i++){
        cout << "Thread ID of " << i << " from main function " << threads[i].get_id() << "\n";
    }
    cout << "Exit of main function\n";
    return 0;
}