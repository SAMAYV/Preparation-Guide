int main() {
    ProductDeliverySystem* system = new ProductDeliverySystem();
    // Create products
    Product* product1 = new Product(1, "Product 1", 10, ProductCategory::ELECTRONICS);
    Product* product2 = new Product(2, "Product 2", 20, ProductCategory::CLOTHING);
    system->addProduct(product1);
    system->addProduct(product2);
    // Create warehouses
    Inventory* wh1Inventory = new Inventory();
    inventory1->increaseProductQuantity(product1, 10);
    inventory1->increaseProductQuantity(product2, 20);
    Address* wh1Address = new Address("123", "Bangalore", "Karnataka");
    Warehouse* warehouse1 = new Warehouse(wh1Inventory, wh1Address);
    system->addWarehouse(warehouse1);
    // Create user
    User* user1 = system->addUser("User 1");
    // Add products to cart
    system->addProductToCart(user1->getId(), product1->getId(), 1);
    system->addProductToCart(user1->getId(), product2->getId(), 2);
    // Place order
    Order* order = system->placeOrder(user1->getId());
    // Track order
    cout << "Order status: " << system->trackOrder(order->getOrderId()) << endl;
    // Generate invoice
    Invoice* invoice = system->generateOrderInvoice(order->getOrderId());
    // Get user orders
    vector<Order*> userOrders = system->getUserOrders(user1->getId());
    for(Order* order : userOrders) {
        cout << "Order id: " << order->getOrderId() << endl;
    }
    return 0;
}