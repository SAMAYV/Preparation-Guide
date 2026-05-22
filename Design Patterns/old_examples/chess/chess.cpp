class Chess {
    Board* board;
    Player* whitePlayer;
    Player* blackPlayer;
    Player* currentPlayer;
    Player* winner;
    vector<Move*> moveHistory;
    MoveValidator* moveValidator;

    public:
    Chess() {
        Board* board = new Board(8);
        this->whitePlayer = new Player(WHITE);
        this->blackPlayer = new Player(BLACK);
        this->currentPlayer = this->whitePlayer;
        this->winner = NULL;
        this->moveValidator = new MoveValidator();
        this->startGame();
    }
    void startGame() {
        while(this->winner == NULL) {
            this->board->printBoard();
            cout << "Current player: " << this->currentPlayer->getColor() << endl;
            this->takeTurn();
        }
        cout << "Winner is " << this->winner->getColor() << endl;
    }
    void takeTurn() {
        int startRow, startCol, endRow, endCol;
        cout << "Enter start row, start column, end row, end column: ";
        cin >> startRow >> startCol >> endRow >> endCol;

        Cell* startCell = this->board->getCell(startPosition(startRow, startCol));
        Cell* endCell = this->board->getCell(endPosition(endRow, endCol));
        Move* move = new Move(this->currentPlayer, startCell, endCell);

        if (!this->makeMove(move)) {
            cout << "Invalid move. Please try again" << endl;
            this->takeTurn();
        }
    }
    bool makeMove(Move* move) {
        // Check if the move is valid
        if (!this->moveValidator->isValidMove(this->board, move->getStartCell(), move->getEndCell())) {
            return false;
        }
        Piece* startPiece = move->getStartCell()->getPiece();
        Piece* endPiece = move->getEndCell()->getPiece();
        // Move the piece
        endPiece->setCaptured(true);
        move->getStartCell()->setPiece(NULL);
        move->getEndCell()->setPiece(startPiece);
        this->moveHistory.push_back(move);
        // Check for winner
        if (this->isCheckmate(endPiece)) {
            this->winner = this->currentPlayer;
        }
        this->updateCurrentPlayer();
        return true;
    }
    void updateCurrentPlayer() {
        if (this->currentPlayer == this->whitePlayer) {
            this->currentPlayer = this->blackPlayer;
        } else {
            this->currentPlayer = this->whitePlayer;
        }
    }
    bool isCheckmate(Piece* endPiece) {
        if(endPiece->getType() == PieceType::KING) {
            return true;
        }
        return false;
    }
}