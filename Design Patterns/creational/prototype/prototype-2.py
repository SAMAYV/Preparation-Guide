from abc import ABC, abstractmethod

# Base prototype.
class Shape(ABC):
    # The prototype constructor. A fresh object is initialized with values from the existing object.
    def __init__(self, source=None):
        if source:
            self.x = source.x
            self.y = source.y
            self.color = source.color
        else:
            self.x = 0
            self.y = 0
            self.color = ""

    # The clone operation returns one of the Shape subclasses.
    @abstractmethod
    def clone(self) -> 'Shape':
        pass


# Concrete prototype. The cloning method creates a new object in one go by calling the constructor of the current class and
# passing the current object as the constructor's argument.
class Rectangle(Shape):
    def __init__(self, source=None):
        if source and isinstance(source, Rectangle):
            super().__init__(source)
            self.width = source.width
            self.height = source.height
        else:
            super().__init__()
            self.width = 0
            self.height = 0
    
    def clone(self):
        return Rectangle(self)


class Circle(Shape):
    def __init__(self, source=None):
        if source and isinstance(source, Circle):
            super().__init__(source)
            self.radius = source.radius
        else:
            super().__init__()
            self.radius = 0
    
    def clone(self):
        return Circle(self)


# Somewhere in the client code.
class Application:
    def __init__(self):
        self.shapes: list[Shape] = []
        
        circle = Circle()
        circle.x = 10
        circle.y = 10
        circle.radius = 20
        self.shapes.extend([circle, circle.clone()])
        
        rectangle = Rectangle()
        rectangle.width = 10
        rectangle.height = 20
        self.shapes.append(rectangle)
    
    def business_logic(self):
        # Prototype rocks because it lets you produce a copy of an object without knowing anything about its type.
        shapes_copy: list[Shape] = []
        
        # For instance, we don't know the exact elements in the shapes array. All we know is that they are all
        # shapes. But thanks to polymorphism, when we call the `clone` method on a shape the program checks its real
        # class and runs the appropriate clone method defined in that class. That's why we get proper clones
        # instead of a set of simple Shape objects.
        for s in self.shapes:
            shapes_copy.append(s.clone())
        
        # The `shapes_copy` array contains exact copies of the `shape` array's children.
        return shapes_copy


if __name__ == "__main__":
    app = Application()
    copies = app.business_logic()
    print(f"Original shapes: {len(app.shapes)}")
    print(f"Copied shapes: {len(copies)}")
