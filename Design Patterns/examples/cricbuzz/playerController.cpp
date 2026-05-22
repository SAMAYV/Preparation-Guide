class PlayerBattingController {
    queue<Player*> yetToBat;
    Player* onStrike;
    Player* offStrike;
    public:
    PlayerBattingController(queue<Player*> remainingBatsmen, Player* onStrike, Player* offStrike) {
        this->yetToBat = remainingBatsmen;
        this->onStrike = onStrike;
        this->offStrike = offStrike;
    }
    Player* chooseNextBatsman() {
        if (this->yetToBat.empty()) {
            cout << "All batsmen have batted" << endl;
            return NULL;
        }
        Player* batsman = this->yetToBat.front();
        this->yetToBat.pop();
        return batsman;
    }
    Player* getOnStrike() {
        return this->onStrike;
    }
    Player* getOffStrike() {
        return this->offStrike;
    }
    void setOnStrike(Player* onStrike) {
        this->onStrike = onStrike;
    }
    void setOffStrike(Player* offStrike) {
        this->offStrike = offStrike;
    }
    void swapStrike() {
        Player* temp = this->onStrike;
        this->onStrike = this->offStrike;
        this->offStrike = temp;
    }
};

class PlayerBowlingController {
    queue<Player*> bowlers;
    map<Player*, int> bowlerToOversBowled;
    Player* currentBowler;
    public:
    PlayerBowlingController(queue<Player*> bowlers) {
        this->bowlers = bowlers;
        this->bowlerToOversBowled = map<Player*, int>();
    }
    Player* getNextBowler(int maxOversPerBowler) {
        Player* nextBowler = this->bowlers.front();
        this->bowlers.pop();
        this->bowlerToOversBowled[nextBowler]++;
        this->currentBowler = nextBowler;
        if (this->bowlerToOversBowled[nextBowler] < maxOversPerBowler) {
            this->bowlers.push(nextBowler);
        }
        return bowler;
    }
    Player* getCurrentBowler() {
        return this->currentBowler;
    }
};