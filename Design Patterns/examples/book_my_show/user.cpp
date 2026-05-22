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