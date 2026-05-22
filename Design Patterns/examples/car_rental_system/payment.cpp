class Payment {
    int paymentId;
    int billId;
    double amountPaid;
    public:
    Payment(int paymentId, int billId, double amountPaid) {
        this->paymentId = paymentId;
        this->billId = billId;
        this->amountPaid = amountPaid;
    }
};

class PaymentStrategy {
    public:
    virtual Payment* processPayment(Bill* bill) = 0;
};

class UPIPaymentStrategy : public PaymentStrategy {
    public:
    Payment* processPayment(Bill* bill) {
        int paymentId = this->generatePaymentId();
        Payment* payment = new Payment(paymentId, bill.getBillId(), bill.getBillAmount());
        bill->setPaid(true);
        return payment;
    }
};

class PaymentManager {
    PaymentStrategy* paymentStrategy;
    map<int, Payment*> payments;
    public:
    PaymentManager(PaymentStrategy* paymentStrategy) {
        this->paymentStrategy = paymentStrategy;
        this->payments = map<int, Payment*>();
    }
    Payment* makePayment(Bill* bill) {
        Payment* payment = this->paymentStrategy->processPayment(bill);
        this->payments[payment->getPaymentId()] = payment;
        return payment;
    }
};