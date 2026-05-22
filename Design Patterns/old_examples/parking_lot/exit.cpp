class Exit {
    int exitGateNumber;
    CostCalculator* costCalculator;
    public:
    Exit(int exitGateNumber, CostCalculator* costCalculator) {
        this->exitGateNumber = exitGateNumber;
        this->costCalculator = costCalculator;
    }
    void exit(ParkingBuilding* parkingBuilding, Ticket* ticket, Payment* payment) {
        cout << "Vehicle " << ticket->getVehicle()->getLicensePlate() << " exiting through exit gate " << this->exitNumber << endl;
        double cost = this->costCalculator->process(ticket);
        bool isPaymentSuccessful = payment->pay(cost);
        if (!isPaymentSuccessful) {
            cout << "Payment failed. Please try again" << endl;
            return;
        }
        parkingBuilding->freeParkingSpot(ticket);
    }
};