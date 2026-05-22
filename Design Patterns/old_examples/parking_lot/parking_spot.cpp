class ParkingSpot {
    int spotNumber;
    VehicleSize spotSize;
    bool isAvailable;
    Vehicle* vehicle;

    public:
    ParkingSpot(int spotNumber, VehicleSize spotSize) {
        this->spotNumber = spotNumber;
        this->spotSize = spotSize;
        this->isAvailable = true;
    }
    void occupySpot(Vehicle* vehicle) {
        this->vehicle = vehicle;
        this->isAvailable = false;
    }
    void freeSpot() {
        this->vehicle = NULL;
        this->isAvailable = true;
    }
};