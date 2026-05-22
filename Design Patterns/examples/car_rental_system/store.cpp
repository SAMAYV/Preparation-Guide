class Store {
    int storeId;
    VehicleInventoryManager* inventoryManager;
    ReservationManager* reservationManager;
    Location* storeLocation;
    BillingManager* billingManager;
    PaymentManager* paymentManager;

    public:
    Store(int storeId, Location* storeLocation) {
        this->inventoryManager = new VehicleInventoryManager();
        this->reservationManager = new ReservationManager();
        this->billingManager = new BillingManager(new DailyBillingStrategy(this->inventoryManager));
        this->paymentManager = new PaymentManager(new UPIPaymentStrategy());
        this->storeId = storeId;
        this->storeLocation = storeLocation;
    }
    void addVehicle(Vehicle* vehicle) {
        this->inventory->addVehicle(vehicle);
    }
    void createReservation(User* user, Vehicle* vehicle, int startTime, int endTime) {
        this->reservationManager->createReservation(user, vehicle, startTime, endTime);
    }
    void cancelReservation(int reservationId) {
        this->reservationManager->cancelReservation(reservationId);
    }
    void startTrip(int reservationId) {
        this->reservationManager->startTrip(reservationId);
    }
    void endTrip(int reservationId) {
        this->reservationManager->endTrip(reservationId);
    }
    Bill* generateBill(int reservationId) {
        return this->billingManager->generateBill(reservationId);
    }
    Payment* makePayment(Bill* bill) {
        // Pay for the trip
        Payment* payment = this->paymentManager->makePayment(bill);
        if (!bill->isPaid()) {
            cout << "Payment failed" << endl;
            return;
        }
        this->reservationManager->removeReservation(reservationId);
        return payment;
    }
};