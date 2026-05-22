from abc import ABC, abstractmethod

# The "implementation" interface declares methods common to all concrete implementation classes. It doesn't have to match the
# abstraction's interface. In fact, the two interfaces can be entirely different. Typically the implementation interface
# provides only primitive operations, while the abstraction defines higher-level operations based on those primitives.
class Device(ABC):
    @abstractmethod
    def isEnabled(self) -> bool:
        pass
    @abstractmethod
    def enable(self):
        pass
    @abstractmethod
    def disable(self):
        pass
    @abstractmethod
    def getVolume(self) -> int:
        pass
    @abstractmethod
    def setVolume(self, percent):
        pass
    @abstractmethod
    def getChannel(self) -> int:
        pass
    @abstractmethod
    def setChannel(self, channel):
        pass


# All devices follow the same interface.
class Tv(Device):
    def __init__(self):
        self._enabled = False
        self._volume = 50
        self._channel = 1
    
    def isEnabled(self):
        return self._enabled
    
    def enable(self):
        self._enabled = True
        print("TV is now ON")
    
    def disable(self):
        self._enabled = False
        print("TV is now OFF")
    
    def getVolume(self):
        return self._volume
    
    def setVolume(self, percent):
        self._volume = percent
        print(f"TV volume set to {percent}")
    
    def getChannel(self):
        return self._channel
    
    def setChannel(self, channel):
        self._channel = channel
        print(f"TV channel set to {channel}")


class Radio(Device):
    def __init__(self):
        self._enabled = False
        self._volume = 30
        self._channel = 1
    
    def isEnabled(self):
        return self._enabled
    
    def enable(self):
        self._enabled = True
        print("Radio is now ON")
    
    def disable(self):
        self._enabled = False
        print("Radio is now OFF")
    
    def getVolume(self):
        return self._volume
    
    def setVolume(self, percent):
        self._volume = percent
        print(f"Radio volume set to {percent}")
    
    def getChannel(self):
        return self._channel
    
    def setChannel(self, channel):
        self._channel = channel
        print(f"Radio channel set to {channel}")


# The "abstraction" defines the interface for the "control" part of the two class hierarchies. It maintains a reference
# to an object of the "implementation" hierarchy and delegates all of the real work to this object.
class RemoteControl:
    def __init__(self, device: Device):
        self.device = device
    
    def togglePower(self):
        if self.device.isEnabled():
            self.device.disable()
        else:
            self.device.enable()
    
    def volumeDown(self):
        self.device.setVolume(self.device.getVolume() - 10)
    
    def volumeUp(self):
        self.device.setVolume(self.device.getVolume() + 10)
    
    def channelDown(self):
        self.device.setChannel(self.device.getChannel() - 1)
    
    def channelUp(self):
        self.device.setChannel(self.device.getChannel() + 1)


# You can extend classes from the abstraction hierarchy independently from device classes.
class AdvancedRemoteControl(RemoteControl):
    def mute(self):
        self.device.setVolume(0)


# Somewhere in client code.
if __name__ == "__main__":
    tv : Device = Tv()
    remote = RemoteControl(tv)
    remote.togglePower()
    remote.volumeUp()
    remote.channelUp()
    
    print("\n--- Switching to Radio ---\n")
    
    radio = Radio()
    remote = AdvancedRemoteControl(radio)
    remote.togglePower()
    remote.volumeUp()
    remote.mute()

# ---------------------------------------------------------------------------------------------------------------------------------------------

# The "implementation" interface declares methods common to all concrete implementation classes.
class Color(ABC):
    @abstractmethod
    def applyColor(self) -> str:
        pass

# Concrete implementations
class Red(Color):
    def applyColor(self):
        return "red"

class Blue(Color):
    def applyColor(self):
        return "blue"

# The "abstraction" defines the interface for the "control" part of the two class hierarchies. It maintains a reference
# to an object of the "implementation" hierarchy.
class Shape(ABC):
    def __init__(self, color: Color):
        self.color = color
    
    @abstractmethod
    def draw(self):
        pass

# Concrete abstractions
class Circle(Shape):
    def draw(self):
        print(f"Drawing Circle in {self.color.applyColor()} color")

class Square(Shape):
    def draw(self):
        print(f"Drawing Square in {self.color.applyColor()} color")

# Client code
if __name__ == "__main__":
    red = Red()
    blue = Blue()
    
    red_circle = Circle(red)
    red_circle.draw()
    
    blue_circle = Circle(blue)
    blue_circle.draw()
    
    red_square = Square(red)
    red_square.draw()
    
    blue_square = Square(blue)
    blue_square.draw()
