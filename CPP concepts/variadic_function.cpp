#include <iostream>

// Function to end the recursion of variadic template function
void log() {
    // This can be empty or used to print something that marks the end of output.
}

template<typename T, typename... Args>
void log(T first, Args... args) 
{
    std::cout << first;
    if constexpr (sizeof...(args) > 0)
    {
        std::cout << " , ";
        log(args...);
    }
    else
    {
        std::cout << std::endl; // New line for the last element
    }
}

int main()
{
    // Calling log() functio with 3 arguments
    log(1 , 4.3 , "Hello");

    // Calling log() functio with 4 arguments
    log('a', "test", 78L, 5);

    // Calling log() functio with 2 arguments
    log("sample", "test");

    return 0;
}