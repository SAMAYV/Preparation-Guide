class Payment {
    public:
    virtual void pay(double amount) = 0;
};

class CashPayment : public Payment {
    public:
    void pay(double amount) {
        cout << "Amount to be paid: " << amount << endl;
        cout << "Paying by cash" << endl;
        cout << "Payment successful" << endl;
    }
};

class CardPayment : public Payment {
    public:
    void pay(double amount) {
        cout << "Amount to be paid: " << amount << endl;
        cout << "Paying by card" << endl;
        cout << "Payment successful" << endl;
    }
};
