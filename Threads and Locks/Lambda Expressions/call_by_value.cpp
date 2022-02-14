#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    string msg = "Hello";
    int counter = 10;
    
    // Defining Lambda function and Capturing Local variables by Value
    auto func = [msg, counter] () mutable {
        cout << "Inside Lambda :: msg = " << msg << endl;
        cout << "Inside Lambda :: counter = " << counter << endl;
        // Change the counter & msg
        // Change will not affect the outer variable because counter variable is captured by value in Lambda function
        msg = "Temp";
        counter = 20;
        cout << "Inside Lambda :: After changing :: msg = " << msg << endl;
        cout << "Inside Lambda :: After changing :: counter = " << counter << endl;
    };
    // Call the Lambda function
    func();
    
    // Values of local variables are not changed.
    cout << "msg = " << msg << endl;
    cout << "counter = " << counter << endl;
    return 0;
}

/* To capture all local variables from outer scope by value, pass “=” in the capture list.

Capturing All Local variables by value except counter, which is captured by reference here.
auto func = [=, &counter] () mutable {}; 

*/