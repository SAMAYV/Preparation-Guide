#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int mul = 5;

    for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x) {
        cout << x << " ";
        // Can modify the mul inside this lambda function because all outer scope elements has write access here.
        mul = 3;
    });
    cout << endl;

    for_each(arr, arr + sizeof(arr) / sizeof(int), [=](int &x) {
        x = x * mul;
        // Can not modify the mul inside this lambda function because all outer scope elements has read only access here.
    });
    cout << endl;
    
    for_each(arr, arr + sizeof(arr) / sizeof(int), [](int x) {
        // No access to mul inside this lambda function because all outer scope elements are not visible here.
    });
    cout << endl;
    
    return 0;
}