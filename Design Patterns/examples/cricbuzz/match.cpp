class Match {
    int matchId;
    Team* team1;
    Team* team2;
    Team* tossWinner;
    Team* winner;
    vector<Innings*> innings;
    MatchType matchType;
    public:
    Match(int matchId, Team* team1, Team* team2, MatchType matchType) {
        this->matchId = matchId;
        this->team1 = team1;
        this->team2 = team2;
        this->matchType = matchType;
        this->innings = vector<Innings*>();
    }
    void startMatch() {
        this->toss();
        cout << this->tossWinner->getName() << " won the toss and chose to bat" << endl;
        for(int i = 0; i < this->matchType->numberOfInnings(); i++) {
            Team* battingTeam = i % 2 == 0 ? this->tossWinner : this->getOpponent(this->tossWinner);
            Team* bowlingTeam = this->getOpponent(battingTeam);
            // Target is 1e9 for first innings and 1 more than the runs scored in the previous innings for the second innings
            int target = i == 0 ? -1 : this->innings[i - 1]->getRunsScored() + 1;
            this->startInnings(battingTeam, bowlingTeam, target);
        }
    }
    void startInnings(Team* battingTeam, Team* bowlingTeam, int target) {
        cout << "Innings " << i + 1 << " : " << battingTeam->getName() << " batting against " << bowlingTeam->getName() << endl;
        Innings* innings = new Innings(battingTeam, bowlingTeam);
        this->innings.push_back(innings);
        innings->startInnings(this->matchType, target);
        if (battingTeam->getIsWinner()) {
            this->winner = battingTeam;
        }
    }
    void toss() {
        srand(time(NULL));
        int toss = rand() % 2;
        if (toss == 0) {
            this->tossWinner = this->team1;
        } else {
            this->tossWinner = this->team2;
        }
    }
    Team* getOpponent(Team* team) {
        return team == this->team1 ? this->team2 : this->team1;
    }
};

class Innings {
    Team* battingTeam;
    Team* bowlingTeam;
    vector<Over*> oversBowled;
    public:
    Innings(Team* battingTeam, Team* bowlingTeam, MatchType matchType) {
        this->battingTeam = battingTeam;
        this->bowlingTeam = bowlingTeam;
        this->matchType = matchType;
        this->oversBowled = vector<Over*>();
    }
    int getRunsScored() {
        int runsScored = 0;
        for (Over* over : this->oversBowled) {
            runsScored += over->getRunsScored();
        }
        return runsScored;
    }
    void startInnings(MatchType matchType, int target) {
        for (int overNumber = 0; overNumber < matchType->getOvers(); overNumber++) {
            // Get the next bowler
            this->bowlingTeam->getNextBowler(matchType->maxOversPerBowler());
            // Bowl the over
            Over* over = new Over(overNumber, this->bowlingTeam->getCurrentBowler());
            this->oversBowled.push_back(over);
            // Start the over
            if (over->startOver(this->battingTeam, this->bowlingTeam, target)) {
                cout << this->battingTeam->getName() << " reached the target in " << overNumber + 1 << " overs" << endl;
                break;
            }
        }
    }
};
