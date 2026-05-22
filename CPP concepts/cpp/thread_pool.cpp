#include<bits/stdc++.h>
using namespace std;

class ThreadPool {
    queue<function<void()>> taskQueue;
    vector<thread> workers;
    mutex queueMutex;
    condition_variable condition;
    bool stop;
    mutex coutMutex;
    int activeTasks;  // Track running tasks
    condition_variable taskComplete;  // Signal when task completes

    public:
    ThreadPool(int numThreads) {
        this->stop = false;
        this->activeTasks = 0;
        for(int i = 0; i < numThreads; i++) {
            this->workers.push_back(thread(&ThreadPool::workerThread, this));
        }
    }
    
    mutex& getCoutMutex() {
        return coutMutex;
    }

    void workerThread() {
        while(true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(this->queueMutex);
                this->condition.wait(lock, [this] { 
                    return this->stop || !this->taskQueue.empty(); 
                });
                if(this->stop && this->taskQueue.empty()) {
                    return;
                }
                task = move(this->taskQueue.front());
                this->taskQueue.pop();
                activeTasks++;
            }
            task();  // Execute without holding lock
            {
                lock_guard<mutex> lock(this->queueMutex);
                activeTasks--;
            }
            taskComplete.notify_all();
        }
    }

    void addTask(function<void()> task) {
        unique_lock<mutex> lock(this->queueMutex);
        this->taskQueue.push(task);
        this->condition.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(this->queueMutex);
            this->stop = true;
        }
        this->condition.notify_all();
        for(thread &worker: this->workers) {
            worker.join();
        }
    }

    void waitForCompletion() {
        unique_lock<mutex> lock(this->queueMutex);
        taskComplete.wait(lock, [this] {
            return taskQueue.empty() && activeTasks == 0;
        });
    }
};

int main() {
    ThreadPool pool(4);
    cout << "Thread pool created with 4 threads" << endl;
    cout << "Adding 50 tasks" << endl;
    for (int i = 0; i < 50; i++) {
        pool.addTask([i, &pool] {
            {
                lock_guard<mutex> lock(pool.getCoutMutex());
                cout << "Task " << i << " is executed by thread: " << this_thread::get_id() << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(100));  // Changed to 100ms
        });
    }
    pool.waitForCompletion();
    cout << "All tasks completed!" << endl;
    return 0;
}
