class CardDetails {
    string cardNumber;
    string expiryDate;
    public:
    CardDetails(string cardNumber) {
        this->cardNumber = cardNumber;
    }
    string getCardNumber() {
        return this->cardNumber;
    }
};