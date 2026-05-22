class ElevatorSelectionStrategy {
    public:
    virtual ElevatorController* selectElevator(vector<ElevatorController*> elevatorControllers, int requestedFloor, ElevatorDirection direction) = 0;
};

class LeastBusyStrategy : public ElevatorSelectionStrategy {
    public:
    ElevatorController* selectElevator(vector<ElevatorController*> elevatorControllers, int requestedFloor, ElevatorDirection direction) {
        // Here we can have a logic to select the least busy elevator
        ElevatorController* selectedElevator = NULL;
        int minRequests = INT_MAX;
        for(ElevatorController* elevatorController : elevatorControllers) {
            int load = elevatorController->upMinPQ.size() + elevatorController->downMinPQ.size();
            if(load < minRequests) {
                minRequests = load;
                selectedElevator = elevatorController;
            }
        }
        return selectedElevator;
    }
};