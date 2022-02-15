#include <iostream>
#include <typeinfo>
#include <map>
#include <string>
#include <iterator>
using namespace std;

auto sum(int x, int y) -> int {
    return x + y;
}
int main()
{
    auto var_1 = 5;     // Storing a int inside a auto variable
    auto var_2 = 'C';   // Storing a character inside a auto variable

    cout << var_1 << endl;
    cout << var_2 << endl;
    
    // Storing Lambda function inside a auto variable
    auto fun_sum = [](int a, int b) {
        return a + b;
    };
    cout << fun_sum(4, 5) << endl;

    map<string, string> mapOfStrs;
    // Insert data in Map
    mapOfStrs.insert(pair<string, string>("first", "1"));
    mapOfStrs.insert(pair<string, string>("sec", "2"));
    mapOfStrs.insert(pair<string, string>("thirs", "3"));
    // Iterate over the map and display all data;
    // Create an iterator
    map<string, string>::iterator it = mapOfStrs.begin();
    while(it != mapOfStrs.end()) {
        cout << it->first << "::" << it->second << endl;
        it++;
    }

    // Iterate using auto
    auto itr = mapOfStrs.begin();
    while (itr != mapOfStrs.end()) {
        cout << itr->first << "::" << itr->second << endl;
        itr++;
    }

    auto x = 1;
    // Cannot change the type of already initialized auto variable
    // Error will occur at compile time
    // x = "dummy";

    // Can not declare auto variable without initialization because its type is based on initiazing value.
    // auto a;
    
    auto value = sum(3, 5);
    cout << value << endl;
    return 0;
}
