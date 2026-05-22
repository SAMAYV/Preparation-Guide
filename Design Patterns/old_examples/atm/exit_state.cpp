class ExitState : public ATMState {
    void removeCard(ATM* atm) {
        cout << "Removing card from atm" << endl;
        atm->setState(new IdleState());
    }
};