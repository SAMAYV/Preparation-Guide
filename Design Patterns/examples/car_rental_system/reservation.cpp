enum ReservationStatus {
    SCHEDULED,
    IN_USE,
    CANCELLED,
    COMPLETED
};

class Reservation {
    int reservationId;
    int vehicleId;
    User* user;
    ReservationStatus status;
    int startTime;
    int endTime;
    public:
    Reservation(int reservationId, User* user, int vehicleId, int startTime, int endTime) {
        this->reservationId = reservationId;
        this->user = user;
        this->vehicleId = vehicleId;
        this->startTime = startTime;
        this->endTime = endTime;
        this->status = ReservationStatus::SCHEDULED;
    }
    int getReservationId() {
        return this->reservationId;
    }
    int getVehicleId() {
        return this->vehicleId;
    }
};

class ReservationManager {
    // Key is reservationId
    map<int, Reservation*> reservations;
    VehicleInventoryManager* vehicleInventoryManager;
    public:
    ReservationManager(VehicleInventoryManager* vehicleInventoryManager) {
        this->reservations = map<int, Reservation*>();
        this->vehicleInventoryManager = vehicleInventoryManager;
    }
    Reservation* getReservation(int reservationId) {
        return this->reservations[reservationId];
    }
    Reservation* createReservation(User* user, int vehicleId, int startTime, int endTime) {
        int reservationId = this->generateReservationId();
        // Check if vehicle is available
        bool isAvailable = this->vehicleInventoryManager->checkAvailability(vehicleId, startTime, endTime);
        if (!isAvailable) {
            cout << "Vehicle not available in the given time slot" << endl;
            return NULL;
        }
        // Book the vehicle
        this->vehicleInventoryManager->bookVehicle(vehicleId, reservationId);
        // Create the reservation
        Reservation* reservation = new Reservation(reservationId, user, vehicleId, startTime, endTime);
        this->reservations[reservationId] = reservation;
        return reservation;
    }
    void cancelReservation(int reservationId) {
        Reservation* reservation = this->reservations.getReservation(reservationId);
        if (reservation == NULL) {
            cout << "Reservation not found" << endl;
            return;
        }
        reservation->setStatus(ReservationStatus::CANCELLED);
        // Release the vehicle
        this->vehicleInventoryManager->releaseVehicle(reservation->getVehicleId(), reservationId);
    }
    void startTrip(int reservationId) {
        Reservation* reservation = this->reservations.getReservation(reservationId);
        if (reservation == NULL) {
            cout << "Reservation not found" << endl;
            return;
        }
        reservation->setStatus(ReservationStatus::IN_USE);
    }
    void endTrip(int reservationId) {
        Reservation* reservation = this->reservations.getReservation(reservationId);
        if (reservation == NULL) {
            cout << "Reservation not found" << endl;
            return;
        }
        reservation->setStatus(ReservationStatus::COMPLETED);
        // Release the vehicle
        this->vehicleInventoryManager->releaseVehicle(reservation->getVehicleId(), reservationId);
    }
    void removeReservation(int reservationId) {
        this->reservations.erase(reservationId);
    }
};