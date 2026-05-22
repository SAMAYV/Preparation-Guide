import threading

condition = threading.Condition()

ready = False

with condition:
    while not ready:
        condition.wait()  # Release lock and sleep
    # Condition is now true


import queue

q = queue.Queue(maxsize=100) # Blocking queue
q.put("task")   # Blocks if queue is full
t = q.get()   # Blocks if queue is empty

# Blocking queues combine a queue with condition variables to provide thread-safe producer-consumer handoff. 
# Producers call put() to add items; if full, they block. Consumers call take() to remove items; if empty, they block.