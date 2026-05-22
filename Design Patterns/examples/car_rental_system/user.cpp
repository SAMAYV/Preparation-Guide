class User {
    int userId;
    string name;
    string drivingLicense;
    public:
    User(int userId, string name, string drivingLicense="") {
        this->userId = userId;
        this->name = name;
        this->drivingLicense = drivingLicense;
    }
    int getUserId() {
        return this->userId;
    }
    string getName() {
        return this->name;
    }
    string getDrivingLicense() {
        return this->drivingLicense;
    }
    void setDrivingLicense(string drivingLicense) {
        this->drivingLicense = drivingLicense;
    }
};