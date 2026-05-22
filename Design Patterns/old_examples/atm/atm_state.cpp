class ATMState {
    virtual void insertCard(ATM* atm, CardDetails* cardDetails) = 0;
    virtual void authenticatePin(ATM* atm, int pin) = 0;
    virtual void selectOperation(ATM* atm, OperationType operationType) = 0;
    virtual void displayBalance(ATM* atm) = 0;
    virtual void removeCard(ATM* atm) = 0;
};
