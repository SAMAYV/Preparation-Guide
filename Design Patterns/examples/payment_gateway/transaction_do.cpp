class TransactionDO {
    int transactionId;
    double amount;
    TransactionStatus status;
    int senderUserId;
    int receiverUserId;
    int debitInstrumentId;
    int creditInstrumentId;
    public:
    TransactionDO(int transactionId, double amount, int senderUserId, int receiverUserId, int debitInstrumentId, int creditInstrumentId) {
        this->transactionId = transactionId;
        this->amount = amount;
        this->status = TransactionStatus::PENDING;
        this->senderUserId = senderUserId;
        this->receiverUserId = receiverUserId;
        this->debitInstrumentId = debitInstrumentId;
        this->creditInstrumentId = creditInstrumentId;
    }
    int getTransactionId() {
        return this->transactionId;
    }
    double getAmount() {
        return this->amount;
    }
    TransactionStatus getStatus() {
        return this->status;
    }
    int getSenderUserId() {
        return this->senderUserId;
    }
    int getReceiverUserId() {
        return this->receiverUserId;
    }
    int getDebitInstrumentId() {
        return this->debitInstrumentId;
    }
    int getCreditInstrumentId() {
        return this->creditInstrumentId;
    }
    void setStatus(TransactionStatus status) {
        this->status = status;
    }
    void setAmount(double amount) {
        this->amount = amount;
    }
    void setSenderUserId(int senderUserId) {
        this->senderUserId = senderUserId;
    }
    void setReceiverUserId(int receiverUserId) {
        this->receiverUserId = receiverUserId;
    }
    void setDebitInstrumentId(int debitInstrumentId) {
        this->debitInstrumentId = debitInstrumentId;
    }
    void setCreditInstrumentId(int creditInstrumentId) {
        this->creditInstrumentId = creditInstrumentId;
    }
};
