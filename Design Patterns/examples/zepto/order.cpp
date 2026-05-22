enum OrderStatus {
    PLACED,
    SHIPPED,
    DELIVERED,
    CANCELLED,
    RETURNED,
    PAYMENT_FAILED
};

class Order {
    int orderId;
    User* user;
    map<Product*, int> productToQuantity;
    Warehouse* warehouse;
    Address* deliveryAddress;
    double totalAmount;
    OrderStatus status;
    PaymentService* paymentService;
    // Can also add order state
    public:
    Order(int orderId, User* user, Warehouse* warehouse) {
        this->orderId = orderId;
        this->user = user;
        this->warehouse = warehouse;
        this->populateProducts();
        this->deliveryAddress = user->getAddress();
        this->status = OrderStatus::PENDING_PAYMENT;
        this->calculateTotalAmount();
        this->paymentService = new PaymentService(new UPIPaymentStrategy());
        this->invoice = new Invoice(this);
    }
    // populate products from cart
    void populateProducts() {
        for(CartItem* item : this->user->getCart()->getItems()) {
            this->productToQuantity[item->getProduct()] = item->getQuantity();
        }
    }
    void calculateTotalAmount() {
        this->totalAmount = 0;
        for(auto item : this->productToQuantity) {
            this->totalAmount += item.first->getPrice() * item.second;
        }
    }
    double getAmount() {
        return this->totalAmount;
    }
    void cancelOrder() {
        // Refund money to user
        this->status = OrderStatus::CANCELLED;
    }
    void placeOrder() {
        cout << "Placing order for user: " << this->user->getName() << endl;
        // Fulfill order
        this->warehouse->fulfillOrder(this);
        // Collect payment
        bool isPaymentSuccessful = this->paymentService->collectPayment(this->user, this->totalAmount);
        if (isPaymentSuccessful) {
            this->status = OrderStatus::PLACED;
            // Empty cart
            this->user->getCart()->emptyCart();
        }
        else {
            this->status = OrderStatus::PAYMENT_FAILED;
            this->warehouse->revertOrder(this);
        }
    }
    OrderStatus getStatus() {
        return this->status;
    }
    void setStatus(OrderStatus status) {
        this->status = status;
    }
};

class OrderController {
    map<int, Order*> orders;
    map<int, vector<int>> userIdToOrderIds; // For user id to order ids mapping
    InvoiceGenerator* invoiceGenerator;
    public:
    OrderController() {
        this->orders = map<int, Order*>();
        this->invoiceGenerator = new InvoiceGenerator();
    }
    Order* placeOrder(User* user, Warehouse* warehouse, bool isGiftWrap=false) {
        int orderId = this->generateOrderId();
        Order* order = new Order(orderId, user, warehouse);
        if (isGiftWrap) {
            order = new GiftWrapDecorator(order);
        }
        order = new TaxDecorator(order);
        order->placeOrder();
        this->orders[orderId] = order;
        this->userIdToOrderIds[user->getId()].push_back(orderId);
        return order;
    }
    void cancelOrder(int orderId) {
        Order* order = this->orders[orderId];
        order->cancelOrder();
    }
    OrderStatus trackOrder(int orderId) {
        return this->orders[orderId]->getStatus();
    }
    Invoice* generateOrderInvoice(int orderId) {
        return this->invoiceGenerator->generateInvoice(this->orders[orderId]);
    }
    vector<Order*> getUserOrders(int userId) {
        vector<Order*> userOrders;
        for(int orderId : this->userIdToOrderIds[userId]) {
            userOrders.push_back(this->orders[orderId]);
        }
        return userOrders;
    }
    void updateOrderStatus(int orderId, OrderStatus status) {
        this->orders[orderId]->setStatus(status);
    }
};