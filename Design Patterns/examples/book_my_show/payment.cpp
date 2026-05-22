class Payment {
    int paymentId;
    int userId;
    int showId;
    double amount;
    public:
    Payment(int paymentId, int userId, int showId, double amount) {
        this->paymentId = paymentId;
        this->userId = userId;
        this->showId = showId;
        this->amount = amount;
    }
};

class PaymentStrategy {
    public:
    virtual void collectPayment(User* user, double amount) = 0;
};

class UPIPaymentStrategy : public PaymentStrategy {
    public:
    void collectPayment(User* user, double amount) {
        cout << "Collecting payment of " << amount << " from " << user->getUserId() << " via UPI" << endl;
    }
};

class PaymentController {
    map<int, Payment*> payments;
    PaymentStrategy* paymentStrategy;
    public:
    PaymentController(PaymentStrategy* paymentStrategy) {
        this->payments = map<int, Payment*>();
        this->paymentStrategy = paymentStrategy;
    }
    Payment* collectPayment(User* user, int showId, double amount) {
        // Collect payment
        this->paymentStrategy->collectPayment(user, amount);
        // Create payment
        Payment* payment = new Payment(this->generatePaymentId(), user->getUserId(), show->getShowId(), amount);
        this->payments[paymentId] = payment;
        return payment;
    }
};