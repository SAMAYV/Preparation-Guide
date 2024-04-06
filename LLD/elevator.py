"""
WIP: Have to implement the run logic. Design is complete.
Elevator System Design: Elevators working concurrently

Components:
    - Lift
    - ExternalPanel
    - InternalButton
    - Elevator Management System
"""

from sortedcontainers import SortedSet
import random
import time
from enum import Enum


class Direction(Enum):
    UP = 1
    DOWN = 0


class ElevatorState(Enum):
    STATIONARY = 0
    MOVING_UP = 1
    MOVING_DOWN = 1


class ExternalButtonState(Enum):
    NOT_PRESSED = 0
    UP_PRESSED = 1
    DOWN_PRESSED = 2
    BOTH_PRESSED = 3


class Elevator:

    def __init__(self, total_serviceable_floors: int):
        self.current_floor: int = 0
        self.elevator_state: Enum = ElevatorState.STATIONARY
        self.floors_to_service: SortedSet = SortedSet()

        self.total_serviceable_floors: int = total_serviceable_floors
        self.internal_panel: InternalPanel = InternalPanel(self.total_serviceable_floors, self)

    def _move(self):
        # Core movement logic of the lift
        # cases:
        #   - wasn't moving started moving Done
        #   - crossing a non-halt floor: 1 second Done
        #   - crossing a halt floor: 3 seconds
        #       - update internal panel button state:
        #       - update external panel state for the currrent floor
        #       - Update floors to service lift
        #   - was moving, serviced the final floor, now stationary
        if self.elevator_state == ElevatorState.STATIONARY:
            if self.floors_to_service[0] > self.current_floor:
                self.elevator_state = ElevatorState.MOVING_UP
            else:
                self.elevator_state = ElevatorState.MOVING_DOWN

        elif self.elevator_state == ElevatorState.MOVING_UP:
            while self.floors_to_service or self.current_floor < self.floors_to_service[-1]:
                if self.current_floor not in self.floors_to_service:
                    time.sleep(1)
                else:
                    time.sleep(3)

        #
        else:
            pass

    def assign_floor(self, floor):
        self.floors_to_service.add(floor)
        if self.elevator_state == ElevatorState.STATIONARY:
            self._move()


class ElevatorManagementSystem:
    __management_system = None

    def __new__(cls, *args, **kwargs):
        if not cls.__management_system:
            cls.__management_system = super().__new__(cls)
        return cls.__management_system

    def __init__(self, number_of_lifts: int, total_serviceable_floors: int):
        self.number_of_lifts: int = number_of_lifts
        self.total_serviceable_floors: int = total_serviceable_floors
        self.list_of_elevators: list[Elevator] = [Elevator(self.total_serviceable_floors)
                                                  for _ in range(self.number_of_lifts)]
        self.list_of_external_buttons: list[ExternalPanel] = [ExternalPanel(self.__management_system, floor)
                                                              for floor in range(self.total_serviceable_floors)]

    def _get_elevator(self, elevator_number) -> Elevator:
        return self.list_of_elevators[elevator_number]

    def request_elevator(self, floor: int, direction: Direction):
        # Assign's an elevator: core logic for elevator allocation goes here.
        # Monkey patched a random elevator now
        elevator_number: int = random.randint(0, self.number_of_lifts - 1)
        elevator: Elevator = self._get_elevator(elevator_number)
        elevator.assign_floor(floor)
        pass


class InternalPanel:

    def __init__(self, total_serviceable_floors: int, elevator: Elevator):
        self.total_serviceable_floors: int = total_serviceable_floors
        self.elevator: Elevator = elevator
        self.buttons_pressed: list = [False] * total_serviceable_floors

    def request_floor(self, floor: int):
        self.buttons_pressed[floor] = True
        self.elevator.assign_floor(floor)
        pass

    def floor_serviced(self, floor: int):
        self.buttons_pressed[floor] = False


class ExternalPanel:

    def __init__(self, elevator_management_system: ElevatorManagementSystem, floor: int):
        self.floor: int = floor
        self.state: Enum = ExternalButtonState.NOT_PRESSED
        self.elevator_management_system: ElevatorManagementSystem = elevator_management_system

    def press_up_button(self):
        if self.state == ExternalButtonState.NOT_PRESSED:
            self.state = ExternalButtonState.UP_PRESSED
        elif self.state == ExternalButtonState.DOWN_PRESSED:
            self.state = ExternalButtonState.BOTH_PRESSED

        self.elevator_management_system.request_elevator(self.floor, Direction.UP)

    def press_down_button(self):
        if self.state == ExternalButtonState.NOT_PRESSED:
            self.state = ExternalButtonState.DOWN_PRESSED
        elif self.state == ExternalButtonState.UP_PRESSED:
            self.state = ExternalButtonState.BOTH_PRESSED

        self.elevator_management_system.request_elevator(self.floor, Direction.DOWN)

    def release_up_button(self):
        if self.state == ExternalButtonState.UP_PRESSED:
            self.state = ExternalButtonState.NOT_PRESSED
        elif self.state == ExternalButtonState.BOTH_PRESSED:
            self.state = ExternalButtonState.DOWN_PRESSED

    def release_down_button(self):
        if self.state == ExternalButtonState.DOWN_PRESSED:
            self.state = ExternalButtonState.NOT_PRESSED
        elif self.state == ExternalButtonState.BOTH_PRESSED:
            self.state = ExternalButtonState.UP_PRESSED
