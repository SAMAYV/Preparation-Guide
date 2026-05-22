class UserExpenseBalanceSheet {
    // Positive balance means you owe this user
    // Negative balance means this user owes you
    map<string, double> userToBalance;
    double totalBalance;
    public:
    UserExpenseBalanceSheet() {
        this->userToBalance = map<User*, double>();
        this->totalBalance = 0;
    }
    void updateYourBalance(double amount) {
        this->totalBalance += amount;
    }
    void updateUserToBalance(string userId, double amount) {
        this->userToBalance[userId] += amount;
    }
};

class UserBalanceSheetController {
    public:
    // update user balance sheet after creating an expense
    void updateUserBalanceSheet(User* paidBy, double totalAmount, vector<Split*> splits) {
        UserExpenseBalanceSheet* paidByBalanceSheet = paidBy->getBalanceSheet();
        // update paidByUser balance
        paidByBalanceSheet->increaseYourBalance(totalAmount);
        for (Split* split : splits) {
            User* owedUser = split->getUser();
            double amountOwe = split->getAmountOwe();
            UserExpenseBalanceSheet* owedUserBalanceSheet = owedUser->getBalanceSheet();
            // update paidByUser balance sheet
            paidByBalanceSheet->updateUserToBalance(owedUser->getId(), -amountOwe);

            if (paidBy->getId() == owedUser->getId()) {
                paidByBalanceSheet->updateYourBalance(-amountOwe);
            }
            else {
                // update owedUser balance
                owedUserBalanceSheet->updateYourBalance(-amountOwe);
                // update owedUser balance sheet
                owedUserBalanceSheet->updateUserToBalance(paidBy->getId(), amountOwe);
            }
        }
    }
};