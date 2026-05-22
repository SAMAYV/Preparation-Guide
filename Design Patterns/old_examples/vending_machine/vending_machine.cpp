class VendingMachine {
    Inventory* inventory;
    State* currentState;
    vector<Coin> coins;
    public:
    VendingMachine() {
        this->inventory = new Inventory();
        this->currentState = new IdleState();
        this->coins = vector<Coin>();
    }
    void setState(State* state) {
        this->currentState = state;
    }
    void clickOnInsertCoinButton() {
        this->currentState->clickOnInsertCoinButton(this);
    }
    void insertCoin(Coin coin) {
        this->currentState->insertCoin(this, coin);
    }
    void clickOnSelectProductButton() {
        this->currentState->clickOnSelectProductButton(this);
    }
    void selectProduct(int codeNumber) {
        this->currentState->selectProduct(this, codeNumber);
    }
    Item dispenseProduct(int codeNumber) {
        return this->currentState->dispenseProduct(this, codeNumber);
    }
    void addCoin(Coin coin) {
        this->coins.push_back(coin);
    }
    vector<Coin> getCoins() {
        return this->coins;
    }
    int getCoinsValue() {
        int total = 0;
        for (Coin coin : this->coins) {
            total += coin.getValue();
        }
        return total;
    }
    void emptyCoins() {
        this->coins = vector<Coin>();
    }
    void getInventory() {
        return this->inventory;
    }
};

int main() {
    VendingMachine* vendingMachine = new VendingMachine();

    // Add items to inventory
    vendingMachine->getInventory()->addItem(new Item(COKE, 10), 1);
    vendingMachine->getInventory()->addItem(new Item(SPRITE, 10), 2);
    vendingMachine->getInventory()->addItem(new Item(FANTA, 10), 3);

    // Start vending
    vendingMachine->clickOnInsertCoinButton();
    vendingMachine->insertCoin(Coin(15));
    vendingMachine->clickOnSelectProductButton();
    vendingMachine->selectProduct(1);
    Item* item = vendingMachine->dispenseProduct(1);
    cout << "Dispensed item: " << item->getPrice() << endl;

    return 0;
}