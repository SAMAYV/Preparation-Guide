class NotificationService {
    public:
    void sendNotification(User* user, Order* order) {
        cout << "Sending notification to user: " << user->getName() << " for order: " << order->getOrderId() << endl;
        cout << "Order status: " << order->getStatus() << endl;
    }
};