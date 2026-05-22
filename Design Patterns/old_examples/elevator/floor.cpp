class Floor {
    int floorNumber;
    ExternalButton* upButton;
    ExternalButton* downButton;
    public:
    Floor(int floorNumber, ExternalDispatcher* dispatcher) {
        this->floorNumber = floorNumber;
        this->upButton = new ExternalButton(dispatcher);
        this->downButton = new ExternalButton(dispatcher);
    }
    void pressUpButton() {
        this->upButton->pressButton(this->floorNumber, ElevatorDirection::UP);
    }
    void pressDownButton() {
        this->downButton->pressButton(this->floorNumber, ElevatorDirection::DOWN);
    }
};