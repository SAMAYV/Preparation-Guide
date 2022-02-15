#include <iostream>
#include <thread>
using namespace std;

class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
        cout << "Inside sampleMemberFunction " << x << endl;
    }
};
int main() 
{ 
    DummyClass dummyObj;
    int x = 10;
    thread threadObj(&DummyClass::sampleMemberFunction, &dummyObj, x);
    threadObj.join();
    return 0;
}
/* Pass the pointer to member function as callback function and pass pointer to Object as second argument. */