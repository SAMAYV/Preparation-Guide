# The flyweight class contains a portion of the state of a tree. These fields store values that are unique for each
# particular tree. For instance, you won't find here the tree coordinates. But the texture and colors shared between many
# trees are here. Since this data is usually BIG, you'd waste a lot of memory by keeping it in each tree object. Instead, we
# can extract texture, color and other repeating data into a separate object which lots of individual tree objects can reference.
class TreeType:
    def __init__(self, name, color, texture):
        self.name = name
        self.color = color
        self.texture = texture
    
    def draw(self, canvas, x, y):
        # 1. Create a bitmap of a given type, color & texture.
        # 2. Draw the bitmap on the canvas at X and Y coords.
        print(f"Drawing {self.name} tree (color: {self.color}, texture: {self.texture}) at ({x}, {y})")


# Flyweight factory decides whether to re-use existing flyweight or to create a new object.
class TreeFactory:
    _tree_types = {}
    
    @staticmethod
    # Returns a flyweight object.
    def getTreeType(name, color, texture) -> TreeType:
        key = (name, color, texture)
        if key not in TreeFactory._tree_types:
            TreeFactory._tree_types[key] = TreeType(name, color, texture)
            print(f"Creating new TreeType: {name}")
        else:
            print(f"Reusing existing TreeType: {name}")
        return TreeFactory._tree_types[key]


# The contextual object contains the extrinsic part of the tree state. An application can create billions of these since they
# are pretty small: just two integer coordinates and one reference field.
class Tree:
    def __init__(self, x, y, type: TreeType):
        self.x = x
        self.y = y
        self.type = type
    
    def draw(self, canvas):
        self.type.draw(canvas, self.x, self.y)


# The Tree and the Forest classes are the flyweight's clients.
# You can merge them if you don't plan to develop the Tree class any further.
class Forest:
    def __init__(self):
        self.trees: list[Tree] = []
    
    def plantTree(self, x, y, name, color, texture):
        self.trees.append(Tree(x, y, TreeFactory.getTreeType(name, color, texture)))
    
    def draw(self, canvas):
        for tree in self.trees:
            tree.draw(canvas)


# Client code
if __name__ == "__main__":
    forest = Forest()
    
    # Plant many trees - notice how TreeType objects are reused
    forest.plantTree(1, 2, "Oak", "Green", "Rough")
    forest.plantTree(3, 4, "Oak", "Green", "Rough")  # Reuses TreeType
    forest.plantTree(5, 6, "Pine", "Dark Green", "Smooth")
    forest.plantTree(7, 8, "Oak", "Green", "Rough")  # Reuses TreeType
    forest.plantTree(9, 10, "Pine", "Dark Green", "Smooth")  # Reuses TreeType
    
    print("\n--- Drawing Forest ---\n")
    forest.draw("Canvas")
    
    print(f"\nTotal unique TreeTypes created: {len(TreeFactory._tree_types)}")
    print(f"Total trees planted: {len(forest.trees)}")
