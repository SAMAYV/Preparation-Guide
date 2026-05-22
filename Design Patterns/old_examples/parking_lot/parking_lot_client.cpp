class ParkingLotClient {
    void run() {
        ParkingBuilding* parkingBuilding = new ParkingBuilding();
        Entrance* entranceGate = new Entrance(1);
        Exit* exitGate = new Exit(1, new CostCalculator(new BasicPricingStrategy()));
        parkingBuilding->addParkingFloor(new ParkingFloor(1, map<VehicleType, ParkingSpotManager*>{
            {VehicleType::TWOWHEELER, new TwoWheelerParkingSpotManager(new SmartParkingSpotLookupStrategy())},
            {VehicleType::FOURWHEELER, new FourWheelerParkingSpotManager(new BasicParkingSpotLookupStrategy())}
        }));
        parkingBuilding->addParkingFloor(new ParkingFloor(2, map<VehicleType, ParkingSpotManager*>{
            {VehicleType::TWOWHEELER, new TwoWheelerParkingSpotManager(new BasicParkingSpotLookupStrategy())},
            {VehicleType::FOURWHEELER, new FourWheelerParkingSpotManager(new SmartParkingSpotLookupStrategy())}
        }));

        ParkingLot* parkingLot = ParkingLot::getInstance(parkingBuilding, entranceGate, exitGate);
        cout << "Welcome to Parking Lot" << endl;

        Vehicle* vehicle = new TwoWheeler("KA-01-1234");
        Ticket* ticket = parkingLot->enter(vehicle);
        cout << "Vehicle parked" << endl;

        cout << "Vehicle leaving parking lot" << endl;
        Payment* payment = new CashPayment();
        parkingLot->exit(ticket, payment);
        cout << "Vehicle left" << endl;
    }
}

int main() {
    ParkingLotClient client;
    client.run();
    return 0;
}