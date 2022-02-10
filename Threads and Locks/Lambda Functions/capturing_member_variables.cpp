#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class OddCounter
{
    // tracks the count of odd numbers encountered
    int mCounter = 0;
public:
    int getCount(){
        return mCounter;
    }
    void update(vector<int> & vec)
    {
        // Traverse the vector and increment mCounter if element is odd
        // this is captured by value inside lambda
        for_each(vec.begin(), vec.end(), [this](int element){
            if(element % 2){
                mCounter++; // Accessing member variable from outer scope
            }
        });
    }
};
int main(int argc, char **argv)
{
    vector<int> vec = {12,3,2,1,8,9,0,2,3,9,7};
    
    OddCounter counterObj;
    
    // Passing the vector to OddCounter object
    counterObj.update(vec);
    
    int count = counterObj.getCount();
    cout << "Counter = " << count << endl;

    return 0;
}