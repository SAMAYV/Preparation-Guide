#include <thread>
#include <chrono>
#include <iostream>

// Print the current thread id
std::cout << std::this_thread::get_id() << "\n";  

// Yield execution of this thread,
// allowing other threads to run
std::this_thread::yield();

using namespace std::chrono;
// Yield execution of this thread for
// at least the specified duration
std::this_thread::sleep_for(240ms);
// Yield execution of this thread until
// at least the specified time point
std::this_thread::sleep_until(steady_clock::now() + 1s);