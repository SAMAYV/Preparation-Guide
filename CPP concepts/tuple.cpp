#include <iostream>
#include <tuple> // Required for std::tuple
#include <string>

/*
 * Returning multiple values from a function by binding them in a single
 * tuple object.
 */
std::tuple<int, double, std::string> someFunction()
{
    // Creating a tuple of int, double and string
    std::tuple<int, double, std::string> result(7, 9.8, "text");

    // Returning tuple object
    return result;
}

int main()
{

    // Get tuple object from a function
    std::tuple<int, double, std::string> result = someFunction();

    // Get values from tuple

    // Get First int value from tuple
    int iVal = std::get < 0 > (result);

    // Get second double value from tuple
    double dVal = std::get < 1 > (result);

    // Get third string value from tuple
    std::string strVal = std::get < 2 > (result);

    // Print values
    std::cout << "int value = " << iVal << std::endl;
    std::cout << "double value = " << dVal << std::endl;
    std::cout << "string value = " << strVal << std::endl;

    // Get 4th int value from tuple
    // Will cause compile error because this tuple
    // has only 3 elements

    //int iVal2 = std::get<4>(result); // Compile error

    // Wrong cast will force compile time error
    // Get first value from tuple in a string

    //std::string strVal2 = std::get<0>(result); // Compile error

    int x = 1;

    // Get second double value from tuple
    // Compile error because x is not compile time contant

    //double dVal2 = std::get<x>(result);

    const int i = 1;
    // Get second double value from tuple
    double dVal3 = std::get < i > (result);

    return 0;
}