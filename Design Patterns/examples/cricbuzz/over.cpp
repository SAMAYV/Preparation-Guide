enum BallType {
    WIDE,
    NO_BALL,
    NORMAL
};

enum RunType {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    SIX
};

class Over {
    int overNumber;
    vector<Ball*> balls;
    int extraBallsCount;
    Player* bowler;
    public:
    Over(int overNumber, Player* bowler) {
        this->overNumber = overNumber;
        this->bowler = bowler;
        this->balls = vector<Ball*>();
        this->extraBallsCount = 0;
    }
    bool startOver(Team* battingTeam, Team* bowlingTeam, int target) {
        int ballCount = 0;
        while(ballCount < 6) {
            Ball* ball = new Ball(ballCount + 1);
            ball->playBall(battingTeam, bowlingTeam, this);
            if (ball->getBallType() == BallType::NORMAL) {
                ballCount++;
                this->balls.push_back(ball);
                if (ball->getWicket() != NULL) {
                    battingTeam->getNextBatsman();
                }
            }
            else {
                this->extraBallsCount++;
                battingTeam->addExtraRuns(ball->getRuns());
            }
            if (target != -1 && battingTeam->getRunsScored() >= target) {
                this->battingTeam->setIsWinner(true);
                return true;
            }
        }
        return false;
    }
    int getRunsScored() {
        int runsScored = 0;
        for (Ball* ball : this->balls) {
            runsScored += ball->getRuns();
        }
        return runsScored;
    }
};

class Ball {
    int ballNumber;
    BallType type;
    RunType runs;
    Player* playedBy;
    Player* bowledBy;
    Wicket* wicket;
    vector<BallObserver*> observers;
    public:
    Ball(int ballNumber) {
        this->ballNumber = ballNumber;
        this->observers = vector<BallObserver*>();
        observers.push_back(new BattingScoreBallObserver());
        observers.push_back(new BowlingScoreBallObserver());
    }
    void playBall(Team* battingTeam, Team* bowlingTeam, Over* over) {
        // Get the batsman and bowler
        this->playedBy = battingTeam->getOnStrike();
        this->bowledBy = bowlingTeam->getCurrentBowler();
        // Play the ball
        this->type = BallType::NORMAL;
        // Check if wicket is taken
        if (this->isWicketTaken()) {
            this->runs = RunType::ZERO;
            this->wicket = new Wicket(WicketType::BOWLED, this->bowledBy, over, this);
            battingTeam->setOnStrike(NULL);
        }
        else {
            this->runs = this->getRunsScored();
            this->wicket = NULL;
            if (this->runs == RunType::ONE || this->runs == RunType::THREE) {
                battingTeam->swapStrike();
            }
        }
        // Notify Updaters to update the scoreboards
        this->notifyUpdaters();
    }
    void notifyUpdaters() {
        for (BallObserver* observer : this->observers) {
            observer->update(this);
        }
    }
    int getRuns() {
        return this->runs;
    }
    BallType getBallType() {
        return this->type;
    }
    Wicket* getWicket() {
        return this->wicket;
    }
    bool isWicketTaken() {
        srand(time(NULL));
        int wicket = rand() % 2;
        return wicket == 0;
    }
    RunType getRunsScored() {
        srand(time(NULL));
        int runs = rand() % 7;
        return (RunType)runs;
    }
};