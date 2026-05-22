import threading

# https://leetcode.com/discuss/post/5950520/concurrency-handling-python-multithreadi-ej9c/

class ReadWriteLock:
    def __init__(self):
        self.readers = 0
        self.read_count_lock = threading.Lock()
        self.write_lock = threading.Lock()

    def acquire_read(self):
        with self.read_count_lock:
            self.readers += 1
            if self.readers == 1:
                self.write_lock.acquire()

    def release_read(self):
        with self.read_count_lock:
            self.readers -= 1
            if self.readers == 0:
                self.write_lock.release()

    def acquire_write(self):
        self.write_lock.acquire()

    def release_write(self):
        self.write_lock.release()

# Simulate shared resource (database)
shared_data = 0
rw_lock = ReadWriteLock()

def reader(thread_id):
    rw_lock.acquire_read()
    print(f"Reader-{thread_id} reading: {shared_data}")
    rw_lock.release_read()

def writer(thread_id):
    global shared_data
    rw_lock.acquire_write()
    shared_data += 1
    print(f"Writer-{thread_id} writing: {shared_data}")
    rw_lock.release_write()

# Create threads
threads: list[threading.Thread] = []
for i in range(2):
    t = threading.Thread(target=writer, args=(i,))
    threads.append(t)
    t.start()

for i in range(5):
    t = threading.Thread(target=reader, args=(i,))
    threads.append(t)
    t.start()

# Wait for all threads to finish
for t in threads:
    t.join()