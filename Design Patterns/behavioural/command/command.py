from abc import ABC, abstractmethod

# Receiver
class AirConditioner:
    def turnOn(self):
        print("AirConditioner: turnOn")
    
    def turnOff(self):
        print("AirConditioner: turnOff")
    
    def setTemperature(self, temperature):
        self.temperature = temperature
        print(f"AirConditioner: setTemperature to {temperature}")

class ICommand(ABC):
    @abstractmethod
    def execute(self):
        pass
    @abstractmethod
    def undo(self):
        pass

# Concrete command
class TurnACOnCommand(ICommand):
    # The command object holds a reference to the receiver.
    def __init__(self, airConditioner: AirConditioner):
        self.airConditioner = airConditioner
    
    def execute(self):
        self.airConditioner.turnOn()

    def undo(self):
        self.airConditioner.turnOff()

class TurnACOffCommand(ICommand):
    def __init__(self, airConditioner: AirConditioner):
        self.airConditioner = airConditioner
    
    def execute(self):
        self.airConditioner.turnOff()

    def undo(self):
        self.airConditioner.turnOn()

class IncreaseACTemperatureCommand(ICommand):
    def __init__(self, airConditioner: AirConditioner):
        self.airConditioner = airConditioner
    
    def execute(self):
        self.airConditioner.setTemperature(self.airConditioner.temperature + 1)

    def undo(self):
        self.airConditioner.setTemperature(self.airConditioner.temperature - 1)

# Invoker
class ACRemote:
    def __init__(self):
        self.history: list[ICommand] = []

    def pressButton(self, command: ICommand):
        print("Button pressed")
        command.execute()
        self.history.append(command)
    
    def pressUndoButton(self):
        if len(self.history) > 0:
            lastCommand: ICommand = self.history.pop()
            lastCommand.undo()
            print("Undoing last command")
        else:
            print("No commands to undo")

class Application:
    def main(self):
        ac = AirConditioner() # Receiver
        remote = ACRemote() # Invoker
        remote.pressButton(TurnACOnCommand(ac))
        remote.pressButton(IncreaseACTemperatureCommand(ac))
        remote.pressUndoButton()
        remote.pressUndoButton()

if __name__ == "__main__":
    app = Application()
    app.main()
