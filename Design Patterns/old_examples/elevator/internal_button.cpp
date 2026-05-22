class InternalDispatcher {
    static InternalDispatcher* instance;
    InternalDispatcher() {
        if (instance == NULL) {
            instance = new InternalDispatcher();
        }
        return instance;
    }
    public:
    static InternalDispatcher* getInstance() {
        return instance;
    }
    void submitInternalRequest(ElevatorController* elevatorController, int destinationFloor) {
        // Here we directly submit the request to the elevator controller because we already know which elevator to use
        elevatorController->submitRequest(destinationFloor);
    }
};

class InternalButton {
    ElevatorController* elevatorController;
    public:
    InternalButton(ElevatorController* elevatorController) {
        this->elevatorController = elevatorController;
    }
    // From the internal button we can only request to go to a floor, we cannot request to go up or down
    void pressButton(int destinationFloor) {
        InternalDispatcher.getInstance()->submitInternalRequest(this->elevatorController, destinationFloor);
    }
};
