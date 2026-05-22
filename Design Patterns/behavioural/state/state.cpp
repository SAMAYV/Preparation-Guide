#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations
class VendingMachine;

// Different states has different operations allowed, hence state design pattern is used
class State {
public:
    virtual void insertCoin(VendingMachine* vendingMachine, int coinValue) = 0;
    virtual void selectProduct(VendingMachine* vendingMachine, int productId) = 0;
    virtual void ejectMoney(VendingMachine* vendingMachine) = 0;
    virtual void dispenseItem(VendingMachine* vendingMachine) = 0;
    virtual ~State() = default;
};

// Declare state classes
class IdleState : public State {
public:
    void insertCoin(VendingMachine* vendingMachine, int coinValue) override;
    void ejectMoney(VendingMachine* vendingMachine) override;
    void selectProduct(VendingMachine* vendingMachine, int productId) override;
    void dispenseItem(VendingMachine* vendingMachine) override;
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* vendingMachine, int coinValue) override;
    void ejectMoney(VendingMachine* vendingMachine) override;
    void selectProduct(VendingMachine* vendingMachine, int productId) override;
    void dispenseItem(VendingMachine* vendingMachine) override;
};

class DispenseState : public State {
public:
    void insertCoin(VendingMachine* vendingMachine, int coinValue) override;
    void ejectMoney(VendingMachine* vendingMachine) override;
    void selectProduct(VendingMachine* vendingMachine, int productId) override;
    void dispenseItem(VendingMachine* vendingMachine) override;
};

class Product {
public:
    int id;
    string name;
    int price;
    int quantity;

    Product(int id, string name, int price, int quantity) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }
};

class VendingMachine {
private:
    State* idleState;
    State* hasCoinState;
    State* dispenseState;
    State* currentState;
    vector<Product*> products;
    int coinValue;
    int selectedProductId;

public:
    VendingMachine() {
        this->idleState = new IdleState();
        this->hasCoinState = new HasCoinState();
        this->dispenseState = new DispenseState();
        this->currentState = idleState;
        this->coinValue = 0;
        this->selectedProductId = -1;
        this->products = vector<Product*>();
        this->populateProducts();
    }

    void populateProducts() {
        this->products.push_back(new Product(0, "Coke", 10, 10));
        this->products.push_back(new Product(1, "Pepsi", 20, 10));
        this->products.push_back(new Product(2, "Sprite", 30, 10));
    }

    void insertCoin(int coinValue) {
        currentState->insertCoin(this, coinValue);
    }

    void ejectMoney() {
        currentState->ejectMoney(this);
    }

    void selectProduct(int productId) {
        currentState->selectProduct(this, productId);
    }

    void dispenseItem() {
        currentState->dispenseItem(this);
    }

    void setState(State* state) {
        this->currentState = state;
    }

    State* getIdleState() {
        return this->idleState;
    }

    State* getHasCoinState() {
        return this->hasCoinState;
    }

    State* getDispenseState() {
        return this->dispenseState;
    }

    void returnMoney() {
        cout << "Returning money to user: " << this->coinValue << endl;
        this->coinValue = 0;
    }

    void returnChange(int change) {
        cout << "Returning change to user: " << change << endl;
        this->coinValue -= change;
    }

    void addCoins(int coinValue) {
        this->coinValue += coinValue;
    }

    int getCoinValue() {
        return this->coinValue;
    }

    void setSelectedProduct(int productId) {
        this->selectedProductId = productId;
    }

    int getProductQuantity(int productId) {
        if (productId >= 0 && productId < products.size()) {
            return this->products[productId]->quantity;
        }
        return 0;
    }

    int getProductPrice(int productId) {
        if (productId >= 0 && productId < products.size()) {
            return this->products[productId]->price;
        }
        return 0;
    }

    int getSelectedProductQuantity() {
        if (selectedProductId >= 0 && selectedProductId < products.size()) {
            return this->products[this->selectedProductId]->quantity;
        }
        return 0;
    }

