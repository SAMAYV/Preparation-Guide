class Board {
    int size;
    Piece*** board;
    public:
    Board(int size) {
        this->size = size;
        this->board = new Piece**[size];
        for(int i = 0; i < size; i++) {
            this->board[i] = new Piece*[size];
            for(int j = 0; j < size; j++) {
                this->board[i][j] = NULL;
            }
        }
    }
    void getPiece(int row, int col) {
        return this->board[row][col];
    }
    void printBoard() {
        for(int i = 0; i < this->size; i++) {
            for(int j = 0; j < this->size; j++) {
                if (this->board[i][j] == NULL) {
                    cout << "_";
                } else {
                    cout << this->board[i][j]->getType();
                }
                cout << " ";
            }
            cout << endl;
        }
    }
    bool isValidMove(int row, int col) {
        return this->board[row][col] == NULL;
    }
    void placePiece(int row, int col, PieceType pieceType) {
        if (isValidMove(row, col)) {
            cout << "Invalid move" << endl;
            return;
        }
        if (pieceType == PieceType::X) {
            this->board[row][col] = new XPiece();
        } else {
            this->board[row][col] = new OPiece();
        }
    }
    bool isFull() {
        for(int i = 0; i < this->size; i++) {
            for(int j = 0; j < this->size; j++) {
                if (this->board[i][j] == NULL) {
                    return false;
                }
            }
        }
        return true;
    }
};