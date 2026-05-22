class CashWithdrawalState : public ATMState {
    void withdrawCash(ATM* atm, int withdrawalAmountRequest) {
        CardDetails* cardDetails = atm->getCardDetails();
        if (atm->getBalance() < withdrawalAmountRequest) {
            cout << "Insufficient funds in atm" << endl;
            atm->setState(new SelectOperationState());
        }
        else if (card->getBalance() < withdrawalAmountRequest) {
            cout << "Insufficient balance in the card" << endl;
            atm->setState(new SelectOperationState());
        }
        else {
            card->deductBalance(withdrawalAmountRequest);
            atm->deductBalance(withdrawalAmountRequest);
            CashWithdrawProcessor* cashWithdrawProcessor = new FiveHundredNoteWithdrawProcessor(new HundredNoteWithdrawProcessor());
            cashWithdrawProcessor->withdrawCash(atm, withdrawalAmountRequest);
            atm->setState(new ExitState());
        }
    }
};