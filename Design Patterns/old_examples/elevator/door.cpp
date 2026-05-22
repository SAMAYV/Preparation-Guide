class Door {
    DoorStatus status;
    public:
    Door() {
        this->status = DoorStatus::CLOSED;
    }
    void openDoor(int id) {
        this->status = DoorStatus::OPEN;
        cout << "Opening door for elevator " << id << endl;
    }
    void closeDoor(int id) {
        this->status = DoorStatus::CLOSED;
        cout << "Closing door for elevator " << id << endl;
    }
};