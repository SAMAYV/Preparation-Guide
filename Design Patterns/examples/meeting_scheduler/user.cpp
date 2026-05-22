class User {
    int userId;
    string name;
    Calendar* calendar;
    public:
    User(int userId, string name) {
        this->userId = userId;
        this->name = name;
        this->calendar = new Calendar();
        this->notification = new Notification();
    }
    int getUserId() {
        return this->userId;
    }
    string getName() {
        return this->name;
    }
    Calendar* getCalendar() {
        return this->calendar;
    }
    void sendMeetingInvite(Meeting* meeting) {
        // Send meeting invite notification to the user
        this->notification->notifyUserForMeeting(this, meeting);
        cout << "User: " << this->name << " notified about meeting: " << meeting->getMeetingId() << endl;
    }
    void acceptMeetingInvite(Meeting* meeting) {
        // When user accepts the meeting invite
        this->calendar->addMeeting(meeting);
        cout << "Meeting invite accepted by user: " << this->name << " for meeting: " << meeting->getMeetingId() << endl;
        // Send the notification to bookedBy user that user has accepted meeting invite
        this->notification->notifyMeetingOwner(meeting->getOwner(), meeting, this);
    }
};

class UserController {
    map<int, User*> users;
    public:
    UserController() {
        this->users = map<int, User*>();
    }
    User* getUser(int userId) {
        return this->users[userId];
    }
    void addUser(int userId, string name) {
        User* user = new User(userId, name);
        this->users[user->getUserId()] = user;
    }
};