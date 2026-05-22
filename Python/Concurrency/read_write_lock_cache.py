import threading

class Cache:
    def __init__(self):
        self._lock = threading.RLock() # reentrant lock, can be acquired multiple times by the same thread
        self._read_count = 0
        self._read_count_lock = threading.Lock()
        self._data = {}

    def get(self, key):
        with self._read_count_lock:
            self._read_count += 1
            if self._read_count == 1:
                self._lock.acquire()
        try:
            return self._data.get(key)
        finally:
            with self._read_count_lock:
                self._read_count -= 1
                if self._read_count == 0:
                    self._lock.release()

    def put(self, key, value):
        with self._lock:
            self._data[key] = value
