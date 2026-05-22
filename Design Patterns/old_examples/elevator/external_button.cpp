class ElevatorScheduler {
    vector<ElevatorController*> elevatorControllers;
    ElevatorSelectionStrategy* elevatorSelectionStrategy;
    public:
    ElevatorScheduler(vector<ElevatorController*> elevatorControllers, ElevatorSelectionStrategy* elevatorSelectionStrategy) {
        this->elevatorControllers = elevatorControllers;
        this->elevatorSelectionStrategy = elevatorSelectionStrategy;
    }
    // This method will be called by the external dispatcher to assign an elevator to a floor
    ElevatorController* assignElevator(int currentFloor, ElevatorDirection direction) {
        return this->elevatorSelectionStrategy->selectElevator(this->elevatorControllers, currentFloor, direction);
    }
};

class ExternalDispatcher {
    ElevatorScheduler* elevatorScheduler;
    public:
    ExternalDispatcher(ElevatorScheduler* elevatorScheduler) {
        this->elevatorScheduler = elevatorScheduler;
    }
    void submitExternalRequest(int currentFloor, ElevatorDirection direction) {
        ElevatorController* elevatorController = this->elevatorScheduler->assignElevator(currentFloor, direction);
        // Once the elevator is assigned, we submit the request to the elevator controller
        elevatorController->submitRequest(currentFloor);
    }
};

class ExternalButton {
    ExternalDispatcher* dispatcher;
    public:
    ExternalButton(ExternalDispatcher* dispatcher) {
        this->dispatcher = dispatcher;
    }
    // From the external button we can request to go up or down, we cannot request to go to a specific floor
    void pressButton(int currentFloor, ElevatorDirection direction) {
        this->dispatcher->submitExternalRequest(currentFloor, direction);
    }
};