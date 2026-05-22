int main() {
    MeetingScheduler* meetingScheduler = new MeetingScheduler();
    // Add users
    User* user1 = meetingScheduler->addUser(1, "User 1");
    User* user2 = meetingScheduler->addUser(2, "User 2");
    User* user3 = meetingScheduler->addUser(3, "User 3");

    // Add meeting rooms
    MeetingRoom* meetingRoom1 = meetingScheduler->addMeetingRoom(1, 10, "Meeting Room 1");
    MeetingRoom* meetingRoom2 = meetingScheduler->addMeetingRoom(2, 20, "Meeting Room 2");

    // Get list of available meeting rooms for startTime to endTime

    // Book a meeting room
    Meeting* meeting1 = meetingScheduler->bookMeetingRoom(meetingRoom1->getId(), 100, 110, user1->getUserId(), {user2->getUserId()});
    // Add user to meeting
    meetingScheduler->sendMeetingInvite(meeting1->getMeetingId(), meeting1->getRoomId(), user3->getUserId());
    meetingScheduler->acceptMeetingInvite(meeting1->getMeetingId(), meeting1->getRoomId(), user3->getUserId());
    // Add meeting with conflict
    Meeting* meeting2 = meetingScheduler->bookMeetingRoom(meetingRoom1->getId(), 105, 115, user2->getUserId(), {});
    return 0;
}