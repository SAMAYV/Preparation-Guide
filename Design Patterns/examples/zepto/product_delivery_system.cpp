class ProductDeliverySystem {
    WarehouseController* warehouseController;
    OrderController* orderController;
    UserController* userController;
    // Stores all the products (without quantity)
    ProductController* productController;
    NotificationService* notificationService;
    public:
    ProductDeliverySystem() {
        this->warehouseController = new WarehouseController(new ClosestWarehouseStrategy());
        this->orderController = new OrderController();
        this->userController = new UserController();
        this->productController = new ProductController();
        this->notificationService = new NotificationService();
    }
    // Warehouse operations
    void addWarehouse(Warehouse* warehouse) {
        this->warehouseController->addWarehouse(warehouse);
    }
    // User operations
    User* addUser(string userName) {
        cout << "Adding user to the system: " << userName << endl;
        return this->userController->addUser(userName);
    }
    User* getUser(string userId) {
        return this->userController->getUser(userId);
    }
    // Product operations
    Product* getProduct(int productId) {
        return this->productController->getProduct(productId);
    }
    // Cart operations
    void addProductToCart(string userId, string productId, int quantity) {
        User* user = this->getUser(userId);
        Product* product = this->getProduct(productId);
        cout << "Adding product to cart: " << product->getName() << " for user: " << user->getName() << " with quantity: " << quantity << endl;
        user->getCart()->addItem(product, quantity);
    }
    void removeProductFromCart(string userId, string productId, int quantity) {
        User* user = this->getUser(userId);
        Product* product = this->getProduct(productId);
        cout << "Removing product from cart: " << product->getName() << " for user: " << user->getName() << " with quantity: " << quantity << endl;
        user->getCart()->removeItem(product, quantity);
    }
    // Order operations
    Order* placeOrder(string userId) {
        User* user = this->getUser(userId);
        cout << "Selecting warehouse for user: " << user->getName() << " for placing order: " << orderId << endl;
        Warehouse* warehouse = this->warehouseController->getWarehouse(user->getAddress());
        cout << "Placing order for user: " << user->getName() << endl;
        Order* order = this->orderController->placeOrder(user, warehouse, true);
        this->notificationService->sendNotification(user, order);
        return order;
    }
    void updateOrderStatus(int orderId, OrderStatus status) {
        this->orderController->updateOrderStatus(orderId, status);
        this->notificationService->sendNotification(user, order);
    }
    void cancelOrder(int orderId) {
        this->orderController->cancelOrder(orderId);
    }
    OrderStatus trackOrder(int orderId) {
        return this->orderController->trackOrder(orderId);
    }
    Invoice* generateOrderInvoice(int orderId) {
        return this->orderController->generateOrderInvoice(orderId);
    }
    vector<Order*> getUserOrders(string userId) {
        return this->orderController->getUserOrders(userId);
    }
};