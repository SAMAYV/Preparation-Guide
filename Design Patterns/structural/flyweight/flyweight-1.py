from abc import ABC, abstractmethod

class IRobot(ABC):
    @abstractmethod
    def display(self, x, y):
        pass

class Sprite:
    def __init__(self):
        pass

class HumanoidRobot(IRobot):
    def __init__(self, type):
        self._type = type
        self._sprite = Sprite()

    def getType(self):
        return self._type
    
    def getSprite(self):
        return self._sprite
    
    def display(self, x, y):
        print(f"Displaying {self.getType()} humanoid robot at {x}, {y}")

class RoboticDog(IRobot):
    def __init__(self, type):
        self._type = type
        self._sprite = Sprite()

    def getType(self):
        return self._type
    
    def getSprite(self):
        return self._sprite
    
    def display(self, x, y):
        print(f"Displaying {self.getType()} robotic dog at {x}, {y}")

# Flyweight factory class - creates and manages flyweight objects
class RobotFactory:
    roboticObjectCache = {}

    @staticmethod
    def createRobot(type) -> IRobot:
        if type in RobotFactory.roboticObjectCache:
            return RobotFactory.roboticObjectCache[type]
        else:
            if type == "Humanoid" or type == "humanoid":
                if type == "Humanoid":
                    robot = HumanoidRobot(type)
                else:
                    robot = RoboticDog(type)
                RobotFactory.roboticObjectCache[type] = robot
                return robot
            else:
                raise Exception("Invalid robot type: " + type)

    def getTotalRobotsCreated(self):
        return len(self.roboticObjectCache)

class RoboticGameSimulator:
    def main(self):
        factory = RobotFactory()
        robot1 = factory.createRobot("Humanoid")
        robot1.display(1, 2)

        robot2 = factory.createRobot("RoboticDog")
        robot2.display(3, 4)

        robot3 = factory.createRobot("Humanoid")
        robot3.display(5, 6)

        robot4 = factory.createRobot("RoboticDog")
        robot4.display(7, 8)

        print(f"Total robots created: {factory.getTotalRobotsCreated()}")

if __name__ == "__main__":
    simulator = RoboticGameSimulator()
    simulator.main()

# -----------------------------------------------------------------------------------------------------------------------------

class ILetter(ABC):
    @abstractmethod
    def display(self, row, col):
        pass

# Flyweight object
class DocumentLetter(ILetter):
    def __init__(self, character, font, size):
        self._character = character
        self._font = font
        self._size = size
    
    def display(self, row, col):
        print(f"Displaying character {self._character} at {row}, {col}")

class LetterFactory:
    letterCache = {}
    def getLetter(self, character, font, size) -> ILetter:
        key = (character, font, size)
        if key in LetterFactory.letterCache:
            return LetterFactory.letterCache[key]
        else:
            letter = DocumentLetter(character, font, size)
            LetterFactory.letterCache[key] = letter
            return letter

class TextEditor:
    def main(self):
        factory = LetterFactory()
        letter1 = factory.getLetter("H", "Arial", 12)
        letter1.display(1, 2)

        letter2 = factory.getLetter("e", "Arial", 12)
        letter2.display(1, 3)

        letter3 = factory.getLetter("H", "Arial", 12)
        letter3.display(1, 4)

if __name__ == "__main__":
    editor = TextEditor()
    editor.main()
