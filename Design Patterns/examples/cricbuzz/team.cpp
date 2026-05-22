class Team {
    string name;
    queue<Player*> p11;
    queue<Player*> bench;
    PlayerBattingController* playerBattingController;
    PlayerBowlingController* playerBowlingController;
    int extraRuns;
    bool isWinner;
    public:
    Team(string name, queue<Player*> p11, queue<Player*> bench) {
        this->name = name;
        this->p11 = p11;
        this->bench = bench;
        this->setBattingController();
        this->setBowlingController();
        this->extraRuns = 0;
    }
    void setBattingController() {
        queue<Player*> p11Copy = this->p11;
        Player* onStrike = p11Copy.front();
        p11Copy.pop();
        Player* offStrike = p11Copy.front();
        p11Copy.pop();
        this->playerBattingController = new PlayerBattingController(p11Copy, onStrike, offStrike);
    }
    void setBowlingController() {
        queue<Player*> bowlers;
        for(Player* player : p11) {
            if (player->type == PlayerType::BOWLER || player->type == PlayerType::ALLROUNDER) {
                bowlers.push(player);
            }
        }
        this->playerBowlingController = new PlayerBowlingController(bowlers);
    }
    Player* getNextBowler(int maxOversPerBowler) {
        return this->playerBowlingController->getNextBowler(maxOversPerBowler);
    }
    Player* getNextBatsman() {
        return this->playerBattingController->getNextBatsman();
    }
    Player* getOnStrike() {
        return this->playerBattingController->getOnStrike();
    }
    Player* getOffStrike() {
        return this->playerBattingController->getOffStrike();
    }
    void swapStrike() {
        this->playerBattingController->swapStrike();
    }
    void setIsWinner(bool isWinner) {
        this->isWinner = isWinner;
    }
    void printBattingScoreboard() {
        cout << "Batting Scoreboard for " << this->name << " : " << endl;
        for (Player* player : this->p11) {
            player->battingScoreboard->print();
        }
    }
    void printBowlingScoreboard() {
        cout << "Bowling Scoreboard for " << this->name << " : " << endl;
        for (Player* player : this->p11) {
            player->bowlingScoreboard->print();
        }
    }
    int getRunsScored() {
        int runsScored = this->extraRuns;
        for (Player* player : this->p11) {
            runsScored += player->battingScoreboard->getRuns();
        }
        return runsScored;
    }
    void addExtraRuns(int runs) {
        this->extraRuns += runs;
    }
};