class Jump {
    int start;
    int end;
};

class Snake : public Jump {
    public:
    Snake(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Ladder : public Jump {
    public:
    Ladder(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Cell {
    Jump* jump;
    public:
    Cell() {
        this->jump = NULL;
    }
    Jump* getJump() {
        return this->jump;
    }
    void setJump(Jump* jump) {
        this->jump = jump;
    }
};

class Board {
    Cell** cells;
    int size;
    public:
    Board(int size, int numSnakes, int numLadders) {
        this->size = size;
        this->cells = new Cell*[size];
        for(int i = 0; i < size; i++) {
            this->cells[i] = new Cell();
        }
        this->addSnakesAndLadders(numSnakes, numLadders);
    }
    int getBoardSize() {
        return this->size * this->size;
    }
    Cell* getCell(int position) {
        int row = position / this->size;
        int col = position % this->size;
        return this->cells[row][col];
    }
    void addSnakesAndLadders(int numSnakes, int numLadders) {
        int boardSize = this->getBoardSize();
        for(int i = 0; i < numSnakes; i++) {
            int snakeHead = 1 + rand() % (boardSize - 1);
            int snakeTail = 1 + rand() % (start - 1);
            this->getCell(snakeHead)->setJump(new Snake(start, end));
        }
        for(int i = 0; i < numLadders; i++) {
            int ladderStart = rand() % this->size;
            int ladderEnd = rand() % (this->size - start) + start;
            this->getCell(ladderStart)->setJump(new Ladder(start, end));
        }
    }
};
