// Data object used at client side
class InstrumentDO {
    int instrumentId;
    int userId;
    InstrumentType type;
    string accountNumber;
    string ifscCode;
    string cardNumber;
    string cvv;
    public:
    InstrumentDO(int instrumentId, int userId, InstrumentType type) {
        this->instrumentId = instrumentId;
        this->userId = userId;
        this->type = type;
    }
    int getInstrumentId() {
        return this->instrumentId;
    }
    int getUserId() {
        return this->userId;
    }
    InstrumentType getType() {
        return this->type;
    }
    string getAccountNumber() {
        return this->accountNumber;
    }
    string getIfscCode() {
        return this->ifscCode;
    }
    string getCardNumber() {
        return this->cardNumber;
    }
    string getCvv() {
        return this->cvv;
    }
    void setAccountNumber(string accountNumber) {
        this->accountNumber = accountNumber;
    }
    void setIfscCode(string ifscCode) {
        this->ifscCode = ifscCode;
    }
    void setCardNumber(string cardNumber) {
        this->cardNumber = cardNumber;
    }
    void setCvv(string cvv) {
        this->cvv = cvv;
    }
};