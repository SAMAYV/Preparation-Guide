class Meta(type):
    def __new__(cls, class_name, bases, dct):
        dct['greet'] = lambda self: f"Hello from {class_name}!"
        return super().__new__(cls, class_name, bases, dct)

class Person(metaclass=Meta):
    def __init__(self, name):
        self.name = name

p = Person("Olivia")

print(p.greet()) # type: ignore