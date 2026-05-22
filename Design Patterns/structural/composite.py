from abc import ABC, abstractmethod

# The component interface declares common operations for both simple and complex objects of a composition.
class Graphic(ABC):
    @abstractmethod
    def move(self, x, y):
        pass
    
    @abstractmethod
    def draw(self):
        pass


# The leaf class represents end objects of a composition. A leaf object can't have any sub-objects. Usually, it's leaf
# objects that do the actual work, while composite objects only delegate to their sub-components.
class Dot(Graphic):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def move(self, x, y):
        self.x += x
        self.y += y
    
    def draw(self):
        # Draw a dot at X and Y.
        print(f"Drawing dot at ({self.x}, {self.y})")


# All component classes can extend other components.
class Circle(Dot):
    def __init__(self, x, y, radius):
        super().__init__(x, y)
        self.radius = radius
    
    def draw(self):
        # Draw a circle at X and Y with radius R.
        print(f"Drawing circle at ({self.x}, {self.y}) with radius {self.radius}")


# The composite class represents complex components that may have children. Composite objects usually delegate the actual
# work to their children and then "sum up" the result.
class CompoundGraphic(Graphic):
    def __init__(self):
        self.children = []
    
    # A composite object can add or remove other components
    # (both simple or complex) to or from its child list.
    def add(self, child):
        # Add a child to the array of children.
        self.children.append(child)
    
    def remove(self, child):
        # Remove a child from the array of children.
        self.children.remove(child)
    
    def move(self, x, y):
        for child in self.children:
            child.move(x, y)
    
    # A composite executes its primary logic in a particular way. It traverses recursively through all its children,
    # collecting and summing up their results. Since the composite's children pass these calls to their own
    # children and so forth, the whole object tree is traversed as a result.
    def draw(self):
        # 1. For each child component:
        #     - Draw the component.
        #     - Update the bounding rectangle.
        # 2. Draw a dashed rectangle using the bounding
        # coordinates.
        print("Drawing compound graphic:")
        for child in self.children:
            child.draw()
        print("Drawing bounding rectangle")


# The client code works with all the components via their base interface. This way the client code can support simple leaf
# components as well as complex composites.
class ImageEditor:
    def __init__(self):
        self.all = None
    
    def load(self):
        self.all = CompoundGraphic()
        self.all.add(Dot(1, 2))
        self.all.add(Circle(5, 3, 10))
        # ...
    
    # Combine selected components into one complex composite component.
    def groupSelected(self, components):
        group = CompoundGraphic()
        for component in components:
            group.add(component)
            self.all.remove(component)
        self.all.add(group)
        # All components will be drawn.
        self.all.draw()


# Client code
if __name__ == "__main__":
    editor = ImageEditor()
    editor.load()
    editor.all.draw()
    
    print("\n--- Grouping components ---\n")
    
    # Create some components to group
    dot1 = Dot(10, 20)
    dot2 = Dot(30, 40)
    editor.groupSelected([dot1, dot2])