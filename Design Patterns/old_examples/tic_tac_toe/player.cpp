class Player {
    PieceType pieceType;
    public:
    Player(PieceType pieceType) {
        this->pieceType = pieceType;
    }
    PieceType getPieceType() {
        return this->pieceType;
    }
}