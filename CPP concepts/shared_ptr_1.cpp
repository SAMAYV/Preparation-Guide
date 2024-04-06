#include <iostream>
#include <memory>

struct Sample {
    void dummyFunction() {
        std::cout << "dummyFunction called" << std::endl;
    }
};

int main() {
    std::shared_ptr<Sample> ptr = std::make_shared<Sample>();

    // This will work: using the dereference operator to call dummyFunction
    (*ptr).dummyFunction();

    // This will work: using the member access operator to call dummyFunction
    ptr->dummyFunction();

    // These lines will not compile due to lack of support for these operators:
    // ptr[0]->dummyFunction(); // shared_ptr does not support subscript operator
    // ptr++;  // shared_ptr does not support pointer arithmetic
    // ptr--;  // shared_ptr does not support pointer arithmetic

    std::shared_ptr<Sample> ptr2 = ptr; // Copy constructor increments reference count

    // This will work: comparison operators are supported
    if (ptr == ptr2) {
        std::cout << "ptr and ptr2 are equal" << std::endl;
    }

    return 0;
}