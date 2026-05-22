class ParkingSpotLookupStrategy {
    public:
    virtual ParkingSpot* findSpot(vector<ParkingSpot*> parkingSpots, Vehicle* vehicle) = 0;
};

class BasicParkingSpotLookupStrategy : public ParkingSpotLookupStrategy {
    public:
    ParkingSpot* findSpot(vector<ParkingSpot*> parkingSpots, Vehicle* vehicle) {
        for(ParkingSpot* parkingSpot : parkingSpots) {
            if (parkingSpot->isAvailable) {
                return parkingSpot;
            }
        }
        return NULL;
    }
};

class SmartParkingSpotLookupStrategy : public ParkingSpotLookupStrategy {
    public:
    ParkingSpot* findSpot(vector<ParkingSpot*> parkingSpots, Vehicle* vehicle) {
        for(ParkingSpot* parkingSpot : parkingSpots) {
            if (parkingSpot->isAvailable && parkingSpot->spotSize == vehicle->getSize()) {
                return parkingSpot;
            }
        }
        return NULL;
    }
};