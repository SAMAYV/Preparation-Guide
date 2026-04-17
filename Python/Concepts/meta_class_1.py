class MainClass(type):
    def __new__(cls, name, bases, attrs):
        if 'foo' in attrs and 'bar' in attrs:
            raise TypeError(f"Class {name} cannot have both foo and bar")
        return super().__new__(cls, name, bases, attrs)

# This will raise an error
class SubClass(metaclass=MainClass):
    foo = 42
    bar = 34
