class Splitwise {
    GroupController* groupController;
    UserController* userController;
    ExpenseController* expenseController;
    public:
    Splitwise() {
        cout << "Welcome to Splitwise" << endl;
        this->groupController = new GroupController();
        this->userController = new UserController();
        this->expenseController = new ExpenseController();
    }
    User* addUser(string userName) {
        return this->userController->addUser(userName);
    }
    Group* createGroup(string groupName, string createdByUserId) {
        User* createdBy = this->userController->getUser(createdByUserId);
        if (createdBy == NULL) {
            cout << "User not found with id: " << createdByUserId << endl;
            return;
        }
        return this->groupController->createGroup(groupName, createdBy);
    }
    void addUserToGroup(string userId, string groupId) {
        User* user = this->userController->getUser(userId);
        if (user == NULL) {
            cout << "User not found with id: " << userId << endl;
            return;
        }
        this->groupController->addUserToGroup(user, groupId);
    }
    void addExpenseToGroup(string groupId, string paidByUserId, double amount, ExpenseType category, ExpenseSplitType splitType, vector<pair<string, double>> userToAmountOwe) {
        User* paidBy = this->userController->getUser(paidByUserId);
        if (paidBy == NULL) {
            cout << "User not found with id: " << paidByUserId << endl;
            return;
        }
        vector<Split*> splits;
        for (auto split : userToAmountOwe) {
            User* user = this->userController->getUser(split.first);
            if (user == NULL) {
                cout << "User not found with id: " << split.first << endl;
                return;
            } 
            splits.push_back(new Split(user, split.second));
        }
        this->groupController->addExpenseToGroup(groupId, paidBy, amount, category, splitType, splits);
    }
    void addNonGroupExpense(string paidByUserId, double amount, ExpenseType category, ExpenseSplitType splitType, vector<pair<string, double>> userToAmountOwe) {
        User* paidBy = this->userController->getUser(paidByUserId);
        if (paidBy == NULL) {
            cout << "User not found with id: " << paidByUserId << endl;
            return;
        }
        vector<Split*> splits;
        for (auto split : userToAmountOwe) {
            User* user = this->userController->getUser(split.first);
            if (user == NULL) {
                cout << "User not found with id: " << split.first << endl;
                return;
            } 
            splits.push_back(new Split(user, split.second));
        }
        this->expenseController->createExpense(paidBy, amount, category, splitType, splits);
    }
};