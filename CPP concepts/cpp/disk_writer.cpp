#include <mutex>
#include <condition_variable>
#include <fstream>
#include <algorithm>
using namespace std;

/*
You want at most 100 MB of data written to disk at once to avoid overwhelming the I/O subsystem. 
Threads writing files track how much data is in flight. Before writing, they acquire permits equal to their file size. 
If not enough permits are available, they wait until ongoing writes complete and release permits. 
This uses a semaphore where each permit represents 1 MB.

This pattern appears when operations consume variable amounts of a shared resource budget.

Memory Budget for Buffers: Each worker thread allocates buffers for processing data, but you want at most 500 MB of 
buffers across all threads. Use a semaphore with 500 permits (1 permit = 1 MB). Before allocating a 10 MB buffer, 
acquire 10 permits. The thread blocks if insufficient memory budget remains. When the thread finishes and deallocates 
its buffer, release 10 permits back. This caps total memory usage while letting threads allocate variable-sized buffers 
based on their needs.
*/

class DiskWriter {
private:
    static constexpr int MB = 1024 * 1024;
    mutex mtx;
    condition_variable cv;
    int available = 100; // 100 MB
public:
    void writeFile(const vector<char>& data, const string& path) {
        int permits = max(1, (int)((data.size() + MB - 1) / MB));
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this, permits] { return available >= permits; });
            available -= permits;
        }
        try {
            ofstream file(path, ios::binary);
            file.write(data.data(), data.size());
        } catch (...) {
            lock_guard<mutex> lock(mtx);
            available += permits;
            cv.notify_all();
            throw;
        }
        lock_guard<mutex> lock(mtx);
        available += permits;
        cv.notify_all();
    }
};
