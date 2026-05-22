class Invoice {
    int invoiceId;
    Order* order;
    public:
    Invoice(int invoiceId, Order* order) {
        this->order = order;
    }
    Json getInvoice() {
        // Generate invoice
        return {
            "invoiceId": this->invoiceId,
            "orderId": this->order->getOrderId(),
            "totalAmount": this->order->getTotalAmount(),
            "status": this->order->getStatus()
        };
    }
};

class InvoiceGenerator {
    public:
    Invoice* generateInvoice(Order* order) {
        return new Invoice(this->generateInvoiceId(), order);
    }
};