class Notification {
    public:
    void notifyUserForMeeting(User* user, Meeting* meeting) {
        cout << "Notifying user: " << user->getName() << " for meeting: " << meeting->getMeetingId() << endl;
    }
    void notifyMeetingOwner(User* meetingOwner, Meeting* meeting, User* acceptedUser) {
        cout << "Notifying meeting owner: " << meetingOwner->getName() << " for meeting: " << meeting->getMeetingId() << " that user: " << 
        acceptedUser->getName() << " has accepted the meeting invite" << endl;
    }
};