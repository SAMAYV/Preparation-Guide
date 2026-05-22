class CartItem {
    Product* product;
    int quantity;
    public:
    CartItem(Product* product, int quantity) {
        this->product = product;
        this->quantity = quantity;
    }
    void increaseQuantity(int quantity=1) {
        this->quantity += quantity;
    }
    void decreaseQuantity(int quantity=1) {
        this->quantity -= quantity;
    }
};

class Cart {
    vector<CartItem*> items;
    public:
    Cart() {
        this->items = vector<CartItem*>();
    }
    void addItem(Product* product, int quantity) {
        // Check if item already exists
        for(CartItem* item : this->items) {
            if (item->getProduct() == product) {
                item->increaseQuantity(quantity);
                return;
            }
        }
        // Item does not exist
        CartItem* item = new CartItem(product, quantity);
        this->items.push_back(item);
    }
    void removeItem(Product* product, int quantity) {
        // Check if item exists
        for(CartItem* item : this->items) {
            if (item->getProduct() == product) {
                item->decreaseQuantity(quantity);
                if (item->getQuantity() <= 0) {
                    this->items.erase(this->items.find(item));
                }
            }
        }
    }
    void emptyCart() {
        this->items.clear();
    }
};