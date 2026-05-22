class User {
    int userId;
    string name;
    public:
    User(int userId, string name) {
        this->userId = userId;
        this->name = name;
    }
    int getUserId() {
        return this->userId;
    }
    string getName() {
        return this->name;
    }
};

class UserService {
    map<int, User*> users;
    public:
    UserService() {
        this->users = map<int, User*>();
    }
    User* getUser(int userId) {
        // get user from db
        return this->users[userId];
    }
    void createUser(int userId, string name) {
        // create user in db
        User* user = new User(userId, name);
        this->users[user->getUserId()] = user;
    }
};

class UserController {
    UserService* userService;
    public:
    UserController() {
        this->userService = new UserService();
    }
    User* getUser(int userId) {
        return this->userService->getUser(userId);
    }
    void createUser(int userId, string name) {
        this->userService->createUser(userId, name);
    }
};