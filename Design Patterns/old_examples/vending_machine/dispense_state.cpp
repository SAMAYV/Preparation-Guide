class DispenseState {
    public:
    DispenseState() {
        cout << "Vending machine is in dispense state" << endl;
    }
    void clickOnInsertCoinButton(VendingMachine* vendingMachine) override {
        // Do nothing
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
        cout << "Dispensing product: " << codeNumber << endl;
        Item item = vendingMachine->getInventory()->getItem(codeNumber);
        vendingMachine->getInventory()->updateItemCount(codeNumber);
        vendingMachine->setState(new IdleState());
        return item;
    }
    int getChange(int extraAmount) override {
        return 0;
    }
    vector<Coin> refundMoney(VendingMachine* vendingMachine) override {
        return vector<Coin>();
    }
    void updateInventory(VendingMachine* vendingMachine, Item item, int codeNumber) override {
        // Do nothing
    }
};