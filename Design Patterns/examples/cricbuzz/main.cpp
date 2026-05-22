int main() {
    // Create players
    vector<Player*> team1Players;
    for (int i = 0; i < 11; i++) {
        team1Players.push_back(new Player("Team 1 Player " + to_string(i), i));
    }
    vector<Player*> team2Players;
    for (int i = 0; i < 11; i++) {
        team2Players.push_back(new Player("Team 2 Player " + to_string(i), i));
    }
    // Create teams
    Team* team1 = new Team("Team 1", team1Players);
    Team* team2 = new Team("Team 2", team2Players);
    // Create a T20 match between Team 1 and Team 2
    Match* match = new Match(1, team1, team2, new T20MatchType());
    match->startMatch();
    cout << "Winner: " << match->getWinner()->getName() << endl;
    match->getWinner()->printBattingScoreboard();
    match->getWinner()->printBowlingScoreboard();
    return 0;
}