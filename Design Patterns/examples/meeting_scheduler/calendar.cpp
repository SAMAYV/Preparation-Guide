class TimeInterval {
    int startTime;
    int endTime;
    TimeInterval(int startTime, int endTime){
        this->startTime = startTime;
        this->endTime = endTime;
    }
    int getStartTime() {
        return this->startTime;
    }
    int getEndTime() {
        return this->endTime;
    }
};

class Calendar {
    // Time slot -> Meeting
    map<TimeInterval, Meeting*> timeToMeeting;
    public:
    Calendar() {
        this->timeToMeeting = map<TimeInterval, Meeting*>();
    }
    void addMeeting(Meeting* meeting) {
        TimeInterval t(meeting->getStartTime(), meeting->getEndTime());
        this->timeToMeeting[t] = meeting;
    }
    TimeInterval removeMeeting(int meetingId) {
        for(auto it : this->timeToMeeting) {
            if (it->second->getMeetingId() == meetingId) {
                TimeInterval timeSlot(it->first);
                this->timeToMeeting.erase(it);
                return timeSlot;
            }
        }
    }
    vector<TimeInterval> getBookedTimeSlots() {
        vector<TimeInterval> timeSlots;
        for(auto it : this->timeToMeeting) {
            timeSlots.push_back(it.first);
        }
        return timeSlots;
    }
};