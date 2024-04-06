#include <iostream>
#include <memory>

int main()
{
    auto arr = std::make_unique<int[]>(3);

    // Initialize elements (not directly via make_unique due to limitations)
    for (int i = 0; i < 3; ++i)
    {
        arr[i] = (i + 1) * 100;
    }

    // Iterate over the array elements & Print them
    for (int i = 0; i < 3; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}