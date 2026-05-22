class ATM {
    ATMState* currentState;
    CardDetails* cardDetails;
    public:
    ATM() {
        this->currentState = new IdleState();
    }
    void setState(ATMState* state) {
        this->currentState = state;
    }
    // State operations
    void insertCard(CardDetails* cardDetails) {
        this->currentState->insertCard(this, cardDetails);
    }
    void authenticatePin(int pin) {
        this->currentState->authenticatePin(this, pin);
    }
    // ATM operations
    void getCardDetails() {
        return this->cardDetails;
    }
}