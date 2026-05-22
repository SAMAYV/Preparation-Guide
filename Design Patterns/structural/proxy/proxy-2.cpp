// Subject
class Order {
    vector<Item*> items;
    public:
    Order(vector<Item*> items) {
        this->items = items;
    }
    vector<Item*> getItems() {
        return this->items;
    }
    virtual boolean fulfillOrder(Order order) = 0;
};

class Item {
    string name;
    int quantity;
    public:
    Item(string name, int quantity) {
        this->name = name;
        this->quantity = quantity;
    }
};

// Real Subject
class Warehouse : public Order {
    map<string, int> inventory;
    string address;
    public:
    boolean fulfillOrder(Order order) {
        // check if order can be fulfilled
        for (Item* item : order.getItems()) {
            if (getInventory(item->getName()) < item->getQuantity()) {
                cout << "Insufficient inventory for " << item->getName() << endl;
                return 0;
            }
        }
        // fulfill order
        for (Item* item : order.getItems()) {
            inventory[item->getName()] -= item->getQuantity();
        }
        cout << "Order fulfilled" << endl;
        return 1;
    }
    int getInventory(string item) {
        return this->inventory[item];
    }
};

// Proxy
class OrderFulfillmentCenter : public Order {
    vector<Warehouse*> warehouses;
    string address;
    public:
    boolean fulfillOrder(Order order) {
        // fulfill order
        for (Warehouse* warehouse : warehouses) {
            cout << "Checking warehouse " << warehouse->getName() << endl;
            // check if order can be fulfilled by warehouse
            if (warehouse->fulfillOrder(order)){
                return 1;
            }
        }
        return 0;
    }
};
