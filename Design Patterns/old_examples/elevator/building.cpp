class Building {
    vector<Floor*> floors;
    public:
    Building(int totalFloors, ExternalDispatcher* dispatcher) {
        for(int i = 0; i < totalFloors; i++) {
            this->floors.push_back(new Floor(i, dispatcher));
        }
    }
    Floor* getFloor(int floorNumber) {
        return this->floors[floorNumber];
    }
}