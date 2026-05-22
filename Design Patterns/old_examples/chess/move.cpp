class Move {
    Player* player;
    Cell* startCell;
    Cell* endCell;
    Piece* movedPiece;
    Piece* capturedPiece;
    public:
    Move(Player* player, Cell* startCell, Cell* endCell) {
        this->player = player;
        this->startCell = startCell;
        this->endCell = endCell;
        this->movedPiece = startCell->getPiece();
        this->capturedPiece = endCell->getPiece();
    }
    Player* getPlayer() {
        return this->player;
    }
    Cell* getStartCell() {
        return this->startCell;
    }
    Cell* getEndCell() {
        return this->endCell;
    }
};

class MoveValidator {
    public:
    static bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        Piece* startPiece = startCell->getPiece();
        Piece* endPiece = endCell->getPiece();
        if (startPiece == NULL) {
            cout << "No piece at start cell" << endl;
            return false;
        }
        if (startPiece->getColor() != this->currentPlayer->getColor()) {
            cout << "Invalid move by " << this->currentPlayer->getColor() << " player" << endl;
            return false;
        }
        if (endPiece != NULL && endPiece->getColor() == this->currentPlayer->getColor()) {
            cout << "Invalid move. Friendly fire is not allowed" << endl;
            return false;
        }
        bool isValidMove = startPiece->isValidMove(this->board, move->getStartCell(), move->getEndCell());
        if (!isValidMove) {
            cout << "Invalid move" << endl;
            return false;
        }
    }
};