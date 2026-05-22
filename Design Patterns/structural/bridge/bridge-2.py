from abc import ABC, abstractmethod

# Implementation
class BreatheImplementation(ABC):
    @abstractmethod
    def breathe(self):
        pass

# Concrete implementations
class LandBreatheImplementation(BreatheImplementation):
    def breathe(self):
        print("Breathing on land")

class WaterBreatheImplementation(BreatheImplementation):
    def breathe(self):
        print("Breathing in water")

class TreeBreatheImplementation(BreatheImplementation):
    def breathe(self):
        print("Breathing through leaves")


# Abstraction
class LivingThing(ABC):
    def __init__(self, breatheImplementation: BreatheImplementation):
        self.breatheImplementation = breatheImplementation
    @abstractmethod
    def breatheProcess(self):
        pass

class Animal(LivingThing):
    def breatheProcess(self):
        print("Animal is breathing")
        self.breatheImplementation.breathe()

class Human(LivingThing):
    def breatheProcess(self):
        print("Human is breathing")
        self.breatheImplementation.breathe()

class Plant(LivingThing):
    def breatheProcess(self):
        print("Plant is breathing")
        self.breatheImplementation.breathe()

class Application:
    def main(self):
        animal: LivingThing = Animal(LandBreatheImplementation())
        animal.breatheProcess()

        plant: LivingThing = Plant(TreeBreatheImplementation())
        plant.breatheProcess()

        human: LivingThing = Human(LandBreatheImplementation())
        human.breatheProcess()

if __name__ == "__main__":
    app = Application()
    app.main()
