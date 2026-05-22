enum TransactionStatus {
    PENDING,
    SUCCESS,
    FAILED,
    REFUNDED,
    CANCELLED
};

class Transaction {
    int transactionId;
    double amount;
    TransactionStatus status;
    int senderUserId;
    int receiverUserId;
    int debitInstrumentId;
    int creditInstrumentId;
    public:
    Transaction(int transactionId, double amount, int senderUserId, int receiverUserId, int debitInstrumentId, int creditInstrumentId) {
        this->transactionId = transactionId;
        this->amount = amount;
        this->senderUserId = senderUserId;
        this->receiverUserId = receiverUserId;
        this->debitInstrumentId = debitInstrumentId;
        this->creditInstrumentId = creditInstrumentId;
        this->status = TransactionStatus::PENDING;
    }
    void setStatus(TransactionStatus status) {
        this->status = status;
    }
};

class TransactionService {
    map<int, vector<Transaction*>> userToTransactions;
    InstrumentController* instrumentController;
    PaymentProcessor* processor;
    public:
    TransactionService() {
        this->userToTransactions = map<int, vector<Transaction*>>();
        this->instrumentController = new InstrumentController();
        this->processor = new Processor();
    }
    TransactionDO* createTransaction(TransactionDO* transactionDO) {
        Transaction* transaction = new Transaction(transactionDO->getTransactionId(), transactionDO->getAmount(), transactionDO->getSenderUserId(), transactionDO->getReceiverUserId(), transactionDO->getDebitInstrumentId(), transactionDO->getCreditInstrumentId());
        // get sender instrument to pass to processors
        InstrumentDO* senderInstrument = this->instrumentController->getInstrumentById(transaction->getSenderUserId(), transaction->getDebitInstrumentId());
        // get receiver instrument to pass to processors
        InstrumentDO* receiverInstrument = this->instrumentController->getInstrumentById(transaction->getReceiverUserId(), transaction->getCreditInstrumentId());
        // process transaction
        bool isPaymentSuccessful = this->processor->processPayment(senderInstrument, receiverInstrument, transaction->getAmount());
        if (isPaymentSuccessful) {
            transaction->setStatus(TransactionStatus::SUCCESS);
        } else {
            transaction->setStatus(TransactionStatus::FAILED);
        }
        // save transaction to db
        this->userToTransactions[transaction->getSenderUserId()].push_back(transaction);
        this->userToTransactions[transaction->getReceiverUserId()].push_back(transaction);
        // return transaction
        transactionDO->setStatus(transaction->getStatus());
        transactionDO->setTransactionId(transaction->getTransactionId());
        return transactionDO;
    }
    vector<TransactionDO*> getTransactionHistory(int userId) {
        vector<TransactionDO*> transactionHistory;
        for (Transaction* transaction : this->userToTransactions[userId]) {
            transactionHistory.push_back(this->mapToTransactionDO(transaction));
        }
        return transactionHistory;
    }
    TransactionDO* mapToTransactionDO(Transaction* transaction) {
        return new TransactionDO(transaction->transactionId, transaction->amount, transaction->status, transaction->senderUserId, transaction->receiverUserId, transaction->debitInstrumentId, transaction->creditInstrumentId);
    }
};

class TransactionController {
    TransactionService* transactionService;
    public:
    TransactionController() {
        this->transactionService = new TransactionService();
    }
    TransactionDO* createTransaction(TransactionDO* transaction) {
        return this->transactionService->createTransaction(transaction);
    }
    vector<TransactionDO*> getTransactionHistory(int userId) {
        return this->transactionService->getTransactions(userId);
    }
};