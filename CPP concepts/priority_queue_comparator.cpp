// C++ Program to implement
// Custom Comparator in Priority Queue
#include <iostream>
#include <queue>
#define PII pair<int, int>
 
// Pair of Ints = PII
using namespace std;
 
// based on first part in ascending and second part in
// descending first basis
class Compare {
public:
    bool operator()(PII below, PII above)
    {
        if (below.first > above.first) {
            return true;
        }
        else if (below.first == above.first
                 && below.second < above.second) {
            return true;
        }
 
        return false;
    }
};
 
int main()
{
    priority_queue<PII, vector<PII>, Compare> ds;
    ds.push({ 100, 11 });
    ds.push({ 100, 41 });
    ds.push({ 100, 21 });
    ds.push({ 300, 1 });
    ds.push({ 300, 2 });
    ds.push({ 1, 1 });
    ds.push({ 1, 2 });
    ds.push({ 1, 20 });
 
    cout << "The priority queue is : \n";
    while (!ds.empty()) {
        cout << ds.top().first << " " << ds.top().second
             << "\n";
        ds.pop(); // heapify happens
    }
 
    return 0;
}