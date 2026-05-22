class MeetingRoom {
    int id;
    int capacity;
    string name;
    Location* location;
    Calendar* calendar;
    MeetingController* meetingController;
    public:
    MeetingRoom(int id, int capacity, string name) {
        this->id = id;
        this->capacity = capacity;
        this->name = name;
        this->calendar = new Calendar();
        this->meetingController = new MeetingController();
    }
    MeetingController* getMeetingController() {
        return this->meetingController;
    }
    void isTimeSlotAvailable(int startTime, int endTime) {
        for(TimeInterval timeSlot : this->calendar->getBookedTimeSlots()) {
            if (timeSlot.getStartTime() <= startTime && timeSlot.getEndTime() >= endTime) {
                return false;
            }
        }
        return true;
    }
    void bookMeeting(int startTime, int endTime, User* bookedBy, vector<User*> attendees) {
        // TODO: Lock the user request to block the meeting
        if (!this->isTimeSlotAvailable(startTime, endTime)) {
            cout << "Time slot not available" << endl;
            return;
        }
        // Get the meeting object from the meeting controller
        Meeting* meeting = this->meetingController->addMeeting(this->id, startTime, endTime, bookedBy, attendees);
        // Book the meeting in the calendar
        this->calendar->addMeeting(meeting);
        // TODO: Unlock the user request to block the meeting
    }
    void cancelMeeting(int meetingId) {
        // Remove the meeting from the calendar and get the time slot
        pair<int, int> timeSlot = this->calendar->removeMeeting(meetingId);
        // Remove the meeting from the meeting controller
        this->meetingController->cancelMeeting(meetingId);
    }
};

class MeetingRoomController {
    map<int, MeetingRoom*> meetingRooms;
    public:
    MeetingRoomController() {
        this->meetingRooms = map<int, MeetingRoom*>();
    }
    MeetingRoom* addMeetingRoom(int id, int capacity, string name) {
        MeetingRoom* meetingRoom = new MeetingRoom(id, capacity, name);
        cout << "Meeting room added: " << meetingRoom->getId() << endl;
        this->meetingRooms[meetingRoom->getId()] = meetingRoom;
        return meetingRoom;
    }
    MeetingRoom* getMeetingRoom(int id) {
        return this->meetingRooms[id];
    }
    Meeting* bookMeetingRoom(int roomId, int startTime, int endTime, User* bookedBy, vector<User*> attendees) {
        MeetingRoom* meetingRoom = this->getMeetingRoom(roomId);
        if (meetingRoom == NULL) {
            cout << "Meeting room not found" << endl;
            return NULL;
        }
        if (!meetingRoom->isTimeSlotAvailable(startTime, endTime)) {
            cout << "Time slot not available" << endl;
            return NULL;
        }
        return meetingRoom->bookMeeting(startTime, endTime, bookedBy, attendees);
    }
    Meeting* sendMeetingInvite(int meetingId, int roomId, User* user) {
        MeetingRoom* meetingRoom = this->getMeetingRoom(roomId);
        return meetingRoom->getMeetingController()->sendMeetingInvite(meetingId, user);
    }
    void acceptMeetingInvite(int meetingId, int roomId, User* user) {
        MeetingRoom* meetingRoom = this->getMeetingRoom(roomId);
        return meetingRoom->getMeetingController()->acceptMeetingInvite(meetingId, user);
    }
    void cancelMeeting(int meetingId, int roomId) {
        MeetingRoom* meetingRoom = this->getMeetingRoom(roomId);
        meetingRoom->cancelMeeting(meetingId);
    }
};