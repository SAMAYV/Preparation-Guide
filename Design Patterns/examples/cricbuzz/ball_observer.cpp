class BallObserver {
    public:
    virtual void update(Ball* ball) = 0;
    int getRunsScored(Ball* ball) {
        RunType runs = ball->getRuns();
        int runsScored = 0;
        switch(runs) {
            case RunType::ONE:
                runsScored = 1;
                break;
            case RunType::TWO:
                runsScored = 2;
                break;
            case RunType::THREE:
                runsScored = 3;
                break;
            case RunType::FOUR:
                runsScored = 4;
                break;
            case RunType::SIX:
                runsScored = 6;
                break;
        }
        return runsScored;
    }
};

class BattingScoreBallObserver : public BallObserver {
    public:
    void update(Ball* ball) {
        // Update batting scoreboard
        Player* batsman = ball->getPlayedBy();
        RunType runs = ball->getRuns();
        int runsScored = this->getRunsScored(ball);
        batsman->getBattingScoreboard()->update(runsScored);
        if (ball->getWicket() != NULL) {
            batsman->getBattingScoreboard()->setWicket(ball->getWicket());
        }
    }
};

class BowlingScoreBallObserver : public BallObserver {
    public:
    void update(Ball* ball) {
        // Update bowling scoreboard
        Player* bowler = ball->getBowledBy();
        RunType runs = ball->getRuns();
        int runsScored = this->getRunsScored(ball);
        bowler->getBowlingScoreboard()->update(runsScored);
        if (ball->getWicket() != NULL) {
            bowler->getBowlingScoreboard()->updateWicket();
        }
        if (ball->getBallNumber() == 6) {
            bowler->getBowlingScoreboard()->updateOver();
        }
    }
};

