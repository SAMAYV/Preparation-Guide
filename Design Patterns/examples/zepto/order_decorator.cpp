class OrderDecorator : public Order {
    Order* order;
    public:
    OrderDecorator(Order* order) {
        this->order = order;
    }
    double getAmount() {
        return this->order->getAmount();
    }
};

class TaxDecorator : public OrderDecorator {
    public:
    TaxDecorator(Order* order) : OrderDecorator(order) {}
    double getAmount() {
        cout << "Adding tax to order: " << this->order->getOrderId() << endl;
        return this->order->getAmount() * 1.1;
    }
};

class GiftWrapDecorator : public OrderDecorator {
    public:
    GiftWrapDecorator(Order* order) : OrderDecorator(order) {}
    double getAmount() {
        cout << "Adding gift wrap to order: " << this->order->getOrderId() << endl;
        return this->order->getAmount() + 10;
    }
};