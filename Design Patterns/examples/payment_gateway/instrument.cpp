enum InstrumentType {
    BANK,
    CARD
};

class Instrument {
    int instrumentId;
    int userId;
    InstrumentType type;
    public:
    Instrument(int instrumentId, int userId, InstrumentType type) {
        this->instrumentId = instrumentId;
        this->userId = userId;
        this->type = type;
    }
};

class BankInstrument : public Instrument {
    string accountNumber;
    string ifscCode;
    public:
    BankInstrument(int instrumentId, int userId, string accountNumber, string ifscCode) : Instrument(instrumentId, userId, InstrumentType::BANK) {
        this->accountNumber = accountNumber;
        this->ifscCode = ifscCode;
    }
};

class CardInstrument : public Instrument {
    string cardNumber;
    string cvv;
    public:
    CardInstrument(int instrumentId, int userId, string cardNumber, string cvv) : Instrument(instrumentId, userId, InstrumentType::CARD) {
        this->cardNumber = cardNumber;
        this->cvv = cvv;
    }
};
