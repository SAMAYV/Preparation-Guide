enum VehicleType {
    CAR,
    BIKE,
    TRUCK
};

enum VehicleStatus {
    AVAILABLE,
    BOOKED,
    MAINTENANCE
};

class Vehicle {
    VehicleType type;
    VehicleStatus status;
    int vehicleId;
    int hourlyRate;
    int distanceTravelled;
    public:
    Vehicle(int id, VehicleType type) {
        this->vehicleId = id;
        this->type = type;
        this->status = AVAILABLE;
        this->distanceTravelled = 0;
    }
    VehicleType getType() {
        return this->type;
    }
    int getHourlyRate() {
        return this->hourlyRate;
    }
    void setHourlyRate(int hourlyRate) {
        this->hourlyRate = hourlyRate;
    }
    VehicleStatus getStatus() {
        return this->status;
    }
    void setStatus(VehicleStatus status) {
        this->status = status;
    }
    int getVehicleId() {
        return this->vehicleId;
    }
};

class VehicleInventoryManager {
    // Key is vehicleId
    map<int, Vehicle*> vehicleInventory;
    // vehicleId -> bookingIds
    map<int, vector<int>> vehicleBookingIds;
    public:
    VehicleInventory() {
        this->vehicleInventory = map<int, Vehicle*>();
        this->vehicleBookingIds = map<int, vector<int>>();
    }
    bool checkAvailability(int vehicleId, int startTime, int endTime) {
        // Check if vehicle is available
        Vehicle* vehicle = this->vehicleInventory.get(vehicleId);
        if (vehicle->getStatus() == VehicleStatus::MAINTENANCE) {
            return false;
        }
        // Check if vehicle is available in the given time slot
        for(int bookingId : this->vehicleBookingIds[vehicleId]) {
            Reservation* reservation = this->reservationManager->getReservation(bookingId);
            if (reservation->getStartTime() <= startTime && reservation->getEndTime() >= endTime) {
                return false;
            }
        }
        return true;
    }
    void releaseVehicle(int vehicleId, int reservationId) {
        this->vehicleBookingIds[vehicleId].erase(reservationId);
    }
    void bookVehicle(int vehicleId, int reservationId) {
        this->vehicleBookingIds[vehicleId].push_back(reservationId);
    }
};