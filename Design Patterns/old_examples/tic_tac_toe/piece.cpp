enum PieceType {
    X,
    O
};

class Piece {
    PieceType type;
    public:
    Piece(PieceType type) {
        this->type = type;
    }
    PieceType getType() {
        return this->type;
    }
};

class XPiece : public Piece {
    public:
    XPiece() : Piece(PieceType::X) {}
};

class OPiece : public Piece {
    public:
    OPiece() : Piece(PieceType::O) {}
};
