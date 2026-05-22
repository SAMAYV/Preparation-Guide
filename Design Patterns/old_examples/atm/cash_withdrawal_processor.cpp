class CashWithdrawProcessor {
    public:
    CashWithdrawProcessor* nextCashWithdrawProcessor;
    CashWithdrawProcessor(CashWithdrawProcessor* nextCashWithdrawProcessor) {
        this->nextCashWithdrawProcessor = nextCashWithdrawProcessor;
    }
    void withdrawCash(ATM* atm, int remainingAmount) {
        if (this->nextCashWithdrawProcessor != NULL) {
            this->nextCashWithdrawProcessor->withdrawCash(atm, remainingAmount);
        }
    }
};

class HundredNoteWithdrawProcessor : public CashWithdrawProcessor {
    public:
    HundredNoteWithdrawProcessor(CashWithdrawProcessor* nextCashWithdrawProcessor) : CashWithdrawProcessor(nextCashWithdrawProcessor) {

    }
    void withdrawCash(ATM* atm, int remainingAmount) {
        int requiredHundredNoteCount = remainingAmount / 100;
        int balance = remainingAmount % 100;
        int withdrawnNoteCount = 0;
        int atmHundredNoteCount = atm->getHundredNoteCount();
        if (requiredHundredNoteCount <= atmHundredNoteCount) {
            withdrawnNoteCount = requiredHundredNoteCount;
        }
        else {
            balance += (requiredHundredNoteCount - atmHundredNoteCount) * 100;
            withdrawnNoteCount = atmHundredNoteCount;
        }
        atm->deductHundredNoteCount(withdrawnNoteCount);
        cout << "Withdrawn hundred rupee notes: " << withdrawnNoteCount << " from atm" << endl;
        if (balance != 0) {
            cout << "Something went wrong" << endl;
        }
    }
};

class FiveHundredNoteWithdrawProcessor : public CashWithdrawProcessor {
    public:
    FiveHundredNoteWithdrawProcessor(CashWithdrawProcessor* nextCashWithdrawProcessor) : CashWithdrawProcessor(nextCashWithdrawProcessor) {

    }
    void withdrawCash(ATM* atm, int remainingAmount) {
        int requiredHundredNoteCount = remainingAmount / 500;
        int balance = remainingAmount % 500;
        int withdrawnNoteCount = 0;
        int atmFiveHundredNoteCount = atm->getFiveHundredNoteCount();
        if (requiredHundredNoteCount <= atmFiveHundredNoteCount) {
            withdrawnNoteCount = requiredHundredNoteCount;
        } else {
            balance += (requiredHundredNoteCount - atmFiveHundredNoteCount) * 100;
            withdrawnNoteCount = atmFiveHundredNoteCount;
        }
        atm->deductFiveHundredNoteCount(withdrawnNoteCount);
        cout << "Withdrawn five hundred rupee notes: " << withdrawnNoteCount << " from atm" << endl;
        if (balance != 0) {
            this->nextCashWithdrawProcessor->withdrawCash(balance);
        }
    }
};