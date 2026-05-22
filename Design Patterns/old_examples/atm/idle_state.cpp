class IdleState : public ATMState {
    void insertCard(ATM* atm, CardDetails* cardDetails) {
        cout << "ATM card inserted" << endl;
        atm->setCardDetails(cardDetails);
        atm->setState(new HasCardState());
    }
};