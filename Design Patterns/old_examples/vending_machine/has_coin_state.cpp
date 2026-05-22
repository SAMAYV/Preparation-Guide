class HasCoinState : public State {
    public:
    HasCoinState() {
        cout << "Vending machine is in has coin state" << endl;
    }
    void clickOnInsertCoinButton(VendingMachine* vendingMachine) override {
        // Do nothing
    }
    void insertCoin(VendingMachine* vendingMachine, Coin coin) override {
        // Add the coin to the vending machine
        cout << "Coin inserted: " << coin.getValue() << endl;
        vendingMachine->addCoin(coin);
    }
    void clickOnSelectProductButton(VendingMachine* vendingMachine) override {
        // Do nothing
        vendingMachine->setState(new SelectionState());
    }
    void selectProduct(VendingMachine* vendingMachine, int codeNumber) override {
        // Do nothing
    }
    Item dispenseProduct(VendingMachine* vendingMachine, int codeNumber) override {
        // Do nothing
        return NULL;
    }
    int getChange(int extraAmount) override {
        return 0;
    }
    vector<Coin> refundMoney(VendingMachine* vendingMachine) override {
        cout << "Refunding money added so far" << endl;
        vendingMachine->setState(new IdleState());
        vector<Coin> coins = vendingMachine->getCoins();
        vendingMachine->emptyCoins();
        return coins;
    }
    void updateInventory(VendingMachine* vendingMachine, Item item, int codeNumber) override {
        // Do nothing
    }
};