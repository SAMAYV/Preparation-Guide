class CheckBalanceState : public ATMState {
    void displayBalance(ATM* atm) {
        CardDetails* cardDetails = atm->getCardDetails();
        cout << "Displaying balance for card: " << cardDetails->getBalance() << endl;
        atm->setState(new SelectOperationState());
    }
}