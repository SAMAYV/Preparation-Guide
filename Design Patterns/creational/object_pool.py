from abc import ABC, abstractmethod
import threading

# Resource intensive object hence using object of this class from object pool
class DBConnection:
    mySQLConnection = None

    class DriverManager:
        @staticmethod
        def getConnection(url, username, password):
            return f"Connection: {url} {username} {password}"

    def __init__(self):
        if self.mySQLConnection is None:
            self.mySQLConnection = self.DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "username", "password")
        else:
            print("Connection already exists")
        return self.mySQLConnection
    

# Singleton class for connection pool manager
class DBConnectionPoolManager():
    _instance = None
    _lock = threading.Lock()

    def __init__(self):
        self.freeConnections = []
        self.usedConnections = []
        self.initialPoolSize = 3
        self.maxPoolSize = 6
        for i in range(self.initialPoolSize):
            self.freeConnections.append(DBConnection())

    def __new__(cls):
        raise Exception("Cannot create instance of DBConnectionPoolManager")
    
    @classmethod
    def getInstance(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super(DBConnectionPoolManager, cls).__new__(cls)
        return cls._instance
    
    # Synchronized method
    def getDBConnection(self):
        if len(self.freeConnections) == 0 and len(self.usedConnections) < self.maxPoolSize:
            self.freeConnections.append(DBConnection())
            print("New DBConnection created and added to freeConnections")
        elif len(self.freeConnections) == 0 and len(self.usedConnections) >= self.maxPoolSize:
            print("No free connections available and max pool size reached. Please wait for a connection to be released.")
            return None
        connection = self.freeConnections.pop(0)
        self.usedConnections.append(connection)
        print(f"DBConnection {connection} borrowed. Free: {len(self.freeConnections)}, Used: {len(self.usedConnections)}")
        return connection
    
    # Synchronized method
    def releaseDBConnection(self, connection):
        if connection != None:
            self.usedConnections.remove(connection)
            self.freeConnections.append(connection)
            print(f"DBConnection {connection} released. Free: {len(self.freeConnections)}, Used: {len(self.usedConnections)}")
        else:
            print("Connection is null. Cannot release.")

class Application:
    def main(self):
        poolManager = DBConnectionPoolManager.getInstance()
        connection1 = poolManager.getDBConnection()
        connection2 = poolManager.getDBConnection()
        connection3 = poolManager.getDBConnection()
        connection4 = poolManager.getDBConnection()
        connection5 = poolManager.getDBConnection()
        connection6 = poolManager.getDBConnection()
        # 7th connection will not be created as max pool size is 6
        nullConnection = poolManager.getDBConnection()
        poolManager.releaseDBConnection(connection1)
        connection7 = poolManager.getDBConnection()
        poolManager2 = DBConnectionPoolManager.getInstance()
        print(f"poolManager == poolManager2: {poolManager is poolManager2}")
