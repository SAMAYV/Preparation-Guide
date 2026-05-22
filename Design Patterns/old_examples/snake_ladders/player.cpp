class Player {
    string id;
    int currentPosition;
    public:
    Player(string id) {
        this->id = id;
        this->currentPosition = 0;
    }
    void move(int steps) {
        this->currentPosition += steps;
    }
    int getPosition() {
        return this->currentPosition;
    }
    void setPosition(int position) {
        this->currentPosition = position;
    }
    string getId() {
        return this->id;
    }
};