enum VehicleSize {
    SMALL,
    MEDIUM,
    LARGE
};

enum VehicleType {
    TWOWHEELER,
    FOURWHEELER
};

class Vehicle {
    VehicleSize size;
    string licensePlate;
    public:
    Vehicle(VehicleSize size, string licensePlate) {
        this->size = size;
        this->licensePlate = licensePlate;
    }
    string getLicensePlate() {
        return this->licensePlate;
    }
    virtual void getType() = 0;
    virtual void getSize() = 0;
};

class TwoWheeler : public Vehicle {
    public:
    TwoWheeler(string licensePlate) : Vehicle(VehicleSize::SMALL, licensePlate) {}
    void getType() {
        return VehicleType::TWOWHEELER;
    }
    void getSize() {
        return VehicleSize::SMALL;
    }
};

class FourWheeler : public Vehicle {
    public:
    FourWheeler(string licensePlate) : Vehicle(VehicleSize::MEDIUM, licensePlate) {}
    void getType() {
        return VehicleType::FOURWHEELER;
    }
    void getSize() {
        return VehicleSize::MEDIUM;
    }
};
