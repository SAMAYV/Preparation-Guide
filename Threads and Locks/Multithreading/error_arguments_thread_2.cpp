#include <iostream>
#include <thread>
using namespace std;

void threadCallback(int const& x)
{
    int& y = const_cast<int&>(x);
    y++;
    cout << "Inside Thread x = " << x << endl;
}
int main()
{
    int x = 9;
    cout << "In Main Thread : Before Thread Start x = " << x << endl;
    thread threadObj(threadCallback, x);
    threadObj.join();
    cout << "In Main Thread : After Thread Joins x = " << x << endl;
    return 0;
}
/* Even if threadCallback accepts arguments as reference but still changes done it are not visible outside the thread.
Its because x in the thread function threadCallback is reference to the temporary value copied at the new thread’s stack. */