class Expense {
    int expenseId;
    double amount;
    ExpenseType category;
    User* paidBy;
    ExpenseSplitType splitType;
    vector<Split*> splits;
    public:
    Expense(int expenseId, double amount, ExpenseType category, User* paidBy, ExpenseSplitType splitType, vector<Split*> splits) {
        this->expenseId = expenseId;
        this->amount = amount;
        this->category = category;
        this->paidBy = paidBy;
        this->splitType = splitType;
        this->splits = splits;
    }
};

class ExpenseController {
    map<int, Expense*> expenses;
    UserbalanceSheetController* userBalanceSheetController;
    public:
    ExpenseController() {
        this->expenses = map<int, Expense*>();
    }
    Expense* createExpense(User* paidBy, double amount, ExpenseType category, ExpenseSplitType splitType, vector<Split*> splits) {
        // validate splits
        ExpenseSplit* expenseSplit = SpliTypeFactory.getSplitType(splitType);
        expenseSplit->validate(splits, amount);
        cout << "Validated splits with split type: " << splitType << endl;
        // split amount
        vector<Split*> finalizedSplits = expenseSplit->splitAmount(splits, amount);
        // create expense
        Expense* expense = new Expense(this->generateExpenseId(), amount, category, paidBy, splitType, finalizedSplits);
        this->addExpense(expense);
        // update balance sheet
        this->userBalanceSheetController->updateUserBalanceSheet(paidBy, amount, finalizedSplits);
        return expense;
    }
    void addExpense(Expense* expense) {
        this->expenses[expense->getExpenseId()] = expense;
    }
};