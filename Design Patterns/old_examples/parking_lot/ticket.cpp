class Ticket {
    Vehicle* vehicle;
    ParkingFloor* parkingFloor;
    ParkingSpot* parkingSpot;
    time_t entranceTime;
    time_t exitTime;
    public:
    Ticket(Vehicle* vehicle, ParkingFloor* parkingFloor, ParkingSpot* parkingSpot) {
        this->vehicle = vehicle;
        this->parkingFloor = parkingFloor;
        this->parkingSpot = parkingSpot;
        this->entranceTime = time(0);
    }
    ParkingFloor* getParkingFloor() {
        return this->parkingFloor;
    }
    ParkingSpot* getParkingSpot() {
        return this->parkingSpot;
    }
    Vehicle* getVehicle() {
        return this->vehicle;
    }
    void setExitTime(time_t exitTime) {
        this->exitTime = exitTime;
    }
};