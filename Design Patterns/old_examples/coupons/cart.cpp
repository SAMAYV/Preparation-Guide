class ShoppingCart {
    map<Product*, int> productToQuantity;
    public:
    void addProduct(Product* product, int quantity) {
        this->productToQuantity[product] += quantity;
    }
    void removeProduct(Product* product, int quantity) {
        this->productToQuantity[product] -= quantity;
    }
    double calculateTotal() {
        double total = 0;
        for(auto item : this->productToQuantity) {
            total += item.first->getPrice() * item.second;
        }
        return total;
    }
    void applyCoupon(Product *product, CouponType couponType, double discountPercentage=0) {
        CouponDecorator* coupon = CouponFactory::getCoupon(product, couponType, discountPercentage);
        cout << "Applying coupon " << coupon->getName() << " to product: " << product->getName() << endl;
        // replace product with coupon
        this->productToQuantity[coupon] = this->productToQuantity[product];
        this->productToQuantity.erase(product);
    }
    // NOTE: This will not work as expected because we are erasing the product and not the coupon
    void removeCoupon(Product* coupon) {
        this->productToQuantity.erase(coupon);
    }
};