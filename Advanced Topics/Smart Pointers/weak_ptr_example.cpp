#include <iostream>
#include <memory>
using namespace std;

class Node
{
    int value;
public:
    shared_ptr<Node> leftPtr;
    shared_ptr<Node> rightPtr;
    
    // Just Changed the shared_ptr to weak_ptr
    weak_ptr<Node> parentPtr;
    Node(int val) : value(val) {
        cout << "Contructor" << endl;
    }
    ~Node() {
        cout << "Destructor" << endl;
    }
};
int main()
{
    shared_ptr<Node> ptr = make_shared<Node>(4);
    ptr->leftPtr = make_shared<Node>(2);
    ptr->leftPtr->parentPtr = ptr;
    ptr->rightPtr = make_shared<Node>(5);
    ptr->rightPtr->parentPtr = ptr;
    
    cout << "ptr reference count = " << ptr.use_count() << endl;
    cout << "ptr->leftPtr reference count = " << ptr->leftPtr.use_count() << endl;
    cout << "ptr->rightPtr reference count = " << ptr->rightPtr.use_count() << endl;
    cout << "ptr->rightPtr->parentPtr reference count = " << ptr->rightPtr->parentPtr.lock().use_count() << endl;
    cout << "ptr->leftPtr->parentPtr reference count = " << ptr->leftPtr->parentPtr.lock().use_count() << endl;
    return 0;
}
// Hence by using weak_ptr the memory leak problem is solved for binary tree nodes.
// https://thispointer.com//shared_ptr-binary-trees-and-the-problem-of-cyclic-references/