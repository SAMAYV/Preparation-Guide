from abc import ABC, abstractmethod

# Strategy: Used to separate out the algorithms from the context.
class Strategy(ABC):
    @abstractmethod
    def move(self):
        pass

# Concrete strategy
class SportsCarStrategy(Strategy):
    def move(self):
        print("Moving like a sports car")

# Concrete strategy
class SUVStrategy(Strategy):
    def move(self):
        print("Moving like an SUV")

# Context
class Vehicle(ABC):
    def __init__(self, movingStrategy: Strategy):
        self.movingStrategy = movingStrategy
    
    def setStrategy(self, strategy: Strategy):
        self.movingStrategy = strategy
    
    def move(self):
        self.movingStrategy.move()

# Concrete context
class SportsCar(Vehicle):
    def move(self):
        print("SportsCar: ", end="")
        self.movingStrategy.move()

# Concrete context
class SUV(Vehicle):
    def move(self):
        print("SUV: ", end="")
        self.movingStrategy.move()

class Application:
    def main(self):
        sportsCar = SportsCar(SportsCarStrategy())
        sportsCar.move()
        suv = SUV(SUVStrategy())
        suv.move()

        sportsCar.setStrategy(SUVStrategy())
        sportsCar.move()

        suv.setStrategy(SportsCarStrategy())
        suv.move()

if __name__ == "__main__":
    app = Application()
    app.main()