class PaymentProcessor {
    InstrumentServiceFactory* instrumentServiceFactory;
    public:
    PaymentProcessor() {
        this->instrumentServiceFactory = new InstrumentServiceFactory();
    }
    bool processPayment(InstrumentDO* senderInstrument, InstrumentDO* receiverInstrument, double amount) {
        cout << "Processing payment of " << amount << " from " << senderInstrument->getInstrumentId() << " to " << receiverInstrument->getInstrumentId() << endl;
        // validate sender instrument
        if (!this->validateInstrument(senderInstrument) || !this->validateInstrument(receiverInstrument)) {
            cout << "Invalid sender or receiver instrument" << endl;
            return false;
        }
        // process payment
        cout << "Payment successful | Money has been sent from " << senderInstrument->getInstrumentId() << " to " << receiverInstrument->getInstrumentId() << endl;
        return true;
    }
    bool validateInstrument(InstrumentDO* instrument) {
        // validate instrument
        InstrumentService* instrumentService = this->instrumentServiceFactory->getInstrumentService(instrument->getType());
        return instrumentService->validateInstrument(instrument);
    }
}