#include <iostream>
#include <functional>
#include <algorithm>

// For placeholders _1, _2, ...
using namespace std::placeholders;

int add(int first, int second) {
    return first + second;
}

bool divisible(int num, int den) {
    return num % den == 0;
}

int main() {
    // Demonstrating binding and rearranging
    auto new_add_func = std::bind(&add, 12, _1);
    std::cout << new_add_func(5) << std::endl; // Outputs 17

    auto mod_add_func = std::bind(&add, _2, _1);
    std::cout << mod_add_func(12, 15) << std::endl; // Outputs 27

    // Using bind with std::function
    std::function<int (int)> mod_add_funcObj = std::bind(&add, 20, _1);
    std::cout << mod_add_funcObj(15) <<

 std::endl; // Outputs 35

    // Counting multiples of 5 in an array
    int arr[10] = {1, 20, 13, 4, 5, 6, 10, 28, 19, 15};
    auto divisible_by_5 = std::bind(&divisible, _1, 5);
    int count = std::count_if(arr, arr + sizeof(arr)/sizeof(int), divisible_by_5);
    std::cout << count << std::endl; // Outputs number of elements divisible by 5

    return 0;
}