class VehicleRentalSystem {
    map<int, Store*> stores;
    map<int, User*> users;
    public:
    VehicleRentalSystem() {
        this->stores = map<int, Store*>();
        this->users = map<int, User*>();
    }
    void addUser(User* user) {
        this->users[user->getUserId()] = user;
    }
    void addStore(Store* store) {
        this->stores[store->getStoreId()] = store;
    }
    User* getUser(int userId) {
        return this->users[userId];
    }
    Store* getStore(int storeId) {
        return this->stores[storeId];
    }
    void removeUser(int userId) {
        this->users.erase(userId);
    }
    void removeStore(int storeId) {
        this->stores.erase(storeId);
    }
};

int main() {
    VehicleRentalSystem* system = new VehicleRentalSystem();
    
    // 1. Create users
    User* user1 = new User(1, "User 1");
    User* user2 = new User(2, "User 2");
    system->addUser(user1);
    system->addUser(user2);

    // 2. Create stores
    Store* store = new Store(1, new Location(201011, "Bangalore", "Karnataka"));
    system->addStore(store);

    // 3. Add vehicles to store
    Vehicle* car = new Vehicle(1, CAR);
    car->setHourlyRate(10);
    store->addVehicle(car);
    Vehicle* bike = new Vehicle(2, BIKE);
    bike->setHourlyRate(5);
    store->addVehicle(bike);
    Vehicle* truck = new Vehicle(3, TRUCK);
    truck->setHourlyRate(20);
    store->addVehicle(truck);

    // 4. Create reservations
    Store selectedStore = system->getStore(1);
    Reservation* reservation = selectedStore->createReservation(user1, car, 10, 11);

    // 5. User starts the trip
    selectedStore->startTrip(reservation->getReservationId());

    // 6. User ends the trip
    selectedStore->endTrip(reservation->getReservationId());

    // 6. Generate bill
    Bill* bill = selectedStore->generateBill(reservation->getReservationId());

    cout << "BILL RECEIPT: " << endl;
    cout << "Reservation ID: " << reservation->getReservationId() << endl;
    cout << "Bill ID: " << bill->getBillId() << endl;
    cout << "Bill Amount: " << bill->getBillAmount() << endl;

    // 7. User pays for the trip
    Payment* payment = selectedStore->makePayment(bill);

    cout << "PAYMENT RECEIPT: " << endl;
    cout << "Reservation ID: " << reservation->getReservationId() << endl;
    cout << "Bill ID: " << bill->getBillId() << endl;
    cout << "Payment ID: " << payment->getPaymentId() << endl;
    cout << "Amount Paid: " << payment->getAmountPaid() << endl;
    cout << "Thank you for using our service" << endl;

    return 0;
}