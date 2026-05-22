from abc import ABC, abstractmethod

# Using the Builder pattern makes sense only when your products
# are quite complex and require extensive configuration.
class Car:
    def __init__(self):
        self.seats = None
        self.engine = None
        self.trip_computer = None
        self.gps = None

class Manual:
    def __init__(self):
        self.seats_info : str | None = None
        self.engine_info : str | None = None
        self.trip_computer_info : str | None = None
        self.gps_info : str | None = None


# The builder interface specifies methods for creating the different parts of the product objects.
class Builder(ABC):
    @abstractmethod
    def reset(self):
        pass
    
    @abstractmethod
    def setSeats(self, seats):
        pass
    
    @abstractmethod
    def setEngine(self, engine):
        pass
    
    @abstractmethod
    def setTripComputer(self, trip_computer):
        pass
    
    @abstractmethod
    def setGPS(self, gps):
        pass


# The concrete builder classes follow the builder interface and provide specific implementations of the building steps.
class CarBuilder(Builder):
    def __init__(self):
        self.reset()
    
    def reset(self):
        self.car = Car()
    
    def setSeats(self, seats):
        self.car.seats = seats
    
    def setEngine(self, engine):
        self.car.engine = engine
    
    def setTripComputer(self, trip_computer):
        self.car.trip_computer = trip_computer
    
    def setGPS(self, gps):
        self.car.gps = gps
    
    def getProduct(self):
        product = self.car
        self.reset()
        return product


# The concrete builder classes follow the builder interface and provide specific implementations of the building steps for the concrete product.
class CarManualBuilder(Builder):
    def __init__(self):
        self.reset()
    
    def reset(self):
        self.manual = Manual()
    
    def setSeats(self, seats):
        self.manual.seats_info = f"Car has {seats} seats"
    
    def setEngine(self, engine):
        self.manual.engine_info = f"Engine: {engine}"
    
    def setTripComputer(self, trip_computer):
        self.manual.trip_computer_info = f"Trip computer: {trip_computer}"
    
    def setGPS(self, gps):
        self.manual.gps_info = f"GPS: {gps}"
    
    def getProduct(self):
        product = self.manual
        self.reset()
        return product


# The director is only responsible for executing the building steps in a particular sequence.
class Director:
    def constructSportsCar(self, builder: Builder):
        builder.reset()
        builder.setSeats(2)
        builder.setEngine("SportEngine")
        builder.setTripComputer(True)
        builder.setGPS(True)
    
    def constructSUV(self, builder: Builder):
        builder.reset()
        builder.setSeats(7)
        builder.setEngine("SUVEngine")
        builder.setTripComputer(True)
        builder.setGPS(True)

    def constructBike(self, builder: Builder):
        builder.reset()
        builder.setEngine("BikeEngine")
        builder.setTripComputer(False)


# The client code creates a builder object, passes it to the
# director and then initiates the construction process.
class Application:
    def makeCar(self):
        director = Director()
        
        # Build a sports car
        car_builder = CarBuilder()
        director.constructSportsCar(car_builder)
        car = car_builder.getProduct()
        
        # Build a manual for the sports car
        manual_builder = CarManualBuilder()
        director.constructSportsCar(manual_builder)
        manual = manual_builder.getProduct()
        
        return car, manual


if __name__ == "__main__":
    app = Application()
    car, manual = app.makeCar()
    print(f"Car built with {car.seats} seats and {car.engine} engine")
    print(f"Manual: {manual.seats_info}, {manual.engine_info}")
