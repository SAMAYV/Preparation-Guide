import threading
import time


class SleepyWorker(threading.Thread):
    def __init__(self, seconds, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._seconds = seconds
        # Important to start execution in constructor
        # daemon is used should be set before the start
        self.start()

    def _sleep_a_little(self):
        time.sleep(self._seconds)
        print(f"Slept for {self._seconds} seconds")

    def run(self):
        self._sleep_a_little()

