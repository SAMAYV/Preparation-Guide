#include <iostream>
#include <list> // for list operations
using namespace std;
 
int main()
{
    list<int> list1 = {1, 2, 3, 4};
    auto it = list1.begin();
    advance(it, 2);
    list1.insert(it, 5);
    list1.remove(2);
    cout << "The list after inserting"
         << " 1 element using insert() is : ";
    for (list<int>::iterator i = list1.begin();
         i != list1.end();
         i++)
        cout << *i << " ";
    cout << endl;
}