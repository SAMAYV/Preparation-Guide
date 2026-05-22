class ElevatorController {
    ElevatorCar* elevatorCar;
    priority_queue<int, vector<int>, greater<int>> upMinPQ;
    priority_queue<int, vector<int>, less<int>> downMaxPQ;
    public:
    ElevatorController(ElevatorCar* elevatorCar) {
        this->elevatorCar = elevatorCar;
        this->upMinPQ = priority_queue<int, vector<int>, greater<int>>();
        this->downMaxPQ = priority_queue<int, vector<int>, less<int>>();
    }
    void submitRequest(int destinationFloor) {
        // logic to move elevator car to the floor
        cout << "Request submitted to move elevator to floor " << destinationFloor << " by elevator " << this->elevatorCar->id << endl;
        if (destinationFloor == this->elevatorCar->nextFloorStoppage) {
            // If the elevator is already going to the floor, we don't need to do anything
            return;
        
        if (destinationFloor > this->elevatorCar->nextFloorStoppage) {
            
        }
    }
};