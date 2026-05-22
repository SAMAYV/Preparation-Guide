class HasCardState : public ATMState {
    void insertCard(ATM* atm) {
        cout << "ATM card already inserted, please remove the existing card to insert a new card" << endl;
    }
    void authenticatePin(ATM* atm, int pin) {
        CardDetails* cardDetails = atm->getCardDetails();
        cout << "Authenticating card: " << cardDetails->getCardNumber() << " against pin: " << pin << endl;
        atm->setState(new SelectOperationState());
    }
};