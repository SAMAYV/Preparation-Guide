import threading

# Simulate a database operation
class Database:
    def __init__(self):
        self.data = {}
        self.lock = threading.Lock()

    def update(self, key, value):
        self.lock.acquire()
        try:
            # Simulate a database write operation
            self.data[key] = value
            print(f"Updated {key} to {value}")
        finally:
            self.lock.release()

    def read(self, key):
        self.lock.acquire()
        try:
            # Simulate a database read operation
            return self.data.get(key, None)
        finally:
            self.lock.release()

# Database instance
db = Database()

def db_operations(thread_id):
    db.update(f"key{thread_id}", f"value{thread_id}")
    print(f"Thread-{thread_id} read: {db.read(f'key{thread_id}')}")

# Create multiple threads that access the database
threads = []
for i in range(3):
    t = threading.Thread(target=db_operations, args=(i,))
    threads.append(t)
    t.start()

for t in threads:
    t.join()