#include <iostream>
#include <tuple>
#include <string>

int main()
{
    // Creating and Initializing a tuple
    std::tuple<int, double, std::string> result1 { 22, 19.28, "text" };

    // Compile error, as no way to deduce the types of elements in tuple
    //auto result { 22, 19.28, "text" }; // Compile error

    // Creating a tuple using std::make_tuple
    auto result2 = std::make_tuple( 7, 9.8, "text" );

    // std::make_tuple automatically deduced the type and created tuple

    // Print values
    std::cout << "int value = " << std::get < 0 > (result2) << std::endl;
    std::cout << "double value = " << std::get < 1 > (result2) << std::endl;
    std::cout << "string value = " << std::get < 2 > (result2) << std::endl;

    return 0;
}