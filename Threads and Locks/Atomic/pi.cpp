#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <random>
#include <chrono>
#include <unistd.h>

#include "thread_pool.h"
#include "timer.h"

std::atomic<int> total_points_in_circle = 0;

struct PiEstimator : public Executable {
  int num_points;
  PiEstimator(int num_points) : num_points(num_points) {}

  void run() override {
    int num_points_in_circle = 0;

    // init pseudo random number generator
    std::random_device rd; 
    std::mt19937 gen (rd());
    std::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < num_points; ++i) {
      double x = dist(gen);
      double y = dist(gen);

      double dist_sq_from_origin = x * x + y * y;
      num_points_in_circle += (dist_sq_from_origin < 1);
    }

    total_points_in_circle += num_points_in_circle;
  }
};

auto parse_arguments(int argc, char** argv) {
  --argc; 
  ++argv;

  if (argc != 3) {
    std::cout << "Requires three arguments - num_threads, total_points and points_per_job\n";
    exit(-1); 
  }

  auto num_threads = std::stoi(argv[0]);
  auto total_points = std::stol(argv[1]);
  auto points_per_job = std::stol(argv[2]);

  return std::make_tuple(num_threads, total_points, points_per_job);
}

void calculate(int num_threads, long long total_points, long long points_per_job) {
  ScopedTimer timer;

  ThreadPool service(num_threads);
  for (long long i = 0; i < total_points; i += points_per_job) {
    auto num_points = std::min(points_per_job, total_points - i);
    service.submit(new PiEstimator(num_points));
  }
}

int main(int argc, char** argv) {
  auto&& [
    num_threads, 
    total_points, 
    points_per_job 
  ] = parse_arguments(argc, argv);

  calculate(num_threads, total_points, points_per_job);

  std::cout << (4.0 * total_points_in_circle) / total_points << '\n';
  return 0;
}
