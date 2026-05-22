class WarehouseSelectionStrategy {
    public:
    virtual Warehouse* selectWarehouse(vector<Warehouse*> warehouses, Address* address) = 0;
};

class ClosestWarehouseStrategy : public WarehouseSelectionStrategy {
    public:
    Warehouse* selectWarehouse(vector<Warehouse*> warehouses, Address* address) {
        // Here we can have a logic to select the closest warehouse from the address
        return warehouses[0];
    }
};

class CheapestWarehouseStrategy : public WarehouseSelectionStrategy {
    public:
    Warehouse* selectWarehouse(vector<Warehouse*> warehouses, Address* address) {
        // Here we can have a logic to select the cheapest warehouse from the address
        return warehouses[0];
    }
};