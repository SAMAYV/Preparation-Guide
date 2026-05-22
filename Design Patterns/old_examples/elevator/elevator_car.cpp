class ElevatorCar {
    int id;
    int currentFloor;
    int nextFloorStoppage;
    ElevatorDirection movingDirection;
    Door door;
    public:
    ElevatorCar(int id) {
        this->id = id;
        this->currentFloor = 0;
        this->nextFloorStoppage = 0;
        this->movingDirection = ElevatorDirection::IDLE;
        this->door = Door();
    }
    void display() {
        cout << "Elevator " << this->id << " is at floor " << this->currentFloor << " and is going " << this->movingDirection << endl;
    }
    void moveElevator(int destinationFloor) {
        // This is a dumb object, so if command has come to go to a particular floor, it will go to that floor
        // We will open the doors, let the people in/out and then move to the next floor
        this->nextFloorStoppage = destinationFloor;
        if (this->currentFloor == this->nextFloorStoppage) {
            // If the elevator is already at the floor, we don't need to do anything
            door.openDoor(id);
            return;
        }

        int startFloor = this->currentFloor;
        door.closeDoor(id);
        if (nextFloorStoppage >= this->currentFloor) {
            this->movingDirection = ElevatorDirection::UP;
            this->display();
            for(int i = startFloor + 1; i <= destinationFloor; i++) {
                this->currentFloor = i;
                this->display();
            }
        }
        else {
            this->movingDirection = ElevatorDirection::DOWN;
            this->display();
            for(int i = startFloor - 1; i >= destinationFloor; i--) {
                this->currentFloor = i;
                this->display();
            }
        }
        door.openDoor(id);
    }
};