#include <iostream>
#include <memory>
using namespace std;

typedef struct Sample 
{
    int internalValue;
    Sample() {
        internalValue = 0;
        cout << "Constructor" << endl;
    }
    ~Sample() {
        cout << "Destructor" << endl;
    }
} Sample;

int main()
{
    {
        Sample* rawPtr = new Sample();
        shared_ptr<Sample> ptr_1(rawPtr);
        {
            shared_ptr<Sample> ptr_2(rawPtr);
        }
        // As ptr_2 dont know that the same raw pointer is used by another shared_ptr i.e. ptr_1, therefore
        // here when ptr_2 goes out of scope and it deletes the raw pointer associated with it.
        // Now ptr_1 is internally containing a dangling pointer. Therefore when we it
        // will go out of scope it will again try to delete the already deleted raw pointer and application
        // will crash.
    }
    {
        int x = 12;
        shared_ptr<int> ptr(&x);
        // shared_ptr expects that memory associated with it is from heap, therefore when it goes out of scope 
        // it deletes the associated memory if reference count is 0. But in above example we associated the memory 
        // from stack to shared_ptr object and in its destructor this shared_ptr object will call delete operation on this memory. 
        // As this memory was from stack not from heap, so our program will crash.
    }
    return 0;
}