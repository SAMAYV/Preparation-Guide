class PaymentStrategy {
    public:
    virtual bool collectPayment(User* user, double amount) = 0;
};

class UPIPaymentStrategy : public PaymentStrategy {
    public:
    bool collectPayment(User* user, double amount) {
        cout << "Collecting payment of " << amount << " from " << user->getUserId() << " via UPI" << endl;
        return true;
    }
};

class PaymentService {
    PaymentStrategy* paymentStrategy;
    public:
    PaymentService(PaymentStrategy* paymentStrategy) {
        this->paymentStrategy = paymentStrategy;
    }
    bool collectPayment(User* user, double amount) {
        return this->paymentStrategy->collectPayment(user, amount);
    }
};