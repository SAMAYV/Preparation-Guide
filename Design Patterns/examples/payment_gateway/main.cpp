int main() {
    PaymentGateway* paymentGateway = new PaymentGateway();
    // create users
    User* user1 = paymentGateway->createUser(1, "User 1");
    User* user2 = paymentGateway->createUser(2, "User 2");

    // add instruments
    InstrumentDO* user1CardInstrument = new InstrumentDO(1, user1->getUserId(), InstrumentType::CARD);
    user1CardInstrument->setCardNumber("1234567890123456");
    user1CardInstrument->setCvv("123");
    paymentGateway->addInstrument(user1CardInstrument);
    InstrumentDO* user1BankInstrument = new InstrumentDO(2, user1->getUserId(), InstrumentType::BANK);
    user1BankInstrument->setAccountNumber("1234567890123456");
    user1BankInstrument->setIfscCode("123456789012");
    paymentGateway->addInstrument(user1BankInstrument);

    InstrumentDO* user2BankInstrument = new InstrumentDO(2, user2->getUserId(), InstrumentType::BANK);
    user2BankInstrument->setAccountNumber("1234567890123456");
    user2BankInstrument->setIfscCode("123456789012");
    paymentGateway->addInstrument(user2BankInstrument);

    // create transaction
    TransactionDO* transaction = new TransactionDO(1, 100.0, user1->getUserId(), user2->getUserId(), user1CardInstrument->getInstrumentId(), user2BankInstrument->getInstrumentId());
    paymentGateway->createTransaction(transaction);
    // get transaction history
    vector<TransactionDO*> transactionHistory = paymentGateway->getTransactionHistory(user1->getUserId());
    for (TransactionDO* transaction : transactionHistory) {
        cout << "Transaction id: " << transaction->getTransactionId() << " | Amount: " << transaction->getAmount() << " | Status: " << transaction->getStatus() << endl;
    }
    return 0;
}