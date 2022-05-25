#include <iostream>
using namespace std;

// Function that accepts no parameter
// It is to break the recursion chain of vardiac template function
void log() {
    cout << "All parameters parsed\n";
}

//  Variadic Template Function that accepts variable number
template<typename T, typename ... Args>
void log(T first, Args ... args) {
    cout << first << "\n";        // Print the First Element
    log(args ...);                // Forward the remaining arguments
}
int main() 
{
    log(2, 3.4, "aaa");
    return 0;
}
/* 
So, this will be stack trace of calling above variadic template function is as follows,
void log();
void log(const char * first);
void log(double first, const char * c);
void log(int first, double b, const char * c);
*/