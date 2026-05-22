class MatchType {
    public:
    virtual int getOvers() = 0;
    virtual int numberOfInnings() = 0;
    virtual int maxOversPerBowler() = 0;
};

class T20MatchType : public MatchType {
    public:
    int getOvers() {
        return 20;
    }
    int numberOfInnings() {
        return 2;
    }
    int maxOversPerBowler() {
        return 4;
    }
};

class ODIMatchType : public MatchType {
    public:
    int getOvers() {
        return 50;
    }
    int numberOfInnings() {
        return 2;
    }
    int maxOversPerBowler() {
        return 10;
    }
};
