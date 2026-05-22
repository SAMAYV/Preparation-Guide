from abc import ABC, abstractmethod

class Vehicle(ABC):
    @abstractmethod
    def getSeatingCapacity(self) -> int:
        pass
    @abstractmethod
    def getTankCapacity(self) -> int:
        pass

class Car(Vehicle):
    def getSeatingCapacity(self):
        return 5
    def getTankCapacity(self):
        return 50
    
class NullVehicle(Vehicle):
    def getSeatingCapacity(self):
        return 0
    def getTankCapacity(self):
        return 0

class VehicleFactory:
    def createVehicle(self, type):
        if type == "Car":
            return Car()
        else:
            return NullVehicle()

class Application:
    def main(self):
        factory = VehicleFactory()
        car = factory.createVehicle("Car")
        print(f"Car seating capacity: {car.getSeatingCapacity()}, Tank capacity: {car.getTankCapacity()}")
        
        bike = factory.createVehicle("Bike")
        print(f"Bike seating capacity: {bike.getSeatingCapacity()}, Tank capacity: {bike.getTankCapacity()}")

if __name__ == "__main__":
    app = Application()
    app.main()
