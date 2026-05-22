class Structure {
    public:
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void location() = 0;
    virtual string getName() = 0;
};

// Leaf
class Room : public Structure {
    string name;
    public:
    Room(string name) : name(name) {}
    void enter() {
        cout << "Entered room " << this->getName() << endl;
    }
    void exit() {
        cout << "Exited room " << this->getName() << endl;
    }
    void location() {
        cout << "Currently at room " << this->getName() << endl;
    }
    string getName() {
        return this->name;
    }
}

// Composite
class House : public Structure {
    vector<Structure*> structures;
    string address;
    public:
    House(string address) {
        this->address = address;
    }
    string getName() {
        return this->address;
    }
    int addStructure(Structure* structure) {
        this->structures.push_back(structure);
        return this->structures.size() - 1;
    }
    int getStructure(int index) {
        return this->structures.at(index);
    }
    void location() {
        cout << "House is at " << this->getName() << endl;
        for (int i = 0; i < this->structures.size(); i++) {
            this->structures[i]->getName();
        }
    }
    void enter() {
        cout << "Entered house" << endl;
    }
    void exit() {
        cout << "Exited house" << endl;
    }
};

void main() {
    House* building = new House("123 Street");
    House* floor1 = new House("123 Street - Floor 1");
    int firstFloorIndex = building->addStructure(floor1);

    Room* room1 = new Room("1F mens washroom");
    Room* room2 = new Room("1F womens washroom");
    Room* common1 = new Room("1F common room");

    int firstMens = floor1->addStructure(room1);
    int firstWomens = floor1->addStructure(room2);
    int firstCommon = floor1->addStructure(common1);

    building->enter();
    Housing* currentFloor = building->getStructure(firstFloorIndex);
    currentFloor->enter();
    Room* currentRoom = currentFloor->getStructure(firstMens);
    currentRoom->enter();
    currentRoom->exit();
    Room* currentRoom = currentFloor->getStructure(firstWomens);
    currentRoom->enter();
    currentRoom->exit();
    currentFloor->exit();
    building->exit();
    return 0;
}