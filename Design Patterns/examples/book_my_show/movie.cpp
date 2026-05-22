enum MovieType {
    ACTION,
    COMEDY,
    HORROR,
    ROMANCE,
    THRILLER
};

class Movie {
    int movieId;
    string name;
    string language;
    MovieType type;
    int duration;
    public:
    Movie(int movieId, string name, string language, MovieType type, int duration) {
        this->movieId = movieId;
        this->name = name;
        this->language = language;
        this->type = type;
        this->duration = duration;
    }
};
