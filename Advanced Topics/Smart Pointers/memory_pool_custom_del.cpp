#include <bits/stdc++.h>
#include <memory>
using namespace std;

struct Sample
{
};

// Memory Pool Dummy Kind of Implementation
template<typename T>
class MemoryPool
{
public:
    T* AquireMemory()
    {
        cout << "AQUIRING MEMORY\n";
        return (new T());
    }
    void ReleaseMemory(T* ptr)
    {
        cout << "RELEASE MEMORY\n";
        delete ptr;
    }
};
int main()
{
    shared_ptr<MemoryPool<Sample>> memoryPoolPtr = std::make_shared<MemoryPool<Sample> >();
    shared_ptr<Sample> p3(memoryPoolPtr->AquireMemory(), bind(&MemoryPool<Sample>::ReleaseMemory, memoryPoolPtr, placeholders::_1));
    return 0;
}
// Cases when we don’t need to delete any memory we just need to releasing memory or resources to a pool etc.