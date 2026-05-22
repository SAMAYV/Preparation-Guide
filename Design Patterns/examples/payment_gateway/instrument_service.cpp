class InstrumentServiceFactory {
    public:
    static InstrumentService* getInstrumentService(InstrumentType type) {
        if (type == InstrumentType::BANK) {
            return new BankService();
        } else if (type == InstrumentType::CARD) {
            return new CardService();
        }
        return NULL;
    }
};

class InstrumentController {
    InstrumentServiceFactory* instrumentServiceFactory;
    public:
    InstrumentController() {
        this->instrumentServiceFactory = new InstrumentServiceFactory();
    }
    vector<InstrumentDO*> getInstruments(int userId) {
        InstrumentService* bankService = this->instrumentServiceFactory->getInstrumentService(InstrumentType::BANK);
        vector<InstrumentDO*> bankInstruments = bankService->getInstruments(userId);
        InstrumentService* cardService = this->instrumentServiceFactory->getInstrumentService(InstrumentType::CARD);
        vector<InstrumentDO*> cardInstruments = cardService->getInstruments(userId);
        vector<InstrumentDO*> allInstruments;
        allInstruments.insert(allInstruments.end(), bankInstruments.begin(), bankInstruments.end());
        allInstruments.insert(allInstruments.end(), cardInstruments.begin(), cardInstruments.end());
        return allInstruments;
    }
    InstrumentDO* getInstrumentById(int userId, int instrumentId) {
        vector<InstrumentDO*> instruments = this->getAllInstruments(userId);
        for (InstrumentDO* instrument : instruments) {
            if (instrument->getInstrumentId() == instrumentId) {
                return instrument;
            }
        }
        return NULL;
    }
    InstrumentDO* addInstrument(InstrumentDO* instrument) {
        InstrumentService* instrumentService = this->instrumentServiceFactory->getInstrumentService(instrument->getType());
        return instrumentService->addInstrument(instrument);
    }
};

class InstrumentService {
    public:
    map<int, vector<Instrument*>> userToInstruments;
    InstrumentService() {
        this->instruments = map<int, Instrument*>();
    }
    bool validateInstrument(InstrumentDO* instrument) {
        cout << "Validating if instrument exists in user's account" << endl;
        vector<Instrument*> instruments = this->userToInstruments[instrument->getUserId()];
        if (instruments.find(instrument->getInstrumentId()) == instruments.end()) {
            return false;
        }
        return true;
    }
    virtual vector<InstrumentDO*> getInstruments(int userId) = 0;
    virtual InstrumentDO* addInstrument(IntstrumentDO* instrument) = 0;
};

class BankService : public InstrumentService {
    public:
    vector<InstrumentDO*> getInstruments(int userId) {
        vector<InstrumentDO*> bankInstruments;
        for (auto instrument : this->userToInstruments[userId]) {
            if (instrument->type == InstrumentType::BANK) {
                bankInstruments.push_back(this->mapToInstrumentDO(instrument));
            }
        }
        return bankInstruments;
    }
    InstrumentDO* addInstrument(InstrumentDO* instrument) {
        Instrument* bankInstrument = new BankInstrument(instrument->getInstrumentId(), instrument->getUserId(), instrument->getAccountNumber(), instrument->getIfscCode());
        this->userToInstruments[bankInstrument->userId].push_back(bankInstrument);
        return this->mapToInstrumentDO(bankInstrument);
    }
    bool validateInstrument(InstrumentDO* instrument) {
        // validate if instrument exists
        if (!InstrumentService::validateInstrument(instrument)) {
            return false;
        }
        cout << "Validating bank instrument" << endl;
        // validate bank instrument
        if (instrument->getAccountNumber().empty() || instrument->getIfscCode().empty()) {
            return false;
        }
        return true;
    }
    InstrumentDO* mapToInstrumentDO(Instrument* instrument) {
        InstrumentDO* instrumentDO = new InstrumentDO(instrument->instrumentId, instrument->userId, instrument->type);
        instrumentDO->setAccountNumber(((BankInstrument*)instrument)->getAccountNumber());
        instrumentDO->setIfscCode(((BankInstrument*)instrument)->getIfscCode());
    }
};

class CardService : public InstrumentService {
    public:
    vector<InstrumentDO*> getInstruments(int userId) {
        vector<Instrument*> cardInstruments;
        for (auto instrument : this->userToInstruments[userId]) {
            if (instrument->type == InstrumentType::CARD) {
                cardInstruments.push_back(this->mapToInstrumentDO(instrument));
            }
        }
        return cardInstruments;
    }
    InstrumentDO* addInstrument(InstrumentDO* instrument) {
        Instrument* cardInstrument = new CardInstrument(instrument->getInstrumentId(), instrument->getUserId(), instrument->getCardNumber(), instrument->getCvv());
        this->userToInstruments[cardInstrument->userId].push_back(cardInstrument);
        return this->mapToInstrumentDO(cardInstrument);
    }
    InstrumentDO* mapToInstrumentDO(Instrument* instrument) {
        InstrumentDO* instrumentDO = new InstrumentDO(instrument->instrumentId, instrument->userId, instrument->type);
        instrumentDO->setCardNumber(((CardInstrument*)instrument)->getCardNumber());
        instrumentDO->setCvv(((CardInstrument*)instrument)->getCvv());
    }
    bool validateInstrument(InstrumentDO* instrument) {
        // validate if instrument exists
        if (!InstrumentService::validateInstrument(instrument)) {
            return false;
        }
        cout << "Validating card instrument" << endl;
        // validate card instrument
        if (instrument->getCardNumber().empty() || instrument->getCvv().empty()) {
            return false;
        }
        return true;
    }
};