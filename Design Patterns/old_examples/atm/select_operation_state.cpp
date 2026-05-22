enum OperationType {
    CASH_WITHDRAWAL,
    CHECK_BALANCE,
    EXIT
};

class SelectOperationState : public ATMState {
    void selectOperation(ATM* atm, OperationType opType) {
        cout << "Selecting operation: " << opType << endl;
        if (opType == OperationType::CHECK_BALANCE) {
            atm->setState(new CheckBalanceState());
        }
        else if (opType == OperationType::CASH_WITHDRAWAL) {
            atm->setState(new CashWithdrawalState());
        }
        else {
            atm->setState(new ExitState());
        }
    }
};