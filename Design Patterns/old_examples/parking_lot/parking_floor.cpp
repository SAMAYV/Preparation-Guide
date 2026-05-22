class ParkingFloor {
    int floorNumber;
    map<VehicleType, ParkingSpotManager*> parkingSpotManagers;
    public:
    ParkingFloor(int floorNumber, map<VehicleType, ParkingSpotManager*> parkingSpotManagers) {
        this->floorNumber = floorNumber;
        this->parkingSpotManagers = parkingSpotManagers;
    }
    bool hasAvailableSpot(VehicleType vehicleType) {
        ParkingSpotManager* parkingSpotManager = this->parkingSpotManagers[vehicleType];
        return parkingSpotManager != NULL && parkingSpotManager->hasFreeSpot();
    }
    ParkingSpot* park(VehicleType vehicleType) {
        ParkingSpotManager* parkingSpotManager = this->parkingSpotManagers[vehicleType];
        if (parkingSpotManager == NULL) {
            return NULL;
        }
        return parkingSpotManager->park(vehicle);
    }
    void unpark(VehicleType vehicleType, ParkingSpot* parkingSpot) {
        ParkingSpotManager* parkingSpotManager = this->parkingSpotManagers[vehicleType];
        if (parkingSpotManager == NULL) {
            return;
        }
        parkingSpotManager->unpark(parkingSpot);
    }
};