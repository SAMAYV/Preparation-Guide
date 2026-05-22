# NOTE: Singletons are not idiomatic in Python. In Python, modules themselves are singletons - they're only imported once. For shared
# resources, create a module-level instance instead of this pattern.

import threading

class DatabaseConnection:
    _instance = None
    # Declare instance attributes for type checking
    connection_string: str
    pool_size: int
    is_connected: bool
    _lock: threading.Lock = threading.Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    # Initialize instance attributes here (only runs once)
                    cls._instance.connection_string = "localhost:5432"
                    cls._instance.pool_size = 10
                    cls._instance.is_connected = False
        return cls._instance

    def query(self, sql: str) -> None:
        print(f"Executing query: {sql}")
        print(f"Using connection: {self.connection_string}")

db1 = DatabaseConnection()
db1.query("SELECT * FROM users")

# Create another instance - should be the same object
db2 = DatabaseConnection()
print(f"\ndb1 is db2: {db1 is db2}")  # True - same instance
print(f"db1 connection: {db1.connection_string}")
print(f"db2 connection: {db2.connection_string}")

# Modify attribute in one instance
db1.pool_size = 20
print(f"\nAfter modifying db1.pool_size to 20:")
print(f"db1.pool_size: {db1.pool_size}")  # 20
print(f"db2.pool_size: {db2.pool_size}")  # 20 - same object!

