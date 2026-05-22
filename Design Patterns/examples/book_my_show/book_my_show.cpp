class BookMyShow {
    TheaterController* theaterController;
    MovieController* movieController;
    BookingController* bookingController;

    public:
    BookMyShow() {
        this->initialize();
        this->userFlow();
    }
    void initialize() {
        this->theaterController = new TheaterController();
        this->movieController = new MovieController();
        this->bookingController = new BookingController(new PaymentController(new UPIPaymentStrategy()));

        // Create movies
        Movie* movie1 = new Movie(1, "Movie 1", "English", MovieType::ACTION, 180);
        Movie* movie2 = new Movie(2, "Movie 2", "Hindi", MovieType::COMEDY, 180);
        this->movieController->addMovie(movie1, City::BANGALORE);
        this->movieController->addMovie(movie1, City::DELHI);
        this->movieController->addMovie(movie2, City::DELHI);

        // Create screens
        Screen* pvrScreen1 = new Screen(1, this->createSeats(100));
        Screen* pvrScreen2 = new Screen(2, this->createSeats(50));
        Screen* inoxScreen1 = new Screen(1, this->createSeats(100));

        // Create theatres
        Theatre* pvrTheatre = new Theatre(1, "PVR", City::BANGALORE, vector<Screen*>{pvrScreen1, pvrScreen2});
        Theatre* inoxTheatre = new Theatre(2, "INOX", City::DELHI, vector<Screen*>{inoxScreen1});
        this->theaterController->addTheatre(pvrTheatre);
        this->theaterController->addTheatre(inoxTheatre);

        // Create shows
        Show* show1 = new Show(1, movie1, 10, 120);
        Show* show2 = new Show(2, movie1, 10, 150);
        Show* show3 = new Show(3, movie2, 10, 120);

        // Add shows to screens
        pvrScreen1->addShow(show1);
        pvrScreen2->addShow(show2);
        inoxScreen1->addShow(show3);
    }
    void userFlow() {
        // Create a user
        User* user = new User(1, "User 1");
        cout << "User created: " << user->getName() << endl;

        // User selects city
        City city = City::BANGALORE;
        cout << "City selected: " << city << endl;

        // User selects date
        int selectedDate = 10;
        cout << "Date selected: " << selectedDate << endl;

        // Get movies for the city and date
        vector<Movie*> movies = this->movieController->getMovies(city, selectedDate);
        cout << "Movies available: " << endl;
        for(Movie* movie : movies) {
            cout << movie->getName() << endl;
        }

        // User selects movie
        Movie* selectedMovie = movies[0];
        cout << "Movie selected: " << selectedMovie->getName() << endl;

        // Get theatres for the movie
        vector<Theatre*> theatres = this->theaterController->getTheatres(city, selectedMovie, selectedDate);
        cout << "Theatres available: " << endl;
        for(Theatre* theatre : theatres) {
            cout << theatre->getName() << endl;
        }
        Theatre* selectedTheatre = theatres[0];
        cout << "Theatre selected: " << selectedTheatre->getName() << endl;

        // Get shows for the theatre
        vector<Show*> shows = this->theaterController->getShows(selectedTheatre, selectedMovie, selectedDate);
        cout << "Time for available shows: " << endl;
        for(Show* show : shows) {
            cout << show->getShowTime() << endl;
        }
        Show* selectedShow = shows[0];
        cout << "Selected show time: " << selectedShow->getShowTime() << endl;

        // Selected seats for the show
        vector<Seat*> seats = {Seat(1, SeatCategory::GOLD), Seat(2, SeatCategory::SILVER)};
        cout << "Seats selected: " << endl;
        for(Seat* seat : seats) {
            cout << seat->getSeatId() << endl;
        }

        // Book the ticket
        bookingController->book(user, selectedShow, seats);
        cout << "Booking successful" << endl;
        cout << "Booking ID: " << booking->getBookingId() << endl;
    }
    vector<Seat*> createSeats(int totalSeats) {
        vector<Seat*> seats;
        for(int i = 0; i < totalSeats; i++) {
            SeatCategory category = i % 3 == 0 ? SeatCategory::GOLD : i % 3 == 1 ? SeatCategory::SILVER : SeatCategory::PLATINUM;
            seats.push_back(new Seat(i, category));
        }
        return seats;
    }
}

int main() {
    BookMyShow* bookMyShow = new BookMyShow();
    return 0;
}