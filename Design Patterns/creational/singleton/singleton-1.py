import threading

# The Database class defines the `getInstance` method that lets clients access the same instance of a database connection throughout the program.
class Database:
    # The field for storing the singleton instance should be
    # declared as a class variable.
    _instance = None
    _lock = threading.Lock()

    def __init__(self):
        # Some initialization code, such as the actual connection to a database server.
        print("Database instance created")
    
    # The singleton's constructor should always be private to prevent direct construction calls with the `new` operator.
    def __new__(cls):
        raise RuntimeError('Call getInstance() instead')
    
    # The static method that controls access to the singleton instance.
    @classmethod
    def getInstance(cls):
        if cls._instance is None:
            with cls._lock:
                # Ensure that the instance hasn't yet been initialized by another thread while this one has been waiting for the lock's release.
                if cls._instance is None:
                    cls._instance = super(Database, cls).__new__(cls)
                    cls._instance.__init__()
        return cls._instance
    
    # Finally, any singleton should define some business logic which can be executed on its instance.
    def query(self, sql):
        # For instance, all database queries of an app go through this method. Therefore, you can place
        # throttling or caching logic here.
        print(f"Executing query: {sql}")


class Application:
    def main(self):
        foo = Database.getInstance()
        foo.query("SELECT ...")
        # ...
        bar = Database.getInstance()
        bar.query("SELECT ...")
        # The variable `bar` will contain the same object as the variable `foo`. Verify they are the same instance
        print(f"foo and bar are same instance: {foo is bar}")


if __name__ == "__main__":
    app = Application()
    app.main()