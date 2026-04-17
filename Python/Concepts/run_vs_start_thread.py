import threading
import time

def task():
    print("Start")
    time.sleep(2)
    print("End")

print("=== Case 1: Using run() - Executes in MAIN thread ===")
t1 = threading.Thread(target=task)
t1.run()  # Runs synchronously in the current thread
print("After run")

print("\n=== Case 2: Using start() - Executes in NEW thread ===")
t2 = threading.Thread(target=task)
t2.start()  # Runs asynchronously in a new thread
print("After start")

# Wait for the second thread to complete
t2.join()
print("Thread completed")
