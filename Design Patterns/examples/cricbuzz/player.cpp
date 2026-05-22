enum PlayerType {
    BATSMAN,
    BOWLER,
    ALLROUNDER,
    WICKETKEEPER
};

class Player {
    string name;
    int jerseyNumber;
    PlayerType type;
    PlayerBattingScoreboard* battingScoreboard;
    PlayerBowlingScoreboard* bowlingScoreboard;
    public:
    Player(string name, int jerseyNumber) {
        this->name = name;
        this->jerseyNumber = jerseyNumber;
    }
    PlayerBattingScoreboard* getBattingScoreboard() {
        return this->battingScoreboard;
    }
    PlayerBowlingScoreboard* getBowlingScoreboard() {
        return this->bowlingScoreboard;
    }
    string getName() {
        return this->name;
    }
}

class PlayerBattingScoreboard {
    int runs;
    int ballsFaced;
    int fours;
    int sixes;
    double strikeRate;
    Wicket* wicket;
    public:
    PlayerBattingScoreboard() {
        this->runs = 0;
        this->ballsFaced = 0;
        this->fours = 0;
        this->sixes = 0;
        this->strikeRate = 0.0;
        this->wicket = NULL;
    }
    void print() {
        cout << "Runs: " << this->runs << " | Balls Faced: " << this->ballsFaced << " | Fours: " << this->fours << " | Sixes: " << this->sixes << " | Strike Rate: " << this->strikeRate << endl;
    }
    void update(int runs) {
        this->runs += runs;
        this->ballsFaced++;
        if (runs == 4) {
            this->fours++;
        }
        else if (runs == 6) {
            this->sixes++;
        }
        this->strikeRate = (double)this->runs / this->ballsFaced;
    }
    void setWicket(Wicket* wicket) {
        this->wicket = wicket;
    }
};

class PlayerBowlingScoreboard {
    int oversBowled;
    int maidensBowled;
    int runsGiven;
    int wicketsTaken;
    double economy;
    public:
    PlayerBowlingScoreboard() {
        this->oversBowled = 0;
        this->maidensBowled = 0;
        this->runsGiven = 0;
        this->wicketsTaken = 0;
        this->economy = 0.0;
    }
    void print() {
        cout << "Overs: " << this->oversBowled << " | Maidens: " << this->maidensBowled << " | Runs Given: " << this->runsGiven << " | Wickets Taken: " << this->wicketsTaken << " | Economy: " << this->economy << endl;
    }
    void update(int runs) {
        this->runsGiven += runs;
        this->economy = (double)this->runsGiven / this->oversBowled;
        if (runs == 0) {
            this->maidensBowled++;
        }
    }
    void updateWicket() {
        this->wicketsTaken++;
    }
    void updateOver() {
        this->oversBowled++;
    }
};