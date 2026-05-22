#include <semaphore>
#include <fstream>
using namespace std;

/*
This pattern appears whenever you need to cap concurrent operations without managing actual resource objects.
*/

// RAII guard to ensure semaphore is always released
template<ptrdiff_t LeastMaxValue>
class SemaphoreGuard {
private:
    counting_semaphore<LeastMaxValue>& sem;

public:
    // Acquire semaphore in constructor
    SemaphoreGuard(counting_semaphore<LeastMaxValue>& s) : sem(s) {
        sem.acquire();
    }

    // Release semaphore in destructor (ALWAYS called!)
    ~SemaphoreGuard() {
        sem.release();
    }

    // Prevent copying
    SemaphoreGuard(const SemaphoreGuard&) = delete;
    SemaphoreGuard& operator=(const SemaphoreGuard&) = delete;
};

class APIClient {
private:
    counting_semaphore<5> requestPermits{5};

public:
    // Method 1: Using RAII Guard (Recommended)
    Response makeRequest(const string& endpoint) {
        SemaphoreGuard<5> guard(requestPermits);  // Acquires semaphore
        auto response = httpClient.get(endpoint);
        return response;
        // Semaphore automatically released when guard goes out of scope
        // Even if httpClient.get() throws an exception!
    }

    // Method 2: Original approach with try-catch (Not recommended)
    Response makeRequestOld(const string& endpoint) {
        requestPermits.acquire();
        try {
            auto response = httpClient.get(endpoint);
            requestPermits.release();
            return response;
        } catch (...) {
            requestPermits.release();  // Code duplication
            throw;
        }
    }
};

class DownloadManager {
private:
    counting_semaphore<3> downloadSlots{3};

public:
    // Method 1: Using RAII Guard (Recommended)
    void download(const string& url, const string& destination) {
        SemaphoreGuard<3> guard(downloadSlots);  // Acquires semaphore

        auto data = httpClient.download(url);
        ofstream file(destination, ios::binary);
        file.write(reinterpret_cast<const char*>(data.data()), data.size());

        // Semaphore automatically released when guard goes out of scope
        // Works even if any of the above operations throw!
    }

    // Method 2: Original approach with try-catch (Not recommended)
    void downloadOld(const string& url, const string& destination) {
        downloadSlots.acquire();
        try {
            auto data = httpClient.download(url);
            ofstream file(destination, ios::binary);
            file.write(reinterpret_cast<const char*>(data.data()), data.size());
            downloadSlots.release();
        } catch (...) {
            downloadSlots.release();  // Code duplication
            throw;
        }
    }
};

/*
Rate-Limited API Wrapper: You integrate with an external API that allows at most 10 concurrent requests per account. 
Exceeding this returns errors. You don't have "request objects" to hand out, just a limit. Use a semaphore with 10 permits. 
Before making a request, acquire a permit. After the request completes (success or failure), release it in a finally block. 
Threads automatically queue when the limit is hit, preventing you from violating the API's rate limits.

Image Processing Pipeline: Your service resizes uploaded images but you want to limit concurrent processing to 5 operations 
to avoid CPU saturation. Use a semaphore with 5 permits. Before starting an image transformation, acquire a permit. 
After completion, release it. This caps concurrent image processing without needing a fixed pool of worker threads. 
The work happens on whatever thread acquired the permit.

Video Transcoding Service: Your server transcodes uploaded videos but you want at most 3 concurrent transcode operations 
since each is CPU and memory intensive. Use a semaphore with 3 permits. Before starting a transcode job, acquire a permit.
After the job finishes, release it. This prevents resource exhaustion while allowing any thread to perform transcoding work.
*/