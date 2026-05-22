class Coin {
    int value;
    public:
    Coin(int value) {
        this->value = value;
    }
    int getValue() {
        return this->value;
    }
};

// State wise, single or multiple operations are allowed, hence state design pattern is used
class State {
    public:
    virtual void clickOnInsertCoinButton(VendingMachine* vendingMachine) = 0;
    virtual void insertCoin(VendingMachine* vendingMachine, int coinValue) = 0;
    virtual void clickOnSelectProductButton(VendingMachine* vendingMachine) = 0;
    virtual void selectProduct(VendingMachine* vendingMachine, int codeNumber) = 0;
    virtual Item dispenseProduct(VendingMachine* vendingMachine, int codeNumber) = 0;
    virtual int getChange(int extraAmount) = 0;
    virtual vector<Coin> refundMoney(VendingMachine* vendingMachine) = 0;
    virtual void updateInventory(VendingMachine* vendingMachine, Item item, int codeNumber) = 0;
};