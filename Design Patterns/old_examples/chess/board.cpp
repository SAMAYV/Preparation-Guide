class Board {
    Cell** cells;
    int size;
    public:
    Board(int size) {
        this->size = size;
        this->initializeBoard();
    }
    void initializeBoard() {
        this->cells = new Cell*[this->size];
        for(int i = 0; i < this->size; i++) {
            this->cells[i] = new Cell[i];
            for(int j = 0; j < this->size; j++) {
                this->cells[i][j] = new Cell(i, j);
            }
        }
        this->placePieces();
    }
    void placePieces() {
        for(int i = 0; i < this->size; i++) {
            this->cells[0][i]->setPiece(new Rook(WHITE));
            this->cells[1][i]->setPiece(new Pawn(WHITE));
            this->cells[this->size - 1][i]->setPiece(new Rook(BLACK));
            this->cells[this->size - 2][i]->setPiece(new Pawn(BLACK));
        }
    }
    void printBoard() {
        for(int i = 0; i < this->size; i++) {
            for(int j = 0; j < this->size; j++) {
                cout << this->cells[i][j].toString() << " ";
            }
            cout << endl;
        }
    }
};