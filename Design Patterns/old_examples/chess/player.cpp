class Player {
    Color color;
    public:
    Player(Color color) {
        this->color = color;
    }
    Color getColor() {
        return this->color;
    }
};