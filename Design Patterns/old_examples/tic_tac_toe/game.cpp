class TicTacToe {
    Board* board;
    deque<Player*> players;
    public:
    TicTacToe() {
        this->board = new Board(3);
        this->players = deque<Player*>();
    }
    void initializeGame() {
        Player* player1 = new Player(PieceType::X);
        Player* player2 = new Player(PieceType::O);
        this->players.push_back(player1);
        this->players.push_back(player2);
    }
    void startGame() {
        this->initializeGame();
        bool isGameOver = false;
        while(!isGameOver && !this->isDraw()) {
            Player* player = this->players.front();
            this->board->printBoard();
            this->takeTurn(player);
            if (this->checkForWinner(player->getPieceType()) {
                isGameOver = true;
                cout << "Player " << player->getPieceType() << " wins!" << endl;
                this->board->printBoard();
                return;
            }
            this->players.push_back(this->players.front());
            this->players.pop_front();
        }
        cout << "Draw!" << endl;
    }
    void takeTurn(Player* player) {
        int row, col;
        cout << "Player " << player->getPieceType() << " enter row and column: ";
        cin >> row >> col;
        if (!this->board->isValidMove(row, col)) {
            cout << "Invalid move. Please try again" << endl;
            this->takeTurn(player);
        }
        else {
            this->board->placePiece(row, col, player->getPieceType());
        }
    }
    bool checkForWinner(PieceType pieceType) {
        return this->checkRows(pieceType) || this->checkCols(pieceType) || this->checkDiagonals(pieceType);
    }
    bool isDraw() {
        return this->board->isFull();
    }
    bool checkRows(PieceType pieceType) {
        for(int i = 0; i < this->board->getSize(); i++) {
            int count = 0;
            for(int j = 0; j < this->board->getSize(); j++) {
                if (this->board->getPiece(i, j) != NULL && this->board->getPiece(i, j)->getType() == pieceType) {
                    count++;
                }
            }
            if (count == this->board->getSize()) {
                return true;
            }
        }
        return false;
    }
    bool checkCols(PieceType pieceType) {
        for(int i = 0; i < this->board->getSize(); i++) {
            int count = 0;
            for(int j = 0; j < this->board->getSize(); j++) {
                if (this->board->getPiece(j, i) != NULL && this->board->getPiece(j, i)->getType() == pieceType) {
                    count++;
                }
            }
            if (count == this->board->getSize()) {
                return true;
            }
        }
        return false;
    }
    bool checkDiagonals(PieceType pieceType) {
        int count = 0;
        for(int i = 0; i < this->board->getSize(); i++) {
            if (this->board->getPiece(i, i) != NULL && this->board->getPiece(i, i)->getType() == pieceType) {
                count++;
            }
        }
        if (count == this->board->getSize()) {
            return true;
        }
        count = 0;
        for(int i = 0; i < this->board->getSize(); i++) {
            if (this->board->getPiece(i, this->board->getSize() - 1 - i) != NULL && this->board->getPiece(i, this->board->getSize() - 1 - i)->getType() == pieceType) {
                count++;
            }
        }
        if (count == this->board->getSize()) {
            return true;
        }
        return false;
    }
}