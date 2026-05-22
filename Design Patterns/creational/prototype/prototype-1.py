from abc import ABC, abstractmethod

class Prototype(ABC):
    @abstractmethod
    def clone(self) -> 'Prototype':
        pass

class Student(Prototype):
    def __init__(self, name, roll_no, age):
        self.name = name
        self.roll_no = roll_no
        self.age = age

    # Give the clone responsibility to the child class and not the client
    def clone(self):
        return Student(self.name, self.roll_no, self.age)

class Application:
    def main(self):
        prototype = Student(name="John", roll_no=1, age=20)
        clone = prototype.clone()
        print(f"Prototype: {prototype.name}, {prototype.roll_no}, {prototype.age}")
        print(f"Clone: {clone.name}, {clone.roll_no}, {clone.age}")

if __name__ == "__main__":
    app = Application()
    app.main()
