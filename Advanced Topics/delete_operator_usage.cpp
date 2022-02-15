#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ComplexNumber
{
    T x;
    T y;
public:
    ComplexNumber(T a, T b) : x(a), y(b) {}
    void display() {
        cout << x << " + i" << y << endl;
    }
    
    // Deleted template specialisation 
    ComplexNumber(char a, char b) = delete;
    
    // Deleted template specialisation  
    ComplexNumber(double a, double b) = delete;
};

// Now we want to restrict that no one can use CompleNumber class with double or char as template parameter. 
// For that we need to delete certain specialized functions.