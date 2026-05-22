class IdleState : public State {
    public:
    IdleState() {
        cout << "Vending machine is in idle state" << endl;
    }
    void clickOnInsertCoinButton(VendingMachine* vendingMachine) override {
        // Transition to has coin state
        vendingMachine->setState(new HasCoinState());
    }
    void insertCoin(VendingMachine* vendingMachine, int coinValue) override {
        // Do nothing
    }
    void clickOnSelectProductButton(VendingMachine* vendingMachine) override {
        // Do nothing
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
        return vector<Coin>();
    }
    void updateInventory(VendingMachine* vendingMachine, Item item, int codeNumber) override {
        vendingMachine->getInventory()->addItem(item, codeNumber);
    }
};