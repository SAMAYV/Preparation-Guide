enum ProductCategory {
    ELECTRONICS,
    CLOTHING,
    BOOKS,
    STATIONERY
};

class Product {
    int id;
    string name;
    double price;
    ProductCategory category;
    public:
    Product(int id, string name, double price, ProductCategory category) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->category = category;
    }
    int getId() {
        return this->id;
    }
};

// All the products in the system
class ProductController {
    map<int, Product*> products;
    public:
    ProductController() {
        this->products = map<int, Product*>();
    }
    Product* addProduct(Product* product) {
        this->products[product->getId()] = product;
        return product;
    }
    Product* getProduct(int productId) {
        return this->products[productId];
    }
};

// Inventory of a warehouse: product to quantity
class Inventory {
    map<Product*, int> productToQuantity;
    public:
    Inventory() {
        this->products = map<Product*, int>();
    }
    void increaseProductQuantity(Product* product, int quantity) {
        this->productToQuantity[product] += quantity;
    }
    void decreaseProductQuantity(Product* product, int quantity) {
        this->productToQuantity[product] -= quantity;
    }
};