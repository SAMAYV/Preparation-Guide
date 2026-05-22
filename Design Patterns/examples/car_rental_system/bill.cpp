class Bill {
    int billId;
    int reservationId;
    int billAmount;
    bool isPaid;
    public:
    Bill(int billId, int reservationId, int billAmount) {
        this->billId = billId;
        this->reservationId = reservationId;
        this->billAmount = billAmount;
        this->isPaid = false;
    }
    int getBillId() {
        return this->billId;
    }
    int getReservationId() {
        return this->reservationId;
    }
    int getBillAmount() {
        return this->billAmount;
    }
    bool isPaid() {
        return this->isPaid;
    }
};

class BillingStrategy {
    public:
    virtual Bill* generateBill(int reservationId) = 0;
};

class DailyBillingStrategy : public BillingStrategy {
    VehicleInventoryManager* vehicleInventoryManager;
    public:
    DailyBillingStrategy(VehicleInventoryManager* vehicleInventoryManager) {
        this->vehicleInventoryManager = vehicleInventoryManager;
    }
    Bill* generateBill(int reservationId) {
        int time = reservation->getEndTime() - reservation->getStartTime();
        Vehicle* vehicle = this->vehicleInventoryManager->getVehicle(reservation->getVehicleId());
        int billAmount = time * vehicle->getHourlyRate();
        int billId = this->generateBillId();
        return new Bill(billId, reservationId, billAmount);
    }
};

class BillingManager {
    BillingStrategy* billingStrategy;
    map<int, Bill*> bills;
    public:
    BillingManager(BillingStrategy* billingStrategy) {
        this->billingStrategy = billingStrategy;
    }
    Bill* generateBill(int reservationId) {
        // Generate bill
        Bill* bill = this->billingStrategy->generateBill(reservationId);
        this->bills[bill->getBillId()] = bill;
        return bill;
    }
};