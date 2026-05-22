from abc import ABC, abstractmethod

class VendingMachineState(ABC):
    @abstractmethod
    def insert_coin(self, machine: 'VendingMachine') -> None:
        pass
    @abstractmethod
    def select_product(self, machine: 'VendingMachine') -> None:
        pass
    @abstractmethod
    def dispense(self, machine: 'VendingMachine') -> None:
        pass

class NoCoinState(VendingMachineState):
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Coin inserted")
        machine.set_state(HasCoinState())

    def select_product(self, machine: 'VendingMachine') -> None:
        print("Insert coin first")

    def dispense(self, machine: 'VendingMachine') -> None:
        print("Insert coin first")

class HasCoinState(VendingMachineState):
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Coin already inserted")

    def select_product(self, machine: 'VendingMachine') -> None:
        print("Product selected")
        machine.set_state(DispenseState())

    def dispense(self, machine: 'VendingMachine') -> None:
        print("Select product first")

class DispenseState(VendingMachineState):
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Please wait, dispensing")

    def select_product(self, machine: 'VendingMachine') -> None:
        print("Please wait, dispensing")

    def dispense(self, machine: 'VendingMachine') -> None:
        print("Dispensing product")
        machine.set_state(NoCoinState())

class VendingMachine:
    def __init__(self):
        self._current_state: VendingMachineState = NoCoinState()

    def insert_coin(self) -> None:
        self._current_state.insert_coin(self)

    def select_product(self) -> None:
        self._current_state.select_product(self)

    def dispense(self) -> None:
        self._current_state.dispense(self)

    def set_state(self, state: VendingMachineState) -> None:
        self._current_state = state

machine = VendingMachine()
machine.select_product()  # "Insert coin first"
machine.insert_coin()     # "Coin inserted"
machine.select_product()  # "Product selected"
machine.dispense()        # "Dispensing product"
