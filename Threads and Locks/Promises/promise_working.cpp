#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
using namespace std;
 
void _accumulate(vector<int>::iterator first, vector<int>::iterator last, promise<int> accumulate_promise) 
{
    int sum = accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}
int main() 
{
    vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    
    // create promise
    promise<int> accumulate_promise;
    
    // engagement with future
    future<int> accumulate_future = accumulate_promise.get_future();
    
    thread work_thread(_accumulate, numbers.begin(), numbers.end(), move(accumulate_promise));
                            
    accumulate_future.wait();           // wait for result
    cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();                 // wait for thread completion

    shared_future<int> shfut = accumulate_future.share();
    // shared futures can be accessed multi times
    cout << "value: " << shfut.get() << '\n';
    cout << "its double: " << shfut.get()*2 << '\n';
    
    return 0;
}