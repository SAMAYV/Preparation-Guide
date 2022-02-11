#include <bits/stdc++.h>
#include <thread>
#include <future>
#include <string>
using namespace std::chrono;
using namespace std;

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) 
{ 
    return pow(x, y); 
}
void task_lambda() 
{
    packaged_task<int(int,int)> task([](int a, int b) {
        return pow(a, b); 
    });
    future<int> result = task.get_future();
    task(2, 9);
    cout << "task_lambda:\t" << result.get() << '\n';
}
void task_bind() 
{
    packaged_task<int()> task(bind(f, 2, 11));
    future<int> result = task.get_future();
    task();
    cout << "task_bind:\t" << result.get() << '\n';
}
void task_thread() 
{
    packaged_task<int(int,int)> task(f);
    future<int> result = task.get_future();
    thread task_td(move(task), 2, 10);
    task_td.join();
    cout << "task_thread:\t" << result.get() << '\n';
}
int main() 
{
    task_lambda();
    task_bind();
    task_thread();
    return 0;
}