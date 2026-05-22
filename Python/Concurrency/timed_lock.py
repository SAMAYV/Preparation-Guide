import threading
import time
from contextlib import contextmanager

class TimedLock:
    def __init__(self):
        self.lock = threading.Lock()
        self.timer = None
    
    def acquire(self, timeout=None, auto_release_after=None):
        """
        Acquire lock with optional timeout and auto-release.
        
        Args:
            timeout: Max time to wait for lock
            auto_release_after: Automatically release after this duration
        """
        if timeout:
            acquired = self.lock.acquire(timeout=timeout)
        else:
            acquired = self.lock.acquire()
        
        if acquired and auto_release_after:
            # Schedule automatic release
            self.timer = threading.Timer(auto_release_after, self.release)
            self.timer.start()
        
        return acquired
    
    def release(self):
        """Release the lock"""
        if self.timer:
            self.timer.cancel()
            self.timer = None
        try:
            self.lock.release()
        except RuntimeError:
            pass  # Already released

# Usage
timed_lock = TimedLock()

def worker(name):
    print(f"{name} acquiring lock...")
    if timed_lock.acquire(timeout=2, auto_release_after=3):
        print(f"{name} got lock, it will auto-release in 3 seconds")
        time.sleep(5)  # Even though we sleep 5, lock releases after 3
        print(f"{name} done")
    else:
        print(f"{name} couldn't get lock")

t1 = threading.Thread(target=worker, args=("Thread-1",))
t2 = threading.Thread(target=worker, args=("Thread-2",))

t1.start()
time.sleep(0.5)
t2.start()

t1.join()
t2.join()