class Address {
    string line1;
    string city;
    string state;
    string pincode;
    public:
    Address(string line1, string city, string state, string pincode) {
        this->line1 = line1;
        this->city = city;
        this->state = state;
        this->pincode = pincode;
    }
};

class Warehouse {
    Inventory* inventory;
    Address* address;
    public:
    Warehouse(Inventory* inventory, Address* address) {
        this->inventory = inventory;
        this->address = address;
    }
    void fulfillOrder(Order* order) {
        // check and update inventory
        for(auto item : order->getProductToQuantity()) {
            this->inventory->decreaseProductQuantity(item.first, item.second);
        }
    }
    void revertOrder(Order* order) {
        // revert inventory
        for(auto item : order->getProductToQuantity()) {
            this->inventory->increaseProductQuantity(item.first, item.second);
        }
    }
};

class WarehouseController {
    vector<Warehouse*> warehouses;
    WarehouseSelectionStrategy* warehouseSelectionStrategy;
    public:
    WarehouseController(vector<Warehouse*> warehouses, WarehouseSelectionStrategy* warehouseSelectionStrategy) {
        this->warehouses = warehouses;
        this->warehouseSelectionStrategy = warehouseSelectionStrategy;
    }
    void addWarehouse(Warehouse* warehouse) {
        this->warehouses.push_back(warehouse);
    }
    Warehouse* getWarehouse(Address* address) {
        return this->warehouseSelectionStrategy->selectWarehouse(this->warehouses, address);
    }
};