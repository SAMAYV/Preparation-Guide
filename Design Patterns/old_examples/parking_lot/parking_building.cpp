class ParkingBuilding {
    vector<ParkingFloor*> parkingFloors;
    public:
    ParkingBuilding() {
        this->parkingFloors = vector<ParkingFloor*>();
    }
    void addParkingFloor(ParkingFloor* parkingFloor) {
        this->parkingFloors.push_back(parkingFloor);
    }
    Ticket* allocateParkingSpot(Vehicle* vehicle) {
        for(ParkingFloor* parkingFloor : this->parkingFloors) {
            if (parkingFloor->hasAvailableSpot(vehicle->getType())) {
                ParkingSpot* parkingSpot = parkingFloor->park(vehicle);
                cout << "Parking allocated on floor " << parkingFloor->getFloorNumber() << " at spot " << parkingSpot->getSpotNumber() << endl;
                return new Ticket(vehicle, parkingFloor, parkingSpot);
            }
        }
        cout << "No parking available" << endl;
        return NULL;
    }
    void freeParkingSpot(Ticket* ticket) {
        ticket->getParkingFloor()->unpark(ticket->getVehicle()->getType(), ticket->getParkingSpot());
        ticket->setExitTime(time(0));
    }
};