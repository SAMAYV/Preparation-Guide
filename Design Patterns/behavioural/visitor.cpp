#include <iostream>
#include <vector>
using namespace std;

// Forward declarations
class SingleRoom;
class DoubleRoom;
class DeluxeRoom;

// Visitor: hosts all the operations taken out from element
class RoomVisitor {
public:
    virtual void visit(SingleRoom* room) = 0;
    virtual void visit(DoubleRoom* room) = 0;
    virtual void visit(DeluxeRoom* room) = 0;
};

// Element: object from which operations needs to be taken out
// This allows us to add new operations to existing classes without changing their structure
class RoomElement {
public:
    virtual void accept(RoomVisitor* visitor) = 0;
};

class SingleRoom : public RoomElement {
public:
    int price;
    string status;
    void accept(RoomVisitor* visitor) {
        visitor->visit(this);
    }
};

class DoubleRoom : public RoomElement {
public:
    int price;
    string status;
    void accept(RoomVisitor* visitor) {
        visitor->visit(this);
    }
};

class DeluxeRoom : public RoomElement {
public:
    int price;
    string status;
    void accept(RoomVisitor* visitor) {
        visitor->visit(this);
    }
};

// For each operation we create a visitor for all concrete elements
class RoomPriceVisitor : public RoomVisitor {
public:
    void visit(SingleRoom* room) override {
        room->price = 1000;
        cout << "Single room price: " << room->price << endl;
    }
    void visit(DoubleRoom* room) override {
        room->price = 2000;
        cout << "Double room price: " << room->price << endl;
    }
    void visit(DeluxeRoom* room) override {
        room->price = 3000;
        cout << "Deluxe room price: " << room->price << endl;
    }
};

class RoomMaintenanceVisitor : public RoomVisitor {
public:
    void visit(SingleRoom* room) override {
        room->status = "clean";
        cout << "Single room status: " << room->status << endl;
    }
    void visit(DoubleRoom* room) override {
        room->status = "clean";
        cout << "Double room status: " << room->status << endl;
    }
    void visit(DeluxeRoom* room) override {
        room->status = "clean";
        cout << "Deluxe room status: " << room->status << endl;
    }
};

int main() {
    RoomElement* single_room = new SingleRoom();
    RoomElement* double_room = new DoubleRoom();
    RoomElement* deluxe_room = new DeluxeRoom();
    
    RoomPriceVisitor* price_visitor = new RoomPriceVisitor();
    single_room->accept(price_visitor);
    double_room->accept(price_visitor);
    deluxe_room->accept(price_visitor);
    
    cout << ((SingleRoom*)single_room)->price << " " << ((DoubleRoom*)double_room)->price << " " << ((DeluxeRoom*)deluxe_room)->price << endl;
    
    RoomMaintenanceVisitor maintenance_visitor;
    single_room->accept(&maintenance_visitor);
    double_room->accept(&maintenance_visitor);
    deluxe_room->accept(&maintenance_visitor);
    
    return 0;
}

