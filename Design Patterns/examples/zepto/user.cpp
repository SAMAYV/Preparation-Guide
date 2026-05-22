class User {
    string id;
    string name;
    Cart* cart;
    public:
    User(string id, string name) {
        this->id = id;
        this->name = name;
        this->cart = new Cart();
    }
    string getId() {
        return this->id;
    }
    string getName() {
        return this->name;
    }
    Cart* getCart() {
        return this->cart;
    }
};

class UserController {
    map<string, User*> users;
    public:
    UserController() {
        this->users = map<string, User*>();
    }
    User* addUser(string name) {
        User* user = new User(this->generateUserId(), name);
        this->addUser(user);
        return user;
    }
    void addUser(User* user) {
        this->users[user->getId()] = user;
    }
    User* getUser(string userId) {
        return this->users[userId];
    }
};