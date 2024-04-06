"""
Will Finish some other day.
Requirement gathering:

Components of a parking Lot:
    - Entry Gates
    - Parking Spot
    - Exit Gate

Flow of vehicles in a parking Lot:
    - Vehicle Enters Parking Lot through Entry Gate.
    - If appropriate space is present in the parking lot it collects the parking ticket.
    - If Parking lot is full entry is denied.
    - If space is present, car parks at the designated spot.
    - After some time, car exits the parking lot through the exit gate after paying the fee.
    - Once vehicle has exited a new parking spot is made available for other cars.

Entities to be considered:
    - Vehicle (Number, Type (2 wheeler/ 4 wheeler)
    - Parking ticket (Entry Time, Vehicle Number, Parking Spot)
    - Parking Spot (Spot id, isAvailable, Vehicle Type, Price, Vehicle Number) # Pricing per hour
    - Parking Lot Entry gate (Gate number : Odd Number)
        -> Find Parking spot, Assign Parking spot, Generate ticket, Deny Entry
    - Parking Lot Exit gate (Gate number : Even Number)
        -> Free up parking spot, Charge Fee

"""
from abc import ABC, abstractmethod


class ParkingSpot(ABC):

    def __init__(self, spot_id, vehicle, price, available_parking_spots):
        self._id = spot_id
        self._is_available = True
        self._price = price
        self._vehicle = vehicle
        available_parking_spots.append(self)

    def allocate(self, vehicle, available_parking_spots):
        self._is_available = False
        self._vehicle = vehicle
        available_parking_spots.remove(self)

    def deallocate(self, available_parking_spots):
        self._is_available = True
        self._vehicle = None
        available_parking_spots.append(self)


class TwoWheelerParkingSpot(ParkingSpot):
    _available_two_wheeler_parking_spots = []


class EntryGate:
    pass

