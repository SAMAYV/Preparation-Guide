class Show {
    int showId;
    Movie* movie;
    int showDate;
    int showTime;
    map<int, SeatStatus> seatStatusMap;
    public:
    Show(int showId, Movie* movie, int showDate, int showTime) {
        this->showId = showId;
        this->movie = movie;
        this->showDate = showDate;
        this->showTime = showTime;
        this->bookedSeats = vector<Seat*>();
    }
    void lockSeats(vector<int> seatIds) {
        // Lock the seats for 5 minutes
        for(int seatId : seatIds) {
            this->seatStatusMap[seatId] = SeatStatus::LOCKED;
        }
    }
    void bookSeats(vector<int> seatIds) {
        for(int seatId : seatIds) {
            this->seatStatusMap[seatId] = SeatStatus::BOOKED;
        }
    }
    void releaseSeats(vector<int> seatIds) {
        for(int seatId : seatIds) {
            this->seatStatusMap[seatId] = SeatStatus::AVAILABLE;
        }
    }
};