class SelectionState : public State {
    public:
    SelectionState() {
        cout << "Vending machine is in selection state" << endl;
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
        Item* item = vendingMachine->getInventory()->getItem(codeNumber);
        int totalAmount = vendingMachine->getCoinsValue();
        if (totalAmount < item->getPrice()) {
            cout << "Insufficient balance, refunding money to user" << endl;
            this->refundMoney();
            return;
        }
        else {
            int change = totalAmount - item->getPrice();
            if (change > 0) {
                cout << "Returning change to user: " << change << endl;
                this->returnChange(change);
            }
            vendingMachine->setState(new DispenseState());
        }
    }
    Item dispenseProduct(VendingMachine* vendingMachine) override {
        // Do nothing
        return NULL;
    }
    int getChange(int extraAmount) override {
        cout << "Returning change to user: " << extraAmount << endl;
        vendingMachine->emptyCoins();
        return extraAmount;
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