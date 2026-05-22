class Group {
    int groupId;
    string name;
    UserController* userController;
    ExpenseController* expenseController;
    public:
    Group(int groupId, string name) {
        this->groupId = groupId;
        this->name = name;
        this->userController = new UserController();
        this->expenseController = new ExpenseController();
    }
    int getGroupId() {
        return this->groupId;
    }
    string getName() {
        return this->name;
    }
    UserController* getUserController() {
        return this->userController;
    }
    ExpenseController* getExpenseController() {
        return this->expenseController;
    }
};

class GroupController {
    map<int, Group*> groups;
    public:
    GroupController() {
        this->groups = map<int, Group*>();
    }
    Group* createGroup(string groupName, User* createdBy) {
        cout << "Creating group: " << groupName << " with group id: " << groupId << " and created by: " << createdBy->getName() << endl;
        Group* group = new Group(this->generateGroupId(), name);
        group->getUserController()->addUser(createdBy);
        this->addGroup(group);
        cout << "Group created" << endl;
        return group;
    }
    void addUserToGroup(User* user, string groupId) {
        Group* group = this->getGroup(groupId);
        if (group == NULL) {
            cout << "Group not found with id: " << groupId << endl;
            return;
        }
        cout << "Adding user: " << user->getName() << " to group: " << group->getName() << endl;
        group->getUserController()->addUser(user);
        cout << "User added to group" << endl;
    }
    Expense* addExpenseToGroup(string groupId, User* paidBy, double amount, ExpenseType category, ExpenseSplitType splitType, vector<Split*> splits) {
        Group* group = this->getGroup(groupId);
        if (group == NULL) {
            cout << "Group not found with id: " << groupId << endl;
            return;
        }
        Expense* expense = group->getExpenseController()->createExpense(paidBy, amount, category, splitType, splits);
        cout << "Expense created in group: " << group->getName() << endl;
        return expense;
    }
    Group* getGroup(string groupId) {
        return this->groups[groupId];
    }
    void addGroup(Group* group) {
        this->groups[group->groupId] = group;
    }
};