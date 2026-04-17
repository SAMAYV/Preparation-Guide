class Meta(type):
    # Actually creates the class object
    def __new__(cls, name, bases, namespace):
        print("Meta __new__")
        return super().__new__(cls, name, bases, namespace)

    # Initializes the class object
    def __init__(cls, name, bases, namespace):
        print("Meta __init__")
        super().__init__(name, bases, namespace)

    _instance = None
    # Entry point for instance creation
    def __call__(cls, *args, **kwargs):
        print("Meta __call__")
        if cls._instance is None:
            cls._instance = super().__call__(*args, **kwargs)
        return cls._instance

class MyClass(metaclass=Meta):
    # Allocates memory for instance
    def __new__(cls, *args, **kwargs):
        print("MyClass __new__")
        return super().__new__(cls)

    # Initializes the instance
    def __init__(self, x):
        print("MyClass __init__")

if __name__ == "__main__":
    print("Creating instance")
    obj = MyClass(10)