class Meeting {
    int meetingId;
    int roomId;
    int startTime;
    int endTime;
    User* bookedBy;
    vector<User*> attendees;
    public:
    Meeting(int meetingId, int roomId, int startTime, int endTime, User* bookedBy, vector<User*> attendees) {
        this->meetingId = meetingId;
        this->roomId = roomId;
        this->startTime = startTime;
        this->endTime = endTime;
        this->bookedBy = bookedBy;
        this->attendees = attendees;
        // Block bookedBy user calendar for the meeting
        this->bookedBy->getCalendar()->addMeeting(meeting);
        this->notifyUsers();
    }
    void notifyUsers() {
        // Notify the users apart from the bookedBy user
        for(User* user : this->attendees) {
            user->sendMeetingInvite(this);
        }
    }
    int getMeetingId() {
        return this->meetingId;
    }
    int getRoomId() {
        return this->roomId;
    }
    User* getOwner() {
        return this->bookedBy;
    }
    void addAttendee(User* user) {
        this->attendees.push_back(user);
        // Notify the user
        user->sendMeetingInvite(this);
    }
};

class MeetingController {
    map<int, Meeting*> meetings;
    public:
    MeetingController() {
        this->meetings = map<int, Meeting*>();
    }
    Meeting* getMeeting(int meetingId) {
        return this->meetings[meetingId];
    }
    Meeting* addMeeting(int roomId, int startTime, int endTime, User* bookedBy, vector<User*> attendees) {
        Meeting* meeting = new Meeting(this->generateMeetingId(), roomId, startTime, endTime, bookedBy, attendees);
        this->meetings[meeting->getMeetingId()] = meeting;
        return meeting;
    }
    Meeting* sendMeetingInvite(int meetingId, User* user) {
        Meeting* meeting = this->getMeeting(meetingId);
        meeting->addAttendee(user);
        return meeting;
    }
    void acceptMeetingInvite(int meetingId, User* user) {
        Meeting* meeting = this->getMeeting(meetingId);
        user->acceptMeetingInvite(meeting);
    }
    void cancelMeeting(int meetingId) {
        this->meetings.erase(meetingId);
    }
};