    void releaseSelectedItem() {
        if (selectedProductId >= 0 && selectedProductId < products.size()) {
            cout << "Dispensing: " << products[selectedProductId]->name << endl;
            this->products[this->selectedProductId]->quantity--;
            this->coinValue = 0;
        }
    }
};

// State method implementations (after VendingMachine is fully defined)
void IdleState::insertCoin(VendingMachine* vendingMachine, int coinValue) {
    cout << "Coin inserted: " << coinValue << endl;
    vendingMachine->addCoins(coinValue);
    vendingMachine->setState(vendingMachine->getHasCoinState());
}
void IdleState::ejectMoney(VendingMachine* vendingMachine) {
    cout << "No money to eject" << endl;
}
void IdleState::selectProduct(VendingMachine* vendingMachine, int productId) {
    cout << "Please insert coin first" << endl;
}
void IdleState::dispenseItem(VendingMachine* vendingMachine) {
    cout << "Please insert coin first" << endl;
}

void HasCoinState::insertCoin(VendingMachine* vendingMachine, int coinValue) {
    cout << "Coin already inserted. Adding more coins: " << coinValue << endl;
    vendingMachine->addCoins(coinValue);
}
void HasCoinState::ejectMoney(VendingMachine* vendingMachine) {
    cout << "Returning money" << endl;
    vendingMachine->returnMoney();
    vendingMachine->setState(vendingMachine->getIdleState());
}
void HasCoinState::selectProduct(VendingMachine* vendingMachine, int productId) {
    cout << "Selecting the product with id: " << productId << endl;
    if (vendingMachine->getProductQuantity(productId) <= 0) {
        cout << "Product with id: " << productId << " is out of stock" << endl;
        vendingMachine->returnMoney();
        vendingMachine->setState(vendingMachine->getIdleState());
        return;
    }
    vendingMachine->setSelectedProduct(productId);
    int returnValue = vendingMachine->getCoinValue() - vendingMachine->getProductPrice(productId);
    if (returnValue >= 0) {
        vendingMachine->setState(vendingMachine->getDispenseState());
        if (returnValue > 0) {
            vendingMachine->returnChange(returnValue);
        }
    }
    else {
        cout << "Insufficient balance. Need " << (-returnValue) << " more" << endl;
        vendingMachine->returnMoney();
        vendingMachine->setState(vendingMachine->getIdleState());
    }
}
void HasCoinState::dispenseItem(VendingMachine* vendingMachine) {
    cout << "Please select a product first" << endl;
}

void DispenseState::insertCoin(VendingMachine* vendingMachine, int coinValue) {
    cout << "Please wait, dispensing in progress" << endl;
}
void DispenseState::ejectMoney(VendingMachine* vendingMachine) {
    cout << "Can't eject money. Please collect your item." << endl;
}
void DispenseState::selectProduct(VendingMachine* vendingMachine, int productId) {
    cout << "Product already selected. Dispensing..." << endl;
}
void DispenseState::dispenseItem(VendingMachine* vendingMachine) {
    cout << "Dispensing product..." << endl;
    if (vendingMachine->getSelectedProductQuantity() > 0) {
        vendingMachine->releaseSelectedItem();
        vendingMachine->setState(vendingMachine->getIdleState());
    } else {
        cout << "Out of stock" << endl;
        vendingMachine->returnMoney();
        vendingMachine->setState(vendingMachine->getIdleState());
    }
}

int main() {
    VendingMachine* vendingMachine = new VendingMachine();

    cout << "=== Scenario 1: Successful purchase ===" << endl;
    vendingMachine->insertCoin(15);
    vendingMachine->selectProduct(0);
    vendingMachine->dispenseItem();

    cout << "\n=== Scenario 2: Insufficient balance ===" << endl;
    vendingMachine->insertCoin(5);
    vendingMachine->selectProduct(1);

    cout << "\n=== Scenario 3: Eject money ===" << endl;
    vendingMachine->insertCoin(15);
    vendingMachine->ejectMoney();

    delete vendingMachine;
    return 0;
}