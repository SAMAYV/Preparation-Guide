class ParkingSpotManager {
    // All parking spots in this manager are of same type
    vector<ParkingSpot*> parkingSpots;
    // It will use a strategy to find a spot
    ParkingSpotLookupStrategy* parkingSpotLookupStrategy;
    // Mutex for thread safety
    mutex mutex_;

    public:
    ParkingSpotManager(vector<ParkingSpot*> parkingSpots, ParkingSpotLookupStrategy* parkingSpotLookupStrategy) {
        this->parkingSpots = parkingSpots;
        this->parkingSpotLookupStrategy = parkingSpotLookupStrategy;
    }
    bool hasFreeSpot() {
        mutex_.lock();
        for(ParkingSpot* parkingSpot : this->parkingSpots) {
            if (parkingSpot->isAvailable) {
                mutex_.unlock();
                return true;
            }
        }
        mutex_.unlock();
        return false;
    }
    ParkingSpot* park(Vehicle* vehicle) {
        mutex_.lock();
        ParkingSpot* parkingSpot = this->parkingSpotLookupStrategy->findSpot(this->parkingSpots, vehicle);
        if (parkingSpot != NULL) {
            parkingSpot->occupySpot(vehicle);
            mutex_.unlock();
            return parkingSpot;
        }
        mutex_.unlock();
        return NULL;
    }
    void unpark(ParkingSpot* parkingSpot) {
        mutex_.lock();
        parkingSpot->freeSpot();
        mutex_.unlock();
    }
};

// It contains only two wheeler parking spots
class TwoWheelerParkingSpotManager : public ParkingSpotManager {
    public:
    TwoWheelerParkingSpotManager(ParkingSpotLookupStrategy* parkingSpotLookupStrategy) {
        // Create parking spots
        vector<ParkingSpot*> parkingSpots;
        // Create 10 two wheeler parking spots
        for(int i = 0; i < 10; i++) {
            parkingSpots.push_back(new ParkingSpot(i, VehicleSize::SMALL));
        }
        ParkingSpotManager(parkingSpots, parkingSpotLookupStrategy);
    }
};

// It contains only four wheeler parking spots
class FourWheelerParkingSpotManager : public ParkingSpotManager {
    public:
    FourWheelerParkingSpotManager(ParkingSpotLookupStrategy* parkingSpotLookupStrategy) {
        // Create parking spots
        vector<ParkingSpot*> parkingSpots;
        // Create 5 four wheeler parking spots
        for(int i = 0; i < 5; i++) {
            parkingSpots.push_back(new ParkingSpot(i, VehicleSize::MEDIUM));
        }
        ParkingSpotManager(parkingSpots, parkingSpotLookupStrategy);
    }
};