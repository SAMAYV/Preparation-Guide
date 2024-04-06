#include <iostream>
#include <thread>
#include <future>
#include <string>
using namespace std::chrono;
using namespace std;

// Fetch some data from DB
string getDataFromDB(string token)
{
    // Make sure that function takes 5 seconds to complete
    this_thread::sleep_for(seconds(5));

    // Do some stuff to fetch the data
    string data = "Data fetched from DB by Filter :: " + token;
    return data;
}
// Function Object to Fetch Data from DB
struct DBDataFetcher
{
    string operator()(string token)
    {
        // Do some stuff to fetch the data
        string data = "Data From " + token;
        return data;
    }
};
int main()
{
    // Get Start Time
    system_clock::time_point start = system_clock::now();

    // Create a packaged_task<> that encapsulated the callback i.e. a function
    packaged_task<string(string)> task(getDataFromDB);
    // Fetch the associated future<> from packaged_task<>
    future<string> result = task.get_future();

    // Create a packaged_task<> that encapsulated a lambda function
    packaged_task<string(string)> task1([](string token){
        // Do some stuff to fetch the data
        string data = "Data From " + token;
        return data;
    });

    // Create a packaged_task<> that encapsulated a lambda function
    packaged_task<string(string)> task2(move(DBDataFetcher()));
    
    // Pass the packaged_task to thread to run asynchronously
    thread th(move(task), "Arg");
    
    // Join the thread. Its blocking and returns when thread is finished.
    th.join();

    // Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
    string data = result.get();

    // Get End Time
    auto end = system_clock::now();
    
    auto diff = duration_cast<chrono::seconds>(end - start).count();

    cout << "Total Time Taken = " << diff << " Seconds" << endl;

    cout << data << endl;
    return 0;
}