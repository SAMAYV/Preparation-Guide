#include <iostream>
#include <functional>

std::function<void()> getCallback() {
    int counter = 10;
    auto func = [&counter]() mutable {
        std::cout << "Inside Lambda :: counter = " << counter << std::endl;
        counter = 20;
    };
    return func;
}

int main() {
    std::function<void()> func = getCallback();
    func();  // Undefined behavior: the original counter is gone
    return 0;
}