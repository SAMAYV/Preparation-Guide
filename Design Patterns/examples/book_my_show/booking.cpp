class Booking {
    int bookingId;
    User* user;
    Show* show;
    vector<Seat*> seats;
    public:
    Booking(int bookingId, User* user, Show* show, vector<Seat*> seats) {
        this->bookingId = bookingId;
        this->user = user;
        this->show = show;
        this->seats = seats;
    }
};

class BookingController {
    map<int, Booking*> bookings;
    PaymentController* paymentController;
    public:
    BookingController(PaymentController* paymentController) {
        this->bookings = map<int, Booking*>();
        this->paymentController = paymentController;
    }
    Booking* book(User* user, Show* show, vector<Seat*> seats) {
        // Check if seats are available
        if (!show->lockSeats(seats)) {
            cout << "Seats not available" << endl;
            return NULL;
        }
        // Collect payment
        Payment* payment = this->paymentController->collectPayment(user, show->getShowId(), show->getPrice() * seats.size());
        if (payment == NULL) {
            cout << "Payment failed" << endl;
            show->releaseSeats(seats);
            return NULL;
        } 
        // Book the seats
        show->bookSeats(seats);
        cout << "Payment successful by user " << user->getUserId() << " for show " << show->getShowId() << endl;
        // Create booking
        Booking* booking = new Booking(this->generateBookingId(), user, show, seats);
        this->bookings[bookingId] = booking;
        return booking;
    }
}