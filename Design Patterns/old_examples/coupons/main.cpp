int main() {
    ShoppingCart* cart = new ShoppingCart();
    Product* product1 = new Product(1, "Product 1", 10, ProductType::ELECTRONICS);
    Product* product2 = new Product(2, "Product 2", 20, ProductType::CLOTHING);
    cart->addProduct(product1, 1);
    cart->addProduct(product2, 1);
    cart->applyCoupon(product1, CouponType::TYPE);
    cart->applyCoupon(product2, CouponType::PERCENTAGE, 10);
    cout << "Total: " << cart->calculateTotal() << endl;
    return 0;
}