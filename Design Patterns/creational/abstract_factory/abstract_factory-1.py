from abc import ABC, abstractmethod

# Product
class Vehicle(ABC):
    @abstractmethod
    def drive(self):
        pass

# Abstract factory
class VehicleFactory(ABC):
    @abstractmethod
    def getVehicle(self, vehicleType) -> Vehicle:
        pass

# Abstract factory producer
class VehicleFactoryProducer():
    def getFactoryInstance(self, vehicleFamily) -> VehicleFactory:
        if vehicleFamily == "Luxury" or vehicleFamily == "Premium":
            return LuxuryVehicleFactory()
        elif vehicleFamily == "Ordinary":
            return OrdinaryVehicleFactory()
        else:
            raise Exception("Invalid vehicle family")

# Concrete factory
class LuxuryVehicleFactory(VehicleFactory):
    def getVehicle(self, vehicleType):
        if vehicleType == "Car":
            return LuxuryCar()
        elif vehicleType == "Bike":
            return LuxuryBike()
        elif vehicleType == "Truck":
            return LuxuryTruck()
        else:
            raise Exception("Invalid vehicle type")

class OrdinaryVehicleFactory(VehicleFactory):
    def getVehicle(self, vehicleType) -> Vehicle:
        if vehicleType == "Car":
            return OrdinaryCar()
        elif vehicleType == "Bike":
            return OrdinaryBike()
        elif vehicleType == "Truck":
            return OrdinaryTruck()
        else:
            raise Exception("Invalid vehicle type")

# Concrete product
class LuxuryCar(Vehicle):
    def drive(self):
        print("Driving a luxury car")

class LuxuryBike(Vehicle):
    def drive(self):
        print("Driving a luxury bike")

class LuxuryTruck(Vehicle):
    def drive(self):
        print("Driving a luxury truck")

class OrdinaryCar(Vehicle):
    def drive(self):
        print("Driving an ordinary car")

class OrdinaryBike(Vehicle):
    def drive(self):
        print("Driving an ordinary bike")

class OrdinaryTruck(Vehicle):
    def drive(self):
        print("Driving an ordinary truck")

class Application:
    def main(self):
        factory = VehicleFactoryProducer()
        luxuryFactory: VehicleFactory = factory.getFactoryInstance("Luxury")
        luxuryCar: Vehicle = luxuryFactory.getVehicle("Car")
        luxuryBike: Vehicle = luxuryFactory.getVehicle("Bike")
        luxuryCar.drive()
        luxuryBike.drive()

        ordinaryFactory: VehicleFactory = factory.getFactoryInstance("Ordinary")
        ordinaryCar: Vehicle = ordinaryFactory.getVehicle("Car")
        ordinaryCar.drive()

if __name__ == "__main__":
    app = Application()
    app.main()
