#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <map>
#include <chrono>

using namespace std;

class Task {
    int id;
    bool isDone;
    mutex taskLock;
    public:
    Task(int id) : id(id), isDone(false) {}
    void execute(int workerId) {
        {
            unique_lock<mutex> lock(taskLock);
            cout << "Task " << id << " executed by worker " << workerId << endl;
            this_thread::sleep_for(chrono::seconds(1));
            // mark the task as completed
            isDone = true;
        }
    }
    int getId() {
        return id;
    }
    bool checkIsDone() {
        return isDone;
    }
};

class TaskSystem {
    vector<int> taskIds;
    map<int, Task*> idTaskMap;
    map<int, vector<int>> taskDependencyList;
    queue<Task*> orderedTasks;
    condition_variable cv;
    mutex queueMutex;
    mutex coutMutex; // used for printing to std:out in a consistent way
    vector<thread> workers;
    bool stop;
    
    public:
    TaskSystem(int noOfWorkers) {
        taskIds.clear();
        initializeWorkers(noOfWorkers);
        stop = false;
    }
    void initializeWorkers(int noOfWorkers) {
        for(int i = 0; i < noOfWorkers; i++) {
            workers.push_back(thread(&TaskSystem::workerThread, this, i));
        }
    }
    Task* createTask(int id) {
        return new Task(id);
    }
    void addTask(int id) {
        // Handle case if task is already present
        if (idTaskMap.count(id)) {
            cout << "Can't create task since it is already present";
            return;
        }
        Task* newTask = this->createTask(id);
        taskIds.push_back(id);
        idTaskMap[id] = newTask;
    }
    void addDependency(int taskAId, int taskBId) {
        if (!idTaskMap.count(taskAId)) {
            cout << "Can't add dependency since task with id " << taskAId << " is not present";
            return;
        }
        if (!idTaskMap.count(taskBId)) {
            cout << "Can't add dependency since task with id " << taskBId << " is not present";
            return;
        }
        taskDependencyList[taskAId].push_back(taskBId);
    }
    void order(int currTask, int parentTask, map<int, bool>& isVisited) {
        isVisited[currTask] = 1;
        for(int dependentTask : taskDependencyList[currTask]) {
            if (!isVisited[dependentTask]) {
                order(dependentTask, currTask, isVisited);
            }
        }
        orderedTasks.push(idTaskMap[currTask]);
    }
    void orderCurrentTasksIds() {
        // order current task ids
        map<int, bool> isVisited;
        int noOfTasks = taskIds.size();
        for(int i = 0; i < noOfTasks; i++) {
            int taskId = taskIds[i];
            if (!isVisited[taskId]) {
                order(taskId, -1, isVisited);
            }
        }
    }
    bool canWePickTask(Task* task) {
        int taskId = task->getId();
        for(int dependentTaskId : taskDependencyList[taskId]) {
            Task* dependentTask = idTaskMap[dependentTaskId];
            if (!dependentTask->checkIsDone()) {
                return false;
            }
        }
        return true;
    }
    void workerThread(int workerId) {
        while(true) {
            Task* task;
            {
                unique_lock<mutex> lock(queueMutex);
                cv.wait(lock, [this]{
                    return orderedTasks.size() > 0 || stop;
                });
                // Exit when no pending tasks are there and we have a stop signal
                if (orderedTasks.size() == 0 && stop) {
                    return;
                }
                task = orderedTasks.front();
                orderedTasks.pop();
                // Check if dependencies are met
                if (!canWePickTask(task)) {
                    // Re-queue at the back and wait
                    orderedTasks.push(task);
                    task = NULL;
                }
            }
            if (task) {
                // use the cout mutex for consistent printing
                lock_guard<mutex> lock(coutMutex);
                // do the task
                task->execute(workerId);
                cv.notify_all();  // Notify others - dependencies may now be met
            }
        }
    }
    void wakeUpWorkers() {
        cv.notify_all();
    }
    void exit() {
        // during exit we can make stop = true since we have tasks already in queue.
        stop = true;
        for(int i = 0; i < workers.size(); i++) {
            workers[i].join();
        }
    }
};

int main()
{
    TaskSystem taskSystem(2);
    taskSystem.addTask(1);
    taskSystem.addTask(2);
    taskSystem.addTask(3);
    taskSystem.addTask(4);
    taskSystem.addDependency(3, 1);
    taskSystem.orderCurrentTasksIds();
    // We can wake up the threads
    taskSystem.wakeUpWorkers();
    taskSystem.exit();
    return 0;
}


/*

Please send the code to: interview-material@onehouse.ai, praveeng@onehouse.ai, sameer@onehouse.ai

Guidelines:
You are required to implement a thread-safe in-memory task workflow orchestration system. The system should be capable of handling complex workflows where tasks depend on the completion of other tasks. Each task can be executed asynchronously, and the system should manage the dependencies and ensure that each task is executed only after all its dependencies have been completed. The system must support the following operations efficiently:
Add Task: Add a task to the workflow.
Add Dependency: Add a dependency between tasks.
Execute Workflow: Execute the entire workflow, ensuring all dependencies are respected.
Shutdown: Gracefully shutdown the system, ensuring all tasks are completed before termination.
Example 
taskSystem.addTask(task1);
taskSystem.addTask(task2);
taskSystem.addTask(task3);

// Add task 2 as a pre-requisite for task 3.
taskSystem.addDependency(task3.id, task2.id);
// Add task 1 as a pre-requisite for task 3.
taskSystem.addDependency(task3.id, task1.id);

taskSystem.executeWorkflow();
// Output:
task1.run()
task2.run()
task3.run()

OR

task2.run()
task1.run()
task3.run()

taskSystem.shutdown(); 
Milestone 1:
Task can be run sequentially
Milestone 2:
Non dependent tasks should run parallel to each other in multi-threaded environment
Milestone 3:
Tasks can have retries defined.
task.run() {
// some logic to fail task given number of times
}
Make the tasks randomly fail (20% of times) and still ensure that the workflow fully runs

*/