class Screen {
    int screenId;
    int totalSeats;
    vector<Seat*> seats;
    map<int, vector<Show*>> dateToShows;
    public:
    Screen(int screenId, vector<Seat*> seats) {
        this->screenId = screenId;
        this->seats = seats;
        this->totalSeats = seats.size();
    }
    void addShow(Show* show) {
        this->dateToShows[show->getDate()].push_back(show);
    }
    vector<Show*> getShows(int date) {
        return this->dateToShows[date];
    }
};