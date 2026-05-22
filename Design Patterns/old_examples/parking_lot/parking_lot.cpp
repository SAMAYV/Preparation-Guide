#include<bits/stdc++.h>
using namespace std;

class ParkingLot {
    ParkingBuilding* parkingBuilding;
    Entrance* entranceGate;
    Exit* exitGate;
    ParkingLot* instance;
    ParkingLot(ParkingBuilding* parkingBuilding, Entrance* entrance, Exit* exit) {
        this->parkingBuilding = parkingBuilding;
        this->entranceGate = entrance;
        this->exitGate = exit;
    }
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    public:
    ParkingLot* getInstance(ParkingBuilding* parkingBuilding, Entrance* entrance, Exit* exit) {
        if (instance == NULL) {
            instance = new ParkingLot(parkingBuilding, entrance, exit);
        }
        return instance;
    }
    Ticket* enter(Vehicle* vehicle) {
        return this->entranceGate->enter(this->parkingBuilding, vehicle);
    }
    void exit(Ticket* ticket, Payment* payment) {
        this->exitGate->exit(this->parkingBuilding, ticket, payment);
    }
};