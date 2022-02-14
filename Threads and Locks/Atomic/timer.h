#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class ScopedTimer {
  using time_point = std::chrono::high_resolution_clock::time_point;
  time_point start;

public:

  time_point now() {
    return std::chrono::high_resolution_clock::now();
  }

  ScopedTimer(): start(now()) {}
  ~ScopedTimer() {

    auto end = now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>
                (end - start).count();
    std::cout << time << "ms" << std::endl;
  }
};

#endif