enum Color {
    WHITE,
    BLACK
};

enum PieceType {
    ROOK,
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    PAWN
};

class Piece {
    Color color;
    bool isCaptured;
    PieceType type;
    public:
    Piece(Color color, PieceType type) {
        this->color = color;
        this->isCaptured = false;
        this->type = type;
    }
    string toString() {
        string symbol = switch(this->type) {
            case PieceType::ROOK: return "R";
            case PieceType::KING: return "K";
            case PieceType::QUEEN: return "Q";
            case PieceType::BISHOP: return "B";
            case PieceType::KNIGHT: return "N";
            case PieceType::PAWN: return "P";
        };
        return this->color == Color::WHITE ? symbol : tolower(symbol);
    }
    PieceType getType() {
        return this->type;
    }
    bool isPathClear(Board* board, Cell* startCell, Cell* endCell) {
        int startRow = startCell->getRow();
        int startCol = startCell->getCol();
        int endRow = endCell->getRow();
        int endCol = endCell->getCol();
        int rowStep = endRow < startRow ? -1 : 1;
        int colStep = endCol < startCol ? -1 : 1;
        int row = startRow + rowStep;
        int col = startCol + colStep;
        while(row != endRow || col != endCol) {
            if (board->getCell(Position(row, col))->getPiece() != NULL) {
                return false;
            }
            row += rowStep;
            col += colStep;
        }
        return true;
    }
    virtual bool isValidMove(Board* board, Cell* startCell, Cell* endCell) = 0;
};

class Rook : public Piece {
    public:
    Rook(Color color) : Piece(color, PieceType::ROOK) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};

class King : public Piece {
    public:
    King(Color color) : Piece(color, PieceType::KING) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};

class Queen : public Piece {
    public:
    Queen(Color color) : Piece(color, PieceType::QUEEN) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};

class Bishop : public Piece {
    public:
    Bishop(Color color) : Piece(color, PieceType::BISHOP) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};

class Knight : public Piece {
    public:
    Knight(Color color) : Piece(color, PieceType::KNIGHT) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};

class Pawn : public Piece {
    public:
    Pawn(Color color) : Piece(color, PieceType::PAWN) {}
    bool isValidMove(Board* board, Cell* startCell, Cell* endCell) {
        // Check if the move is valid
    }
};
