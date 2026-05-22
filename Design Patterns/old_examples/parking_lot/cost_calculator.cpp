class PricingStrategy {
    public:
    virtual double calculatePrice(Ticket* ticket) = 0;
};

class CostCalculator {
    public:
    CostCalculator(PricingStrategy* pricingStrategy) {
        this->pricingStrategy = pricingStrategy;
    }
    double process(Ticket* ticket) {
        cout << "Calculating cost using pricing strategy" << endl;
        return this->pricingStrategy->calculatePrice(ticket);
    }
};

class BasicPricingStrategy : public PricingStrategy {
    public:
    double calculatePrice(Ticket* ticket) {
        // Basic pricing logic
        return 100;
    }
};

class SmartPricingStrategy : public PricingStrategy {
    public:
    double calculatePrice(Ticket* ticket) {
        // Smart pricing logic
        // Consider time, vehicle type, etc.
        time_t entranceTime = ticket->getEntranceTime();
        time_t exitTime = ticket->getExitTime();
        int hours = (exitTime - entranceTime) / 3600;
        return hours * ticket->getParkingSpot()->getSpotSize() * 10;
    }
};