#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std::chrono;
using namespace std;

string fetchDataFromDB(string recvdData)
{
    // Make sure that function takes 5 seconds to complete
    this_thread::sleep_for(seconds(5));
    
    // Do stuff like creating DB Connection and fetching Data
    return "DB_" + recvdData;
}
struct FileFetcher
{
    string operator()(string recvdData)
    {
        // Make sure that function takes 5 seconds to complete
        this_thread::sleep_for(seconds(5));
        
        // Do stuff like fetching Data File
        return "File_" + recvdData;
    }
};
int main()
{
    // Get Start Time
    system_clock::time_point start = system_clock::now();
    
    future<string> resultFromDB = async(launch::async, fetchDataFromDB, "Data");
    
    future<string> resultFromFile = async(launch::async, FileFetcher(), "Data");

    // Fetch Data from DB
    // Will block till data is available in future<string> object.
    string dbData = resultFromDB.get();

    // Fetch Data from File
    // Will block till data is available in future<string> object.
    string fileData = resultFromFile.get();

    // Lambda Function
    future<string> result = async([](string recvdData){
        this_thread::sleep_for(seconds(5));

        // Do stuff like creating DB Connection and fetching Data
        return "DB_" + recvdData;
    
    }, "Data");
    
    // Get End Time
    auto end = system_clock::now();
    
    auto diff = duration_cast<chrono::seconds>(end - start).count();
    
    cout << "Total Time Taken = " << diff << " Seconds" << endl;
    
    // Combine The Data
    string data = dbData + " :: " + fileData;
    
    // Printing the combined Data
    cout << "Data = " << data << endl;

    return 0;
}