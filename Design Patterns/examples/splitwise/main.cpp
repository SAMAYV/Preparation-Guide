int main() {
    Splitwise* splitwise = new Splitwise();
    // add users
    User* user1 = splitwise->addUser("User 1");
    User* user2 = splitwise->addUser("User 2");
    User* user3 = splitwise->addUser("User 3");
    // create group
    Group* group1 = splitwise->createGroup("Group 1", user1->getId());
    // add users to group
    splitwise->addUserToGroup(user2->getId(), group1->getId());
    splitwise->addUserToGroup(user3->getId(), group1->getId());
    // add expense to group
    vector<pair<string, double>> splits1 = {new Split(user2, 50), new Split(user3, 50)};
    Expense* expense1 = splitwise->addExpenseToGroup(group1->getId(), user1->getId(), 100, ExpenseType::FOOD, ExpenseSplitType::EQUAL, splits1);
    // add non group expense
    vector<pair<string, double>> splits2 = {new Split(user2, 0, 30), new Split(user3, 0, 70)};
    Expense* expense2 = splitwise->addNonGroupExpense(user1->getId(), 300, ExpenseType::CLOTHING, ExpenseSplitType::PERCENT, splits2);
    return 0;
}