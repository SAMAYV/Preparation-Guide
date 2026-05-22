enum WicketType {
    BOWLED,
    CAUGHT,
    LBW,
    STUMPED,
    RUN_OUT
};

class Wicket {
    WicketType type;
    Player* takenBy;
    Over* overTakenIn;
    Ball* ballTakenIn;
    public:
    Wicket(WicketType type, Player* takenBy, Over* overTakenIn, Ball* ballTakenIn) {
        this->type = type;
        this->takenBy = takenBy;
        this->overTakenIn = overTakenIn;
        this->ballTakenIn = ballTakenIn;
    }
};