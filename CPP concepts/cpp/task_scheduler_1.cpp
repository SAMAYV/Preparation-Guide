#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class TaskScheduler {
    queue<function<void()>> queue_;
    mutex mutex_;
    condition_variable not_empty_;
    condition_variable not_full_;
    static constexpr size_t MAX_SIZE = 1000;

public:
    void submitTask(function<void()> task) {
        unique_lock<mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return queue_.size() < MAX_SIZE; });
        queue_.push(move(task));
        not_empty_.notify_one();
    }
    void workerLoop() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(mutex_);
                not_empty_.wait(lock, [this] { return !queue_.empty(); });
                task = move(queue_.front());
                queue_.pop();
                not_full_.notify_one();
            }
            task();
        }
    }
};
