class MeetingScheduler {
    MeetingRoomController* meetingRoomController;
    UserController* userController;
    public:
    MeetingScheduler() {
        this->meetingRoomController = new MeetingRoomController();
        this->userController = new UserController();
    }
    void addMeetingRoom(int id, int capacity, string name) {
        this->meetingRoomController->addMeetingRoom(id, capacity, name);
    }
    void addUser(int userId, string name) {
        this->userController->addUser(userId, name);
    }
    // Book a meeting room
    Meeting* bookMeetingRoom(int roomId, int startTime, int endTime, int bookedByUserId, vector<string> attendeeUserIds) {
        cout << "Booking meeting room: " << roomId << " from " << startTime << " to " << endTime << " by " << bookedByUserId << endl;
        // Find the users
        User* bookedBy = this->userController->getUser(bookedByUserId);
        vector<User*> attendees;
        for(string attendeeUserId : attendeeUserIds) {
            User* user = this->userController->getUser(attendeeUserId);
            attendees.push_back(user);
        }
        Meeting* meeting = this->meetingRoomController->bookMeetingRoom(roomId, startTime, endTime, bookedBy, attendees);
        cout << "Meeting booked: " << meeting->getMeetingId() << endl;
        return meeting;
    }
    void sendMeetingInvite(int meetingId, int roomId, int userId) {
        cout << "Send user: " << userId << " meeting invite for meeting: " << meetingId << endl;
        User* user = this->userController->getUser(userId);
        Meeting* meeting = this->meetingRoomController->sendMeetingInvite(meetingId, roomId, user);
        cout << "Sent meeting invite to user: " << user->getUserId() << " for meeting: " << meeting->getMeetingId() << endl;
    }
    void acceptMeetingInvite(int meetingId, int roomId, int userId) {
        cout << "Meeting invite accepted by user: " << userId << " for meeting: " << meetingId << endl;
        User* user = this->userController->getUser(userId);
        Meeting* meeting = this->meetingRoomController->acceptMeetingInvite(meetingId, roomId, user);
    }
    void cancelMeeting(int meetingId, int roomId) {
        cout << "Cancelling meeting: " << meetingId << endl;
        this->meetingRoomController->cancelMeeting(meetingId, roomId);
        cout << "Meeting cancelled: " << meetingId << endl;
    }
};