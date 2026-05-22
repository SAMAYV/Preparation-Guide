class Theatre {
    int theatreId;
    string name;
    City city;
    vector<Screen*> screens;
    public:
    Theatre(int theatreId, string name, City city, vector<Screen*> screens) {
        this->theatreId = theatreId;
        this->name = name;
        this->city = city;
        this->screens = screens;
    }
    City getCity() {
        return this->city;
    }
    vector<Screen*> getScreens() {
        return this->screens;
    }
};

class TheaterController {
    map<City, vector<Theatre*>> cityToTheatres;
    public:
    TheaterController() {
        this->cityToTheatres = map<City, vector<Theatre*>>();
    }
    void addTheatre(Theatre* theatre) {
        this->cityToTheatres[theatre->getCity()].push_back(theatre);
    }
    vector<Movie*> getMovies(City city, int date) {
        vector<Theatre*> theatres = this->cityToTheatres[city];
        set<Movie*> movies;
        for(Theatre* theatre : theatres) {
            for(Screen* screen : theatre->getScreens()) {
                for(Show* show : screen->getShows(date)) {
                    movies.insert(show->getMovie());
                }
            }
        }
        return vector<Movie*>(movies.begin(), movies.end());
    }
    vector<Theatre*> getTheatres(City city, Movie* movie, int date) {
        vector<Theatre*> theatres = this->cityToTheatres[city];
        vector<Theatre*> result;
        for(Theatre* theatre : theatres) {
            bool movieFound = false;
            for(Screen* screen : theatre->getScreens()) {
                for(Show* show : screen->getShows(date)) {
                    if (show->getMovie() == movie) {
                        movieFound = true;
                        break;
                    }
                }
            }
            if (movieFound) {
                result.push_back(theatre);
            }
        }
        return result;
    }
    vector<Show*> getShows(Theatre* theatre, Movie* movie, int date) {
        vector<Show*> result;
        for(Screen* screen : theatre->getScreens()) {
            for(Show* show : screen->getShows(date)) {
                if (show->getMovie() == movie) {
                    result.push_back(show);
                }
            }
        }
        return result;
    }
};