class Entrance {
    int entranceGateNumber;
    public:
    Entrance(int entranceGateNumber) {
        this->entranceGateNumber = entranceGateNumber;
    }
    Ticket* enter(ParkingBuilding* parkingBuilding, Vehicle* vehicle) {
        cout << "Vehicle " << vehicle->getLicensePlate() << " entered through entrance " << this->entranceNumber << endl;
        return parkingBuilding->allocateParkingSpot(vehicle);
    }
};