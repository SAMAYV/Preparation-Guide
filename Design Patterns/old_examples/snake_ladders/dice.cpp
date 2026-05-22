class Dice {
    int numDices;
    public:
    Dice(int numDices) {
        this->numDices = numDices;
    }
    int roll() {
        int sum = 0;
        for(int i = 0; i < this->numDices; i++) {
            sum += rand() % 6 + 1;
        }
        return sum;
    }
};