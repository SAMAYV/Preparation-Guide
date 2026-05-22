class User {
    string id;
    string name;
    // balance sheet of user with respect to each user
    UserExpenseBalanceSheet* balanceSheet;
    public:
    User(string id, string name) {
        this->id = id;
        this->name = name;
        this->balanceSheet = new UserExpenseBalanceSheet();
    }
    string getName() {
        return this->name;
    }
    UserExpenseBalanceSheet* getBalanceSheet() {
        return this->balanceSheet;
    }
};

class UserController {
    map<string, User*> users;
    public:
    UserController() {
        this->users = map<string, User*>();
    }
    User* addUser(string userName) {
        User* user = new User(this->generateUserId(), userName);
        this->addUser(user);
        return user;
    }
    void addUser(User* user) {
        this->users[user->id] = user;
    }
    void removeUser(User* user) {
        this->users.erase(user->id);
    }
};

