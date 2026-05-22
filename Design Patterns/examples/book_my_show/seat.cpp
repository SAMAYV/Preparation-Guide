enum SeatCategory {
    GOLD,
    SILVER,
    PLATINUM
};

enum SeatStatus {
    AVAILABLE,
    BOOKED,
    LOCKED
};

class Seat {
    int seatId;
    SeatCategory category;
    public:
    Seat(int seatId, SeatCategory category) {
        this->seatId = seatId;
        this->category = category;
    }
};