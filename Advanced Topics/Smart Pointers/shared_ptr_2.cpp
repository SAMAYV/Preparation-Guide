#include <iostream>
#include <memory>
using namespace std;

struct Sample
{
    void dummyFunction() {
        cout << "dummyFunction" << endl;
    }
};
int main()
{
    shared_ptr<Sample> ptr = make_shared<Sample>();
    (*ptr).dummyFunction();     // Will Work
    ptr->dummyFunction();       // Will Work
    
    // ptr[0]->dummyFunction(); // This line will not compile.
    // ptr++;                   // This line will not compile.
    // ptr--;                   // This line will not compile.
    
    shared_ptr<Sample> ptr2(ptr);
    if(ptr == ptr2)             // Will work
        cout << "ptr and ptr2 are equal" << endl;

    // We can also access the internal raw pointer from shared_ptr object like this
    ptr = make_shared<Sample>();
    Sample* rawptr = ptr.get();

    // Ideally we should not use this because it can cause problem if we delete this pointer by mistake. 
    // In that case when shared_ptr object will go out of scope then it will try to delete already deleted memory 
    // and it will create our program to crash. We will discuss this in more detail in next post.
    return 0;
}
