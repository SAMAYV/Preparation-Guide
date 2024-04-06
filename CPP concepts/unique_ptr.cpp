#include <iostream>
#include <memory>

void processValue(std::unique_ptr<int> ptr)
{
    // Print information about the ptr (in our case, an int value)
    std::cout << "Integer value: " << *ptr << std::endl;
}

int main()
{
    std::unique_ptr<int> ptrObj = std::make_unique<int>(10);

    // This line would cause a compile-time error
    // Because we can not create a copy of  unique pointer
    //processValue(ptrObj);

    // We can move unique_ptr object
    processValue(std::move(ptrObj)); // This is correct

    // Once moved, unique_ptr object is empty and internally points to null
    if (!ptrObj)
    {
        std::cout << "ptrObj is now null." << std::endl;
    }

    // We can move unique_ptr object
    processValue(std::make_unique<int>(30)); // This is correct

    return 0;
}