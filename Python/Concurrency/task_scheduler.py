import queue
from typing import Callable

class TaskScheduler:
    def __init__(self):
        self._queue = queue.Queue(maxsize=1000)

    def submit_task(self, task: Callable) -> None:
        self._queue.put(task)  # Blocks if queue is full

    def worker_loop(self) -> None:
        while True:
            task = self._queue.get()  # Blocks if queue is empty
            task()
