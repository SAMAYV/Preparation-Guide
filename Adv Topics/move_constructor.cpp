#include <iostream>
#include <vector>
using namespace std;

class Container 
{
    int* m_Data;
public:
    Container(){
        // Allocate an array of 20 int on heap
        m_Data = new int[20];
        cout << "Constructor: Allocation 20 int" << endl;
    }
    ~Container(){
        if(m_Data){
            delete[] m_Data;
            m_Data = NULL;
        }
    }
    // Copy Constructor
    Container(const Container& obj)
    {
        // Allocate an array of 20 int on heap
        m_Data = new int[20];
        // Copy the data from passed object
        for(int i = 0; i < 20; i++){
            m_Data[i] = obj.m_Data[i];
        }
        cout << "Copy Constructor: Allocation 20 int" << endl;
    }
    // Assignment Operator
    Container& operator=(const Container& obj)
    {
        if(this != &obj)
        {
            // Allocate an array of 20 int on heap
            m_Data = new int[20];
            // Copy the data from passed object
            for(int i = 0; i < 20; i++){
                m_Data[i] = obj.m_Data[i];
            }
            cout << "Assigment Operator: Allocation 20 int" << endl;
        }
        return *this;
    }
    // Move Constructor
    Container(Container&& obj)
    {
        // Just copy the pointer
        m_Data = obj.m_Data;
        // Set the passed object's member to NULL
        obj.m_Data = NULL;
        cout << "Move Constructor" << endl;
    }
    // Move Assignment Operator
    Container& operator=(Container&& obj)
    {
        if(this != &obj)
        {
            // Just copy the pointer
            m_Data = obj.m_Data;
            // Set the passed object's member to NULL
            obj.m_Data = NULL;
            cout << "Move Assignment Operator" << endl;
        }
        return *this;
    }
};
// Create an object of Container and return
Container getContainer()
{
    Container obj;
    return obj;
}
int main() 
{
    // Create a vector of Container Type
    vector<Container> vecOfContainers;

    // Add object returned by function into the vector
    vecOfContainers.push_back(getContainer());
    Container obj;
    obj = getContainer();
    return 0;
}

/* In the move constructor, we just copied the pointer. Now member variable m_Data points to the same memory on heap. 
Then we set the m_Data of passed object to NULL. So, we didn’t allocated any memory on heap in move constructor, we just 
shifted the control of memory. Now if we create the vector  of class container and push a object returned from getContainer() 
into it. Then a new object will created from this temporary object but as getContainer() is a rvalue, so Move Constructor 
of this new Container class’s object will be called and in that memory will be just shifted. So, actually on heap we will 
create only one array of integers. */

/* Generally, we use Factory classes to create object of our classes. But we actually created 2 objects for it because 
getContainer() function returned a temporary object which got copied into a new object and then destructed. 
This 2nd object got inserted in vector. How to solve this problem of resource and effort wastage due to temporary objects? 
Is there a way to move the 1st object instead of creating 2nd one and copying contents to it? */