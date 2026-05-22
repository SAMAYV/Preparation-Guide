enum ProductType {
    ELECTRONICS,
    CLOTHING,
    BOOKS,
    STATIONERY
};

class Product {
    string name;
    double originalPrice;
    ProductType type;
    public:
    Product(string name, double originalPrice, ProductType type) {
        this->name = name;
        this->originalPrice = originalPrice;
        this->type = type;
    }
    string getName() {
        return this->name;
    }
    virtual double getPrice() = 0;
};

class Item1 : public Product {
    public:
    Item1(string name, double originalPrice) : Product(name, originalPrice) {}
    double getPrice() {
        cout << "Original price of " << this->name << " is " << this->originalPrice << endl;
        return this->originalPrice;
    }
};

class Item2 : public Product {
    public:
    Item2(string name, double originalPrice) : Product(name, originalPrice) {}
    double getPrice() {
        cout << "Original price of " << this->name << " is " << this->originalPrice << endl;
        return this->originalPrice;
    }
};