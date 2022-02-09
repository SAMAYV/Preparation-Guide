#include <iostream>
#include <string>
#include <thread>
using namespace std;

void threadCallback(int x, string str)
{
    cout << "Passed Number = " << x << endl;
    cout << "Passed String = " << str << endl;
}
int main()
{
    int x = 10;
    string str = "Sample String";
    thread threadObj(threadCallback, x, str);
    threadObj.join();
    return 0;
}