"""
Singleton Design Pattern:

Principle:
    The basic principle behind singleton class is that every object of singleton class is the same.
    That is in case of using singleton class we can only have one instance of the object.

Use-case:
    A computer is connected to the internet through a connection object, the computer will always be
    connected to the internet through the same connection even if we disconnect and reconnect the
    connection.
"""


class Connection:
    __instance = None
    
    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            print("Creating Connection.")
            cls.__instance = super().__new__(cls)
            return cls.__instance
        else:
            print("WARNING: Theres already a connection")
            return cls.__instance

    def __init__(self):
        print("Connected to internet!")
        

def main():

    connection1 = Connection()
    connection2 = Connection()
    connection3 = Connection()
    connection4 = Connection()

    print(f"\nConnection1 is same as connection3: {connection1 is connection3}")


if __name__ == '__main__':
    main()
