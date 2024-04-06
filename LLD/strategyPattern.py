"""
Strategy Design Pattern: https://youtu.be/u8DttUrXtEw?si=pjq4JshEsBqbuwRu

Problem:
We have a base class that implements a basic functionality of a function foo. We face code duplication if we
inherit multiple classes from the base class and some of those classes over-ride the foo method identically.
This way multiple child classes redundantly implement foo which leads to code duplication and impacts
maintainability and scalability.

# Bad Approach, with code duplication:


class Vehicle:
    def drive(self):
        print("Normal Drive")


class NormalVehicle(Vehicle):
    pass


class SportyVehicle(Vehicle):
    def drive(self):
        # Code duplication with OffRoadVehicle
        print("Special Driving Capabilities.")


class OffRoadVehicle(Vehicle):
    def drive(self):
        # Code duplication with SportyVehicle
        print("Special Driving Capabilities.")


print("Normal Vehicle Driving: ")
NormalVehicle().drive()

print("Sporty Vehicle Driving: ")
SportyVehicle().drive()

print("Off Read Vehicle Driving: ")
OffRoadVehicle().drive()

"""

# Good Approach Following Strategy Pattern:

from abc import ABC, abstractmethod


class DriveStrategy(ABC):
    @abstractmethod
    def drive(self):
        pass


class NormalDrive(DriveStrategy):
    def drive(self):
        print("Normal Drive")


class SpecialDrive(DriveStrategy):
    def drive(self):
        print("Special Driving Capabilities.")


class Vehicle:
    def __init__(self, drive_strategy):
        self._drive_strategy = drive_strategy()

    @property
    def drive(self):
        return self._drive_strategy.drive


class NormalVehicle(Vehicle):
    def __init__(self):
        super().__init__(NormalDrive)


class SportyVehicle(Vehicle):
    def __init__(self):
        super().__init__(SpecialDrive)


class OffRoadVehicle(Vehicle):
    def __init__(self):
        super().__init__(SpecialDrive)


print("Normal Vehicle Driving: ")
NormalVehicle().drive()

print("Sporty Vehicle Driving: ")
SportyVehicle().drive()

print("Off Read Vehicle Driving: ")
OffRoadVehicle().drive()
