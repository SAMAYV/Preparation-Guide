class PaymentGateway {
    UserController* userController;
    InstrumentController* instrumentController;
    TransactionController* transactionController;
    public:
    PaymentGateway() {
        this->userController = new UserController();
        this->instrumentController = new InstrumentController();
        this->transactionController = new TransactionController();
    }
    // User operations
    User* getUser(int userId) {
        return this->userController->getUser(userId);
    }
    User* createUser(int userId, string userName) {
        return this->userController->createUser(user);
    }
    // Instrument operations
    InstrumentDO* getInstrumentById(int userId, int instrumentId) {
        return this->instrumentController->getInstrumentById(userId, instrumentId);
    }
    InstrumentDO* addInstrument(InstrumentDO* instrument) {
        return this->instrumentController->addInstrument(instrument);
    }
    vector<InstrumentDO*> getInstruments(int userId) {
        return this->instrumentController->getInstruments(userId);
    }
    // Transaction operations
    TransactionDO* createTransaction(TransactionDO* transaction) {
        return this->transactionController->createTransaction(transaction);
    }
    vector<TransactionDO*> getTransactionHistory(int userId) {
        return this->transactionController->getTransactionHistory(userId);
    }
};