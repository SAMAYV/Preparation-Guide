#include <iostream>
#include <memory>
using namespace std;

struct Task
{
    int mId;
    Task(int id) : mId(id) {
        cout << "Task::Constructor" << endl;
    }
    ~Task() {
        cout << "Task::Destructor" << endl;
    }
};
int main()
{
    // Empty unique_ptr object
    unique_ptr<int> ptr1;
    
    // Check if unique pointer object is empty
    if(!ptr1) cout << "ptr1 is empty" << endl;
    
    // Check if unique pointer object is empty
    if(ptr1 == nullptr) cout << "ptr1 is empty" << endl;

    // can not create unique_ptr object by initializing through assignment
    // std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error
    
    // Create a unique_ptr object through raw pointer
    unique_ptr<Task> taskPtr(new Task(23));
    
    // Check if taskPtr is empty or it has an associated raw pointer
    if(taskPtr != nullptr) cout << "taskPtr is not empty" << endl;

    //Access the element through unique_ptr
    cout << taskPtr->mId << endl;
    cout << "Reset the taskPtr" << endl;

    // Reseting the unique_ptr will delete the associated raw pointer and make unique_ptr object empty
    taskPtr.reset();

    // Check if taskPtr is empty or it has an associated raw pointer
    if(taskPtr == nullptr) cout << "taskPtr is empty" << endl;

    // Create a unique_ptr object through raw pointer
    unique_ptr<Task> taskPtr2(new Task(55));
    if(taskPtr2 != nullptr) cout << "taskPtr2 is not empty" << endl;

    // unique_ptr object is Not copyable
    // taskPtr = taskPtr2; //compile error
    // unique_ptr object is Not copyable
    // std::unique_ptr<Task> taskPtr3 = taskPtr2;
    {
        // Transfer the ownership
        unique_ptr<Task> taskPtr4 = move(taskPtr2);
        if(taskPtr2 == nullptr) cout << "taskPtr2 is empty" << endl;

        // ownership of taskPtr2 is transfered to taskPtr4
        if(taskPtr4 != nullptr) cout << "taskPtr4 is not empty" << endl;

        cout << taskPtr4->mId << endl;
        // taskPtr4 goes out of scope and deletes the assocaited raw pointer
    }
    // Create a unique_ptr object through raw pointer
    unique_ptr<Task> taskPtr5(new Task(55));
    if(taskPtr5 != nullptr) cout << "taskPtr5 is not empty" << endl;

    // Release the ownership of object from raw pointer
    Task* ptr = taskPtr5.release();
    if(taskPtr5 == nullptr) cout << "taskPtr5 is empty" << endl;
    cout << ptr->mId << endl;
    delete ptr;

    return 0;
}