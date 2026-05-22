class Position {
    int row;
    int col;
    public:
    Position(int row, int col) {
        this->row = row;
        this->col = col;
    }
};

class Cell {
    Piece* piece;
    Position position;
    public:
    Cell(Position position) {
        this->position = position;
        this->piece = NULL;
    }
    Piece* getPiece() {
        return this->piece;
    }
    void setPiece(Piece* piece) {
        this->piece = piece;
    }
    string toString() {
        if (this->piece == NULL) {
            return "_";
        }
        return this->piece->toString();
    }
    int getRow() {
        return this->row;
    }
    int getCol() {
        return this->col;
    }
};