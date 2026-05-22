import threading
import time

permits = threading.Semaphore(5)  # Allow 5 concurrent operations
permits.acquire()  # Block if no permits available
try:
    print("Do work")
    time.sleep(1)
finally:
    permits.release()  # Always release, even on exception


class APIClient:
    def __init__(self):
        self._semaphore = threading.Semaphore(5)

    def make_request(self, endpoint: str):
        with self._semaphore:
            return self._http_client.get(endpoint)
