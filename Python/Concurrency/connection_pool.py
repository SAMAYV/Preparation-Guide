import queue

class ConnectionPoolWithTimeout:
    def __init__(self, pool_size: int, timeout_sec: float):
        self._pool = queue.Queue(maxsize=pool_size)
        self._timeout = timeout_sec
        for _ in range(pool_size):
            self._pool.put(self._create_connection())

    def acquire(self):
        try:
            return self._pool.get(timeout=self._timeout)
        except queue.Empty:
            raise RuntimeError(f"No connection available within {self._timeout}s")

    def execute_query(self, query: str):
        conn = self.acquire()
        try:
            conn.execute(query)
        finally:
            self._pool.put(conn)
