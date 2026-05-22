#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <functional>
#include <climits>
#include <string>

using namespace std;

// https://leetcode.com/discuss/post/1388054/concurrency-problem-faangconcurrency-gen-jr7d/

long currentTime() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

class Task {
    public:
    virtual void run() = 0;
    virtual ~Task() {}
};

class PrintTask : public Task {
    string message;
    public:
    PrintTask(string msg) : message(msg) {}
    void run() override {
        cout << currentTime() << " - " << message << " executed by thread: " << this_thread::get_id() << endl;
    }
};

class TaskWrapper {
    public:
    virtual long getExecutionTime() = 0;
    virtual void run() = 0;
    virtual TaskWrapper* getNextTaskInstance() = 0;
    virtual bool shouldSchedule() = 0;
    virtual ~TaskWrapper() {}
};

class InitialDelayTaskWrapper : public TaskWrapper {
    Task* task;
    long executionTime;
    public:
    InitialDelayTaskWrapper(Task* task, long executionTime) {
        this->task = task;
        this->executionTime = executionTime;
    }
    long getExecutionTime() {
        return this->executionTime;
    }
    void run() {
        this->task->run();
    }
    TaskWrapper* getNextTaskInstance() {
        return NULL;
    }
    bool shouldSchedule() {
        return 0;
    }
};

// Fixed interval: task=2s: 0, interval=5s: 0, 5, 10, 15, 20, ...
// Fixed delay: task=2s, delay=5s: 0, 2, 7, 12, 17, ...
class FixedIntervalTaskWrapper : public TaskWrapper {
    Task* task;
    long interval;
    long executionTime;
    public:
    FixedIntervalTaskWrapper(Task* task, long interval, long executionTime) {
        this->task = task;
        this->interval = interval;
        this->executionTime = executionTime;
    }
    long getExecutionTime() {
        return this->executionTime;
    }
    void run() {
        this->task->run();
    }
    TaskWrapper* getNextTaskInstance() {
        return new FixedIntervalTaskWrapper(this->task, this->interval, this->executionTime + this->interval);
    }
    bool shouldSchedule() {
        return 1;
    }
};


class Comparator {
    public:
    bool operator()(TaskWrapper* a, TaskWrapper* b) {
        return a->getExecutionTime() > b->getExecutionTime();
    }
};

class Scheduler {
    priority_queue<TaskWrapper*, vector<TaskWrapper*>, Comparator> taskQueue;
    mutex lock;
    condition_variable isNewTaskAvailable;
    thread schedulerThread;
    bool stop;
    
    public:
    Scheduler() {
        this->stop = false;
        this->schedulerThread = thread(&Scheduler::schedule, this);
    }
    void schedule() {
        while(!stop) {
            unique_lock<mutex> ul(this->lock);
            long sleep = getSleepTimeUntilNextTask();
            while(sleep > 0){
                // wait for isNewTaskAvailable or sleep
                // if isNewTaskAvailable then break else sleep for sleep time
                isNewTaskAvailable.wait_for(ul, chrono::milliseconds(sleep), [this] { 
                    return this->stop;
                });
                if(stop) {
                    return;
                }
                sleep = getSleepTimeUntilNextTask();
            }
            // Get the task and remove it from the queue
            TaskWrapper* latestTask = taskQueue.top();
            taskQueue.pop();
            ul.unlock();
            // Run the task in a new thread
            thread taskThread(&Scheduler::executeTask, this, latestTask);
            taskThread.detach();
        }
    }
    void executeTask(TaskWrapper* task) {
        task->run();
        if (task->shouldSchedule()) {
            unique_lock<mutex> ul(this->lock);
            this->taskQueue.push(task->getNextTaskInstance());
            ul.unlock();
            isNewTaskAvailable.notify_all();
        }
    }
    void addTask(TaskWrapper* task) {
        unique_lock<mutex> ul(this->lock);
        taskQueue.push(task);
        ul.unlock();
        isNewTaskAvailable.notify_all();
    }
    long getSleepTimeUntilNextTask() {
        return taskQueue.empty() ? LONG_MAX : taskQueue.top()->getExecutionTime() - currentTime();
    }
    ~Scheduler() {
        this->stop = true;
        this->isNewTaskAvailable.notify_all();
        this->schedulerThread.join();
    }
};

class SchedulerService {
    Scheduler* scheduler;
    public:
    SchedulerService() {
        this->scheduler = new Scheduler();
    }
    void scheduleTaskWithInitialDelay(Task* task, long initialDelay) {
        InitialDelayTaskWrapper* taskWrapper = new InitialDelayTaskWrapper(task, currentTime() + initialDelay);
        this->scheduler->addTask(taskWrapper);
    }
    void scheduleTaskWithFixedInterval(Task* task, long initialDelay, long interval) {
        FixedIntervalTaskWrapper* taskWrapper = new FixedIntervalTaskWrapper(task, interval, currentTime() + initialDelay);
        this->scheduler->addTask(taskWrapper);
    }
};

int main() {
    SchedulerService* service = new SchedulerService();
    
    // Schedule tasks with initial delay
    Task* task1 = new PrintTask("Task 1 (delay 2s)");
    service->scheduleTaskWithInitialDelay(task1, 2000);
    
    Task* task2 = new PrintTask("Task 2 (delay 5s)");
    service->scheduleTaskWithInitialDelay(task2, 5000);
    
    // Schedule recurring task with fixed interval
    Task* task3 = new PrintTask("Task 3 (recurring every 3s)");
    service->scheduleTaskWithFixedInterval(task3, 1000, 3000);
    
    Task* task4 = new PrintTask("Task 4 (recurring every 2s)");
    service->scheduleTaskWithFixedInterval(task4, 500, 2000);
    
    cout << "Scheduler started at: " << currentTime() << endl;
    
    // Let tasks run for 15 seconds
    this_thread::sleep_for(chrono::seconds(15));
    
    cout << "Main thread exiting at: " << currentTime() << endl;
    
    return 0;
}
