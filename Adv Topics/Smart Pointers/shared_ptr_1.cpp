#include <iostream>
#include <memory> // We need to include this for shared_ptr
using namespace std;

int main()
{
    // Creating a shared_ptr through make_shared
    shared_ptr<int> p1 = make_shared<int>();    // same as shared_ptr<int> p1(new int());
    *p1 = 78;
    cout << "p1 = " << *p1 << endl;
    
    // Shows the reference count
    cout << "p1 Reference count = " << p1.use_count() << endl;

    // Second shared_ptr object will also point to same pointer internally
    // It will make the reference count to 2.
    shared_ptr<int> p2(p1);
    
    // Shows the reference count
    cout << "p2 Reference count = " << p2.use_count() << endl;
    cout << "p1 Reference count = " << p1.use_count() << endl;

    // Comparing smart pointers
    if(p1 == p2) {
        cout << "p1 and p2 are pointing to same pointer\n";
    }
    cout << "Reset p1 " << endl;
    p1.reset();

    // Reset the shared_ptr, in this case it will not point to any Pointer internally
    // hence its reference count will become 0.
    cout << "p1 Reference Count = " << p1.use_count() << endl;

    // Reset the shared_ptr, in this case it will point to a new Pointer internally
    // hence its reference count will become 1.
    p1.reset(new int(11));
    cout << "p1  Reference Count = " << p1.use_count() << endl;
    
    // Assigning nullptr will de-attach the associated pointer and make it to point null
    p1 = nullptr;
    cout << "p1  Reference Count = " << p1.use_count() << endl;
    if(!p1) {
        cout << "p1 is NULL" << endl;
    }
    return 0;
}

/* When a shared_ptr object goes out of scope, its destructor is called. Inside its destructor 
it decrements the reference count by 1 and if new value of reference count is 0 then it deletes the associated raw pointer. */