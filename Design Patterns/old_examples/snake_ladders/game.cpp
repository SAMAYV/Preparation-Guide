class Game {
    Board* board;
    deque<Player*> players;
    Dice* dice;
    public:
    Game(int size) {
        this->board = new Board(size, 5, 5);
        this->addPlayers();
    }
    void addPlayers() {
        this->players.push_back(new Player("Player 1"));
        this->players.push_back(new Player("Player 2"));
    }
    bool isWinner(Player* player) {
        return player->getPosition() == this->board->getBoardSize();
    }
    void startGame() {
        // Start game
        Player winner = NULL;
        while(winner == NULL) {
            Player* player = this->players.front();
            this->playTurn(player);
            if (this->isWinner(player)) {
                winner = player;
            }
            else {
                this->players.push_back(this->players.front());
                this->players.pop_front();
            }
        }
        cout << "Winner is " << winner->getId() << endl;
    }
    void playTurn(Player* player) {
        int steps = this->dice->roll();
        cout << player->getId() << " rolled " << steps << endl;
        if (player->getPosition() + steps > this->board->getBoardSize()) {
            cout << "Invalid move. Please try again" << endl;
            return;
        }
        player->move(steps);
        Cell* cell = this->board->getCell(player->getPosition());
        // Check if there is a snake or ladder
        Jump* jump = cell->getJump();
        if (jump != NULL) {
            player->setPosition(jump->end);
        }
    }
}