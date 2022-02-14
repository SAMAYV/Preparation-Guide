#ifndef THREAD_POOL
#define THREAD_POOL

#include <vector>
#include <queue>
#include <cassert>
#include <atomic>
#include <pthread.h>

struct Executable {
  virtual void run() = 0;
  virtual ~Executable() = default;
};

class ThreadPool {
  int nthreads;
  std::atomic<bool> running{true};

  std::vector<pthread_t> thread_ids;
  std::queue<Executable*> task_queue;

  pthread_mutex_t event_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t event_cond = PTHREAD_COND_INITIALIZER;

public:
  ThreadPool(int nthreads): nthreads(nthreads) {
    assert(nthreads >= 1);
    thread_ids.resize(nthreads);
    start();
  }

  ~ThreadPool() {
    stop();
  }

  void submit(Executable* task) {
    pthread_mutex_lock(&event_mutex);
    task_queue.push(task);
    pthread_mutex_unlock(&event_mutex);

    pthread_cond_signal(&event_cond);
  }

private:

  void start() {
    for (int i = 0; i < nthreads; ++i) {
      pthread_create(&thread_ids[i], nullptr, &worker_wrapper, this);
    }
  }

  static void* worker_wrapper(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    pool->worker();
    return nullptr;
  }

  void worker() {
    while (true) {
      pthread_mutex_lock(&event_mutex);

      while (running && task_queue.empty()) {
        pthread_cond_wait(&event_cond, &event_mutex);
      }

      if (!running && task_queue.empty()) {
        pthread_mutex_unlock(&event_mutex);
        return;
      }

      auto task = task_queue.back();
      task_queue.pop();

      pthread_mutex_unlock(&event_mutex);

      if (task != nullptr) task->run();
    }
  }

  void stop() noexcept {
    running = false;
    pthread_cond_broadcast(&event_cond);

    for (pthread_t& tid : thread_ids) {
      pthread_join(tid, nullptr);
    }
  }
};

#endif