class Split {
    User* user;
    double amountOwe;
    double percentage;
    public:
    Split(User* user, double amountOwe=0, double percentage=0) {
        this->user = user;
        this->amountOwe = amountOwe;
        this->percentage = percentage;
    }
    User* getUser() {
        return this->user;
    }
    double getAmountOwe() {
        return this->amountOwe;
    }
    double getPercentage() {
        return this->percentage;
    }
};

class ExpenseSplit {
    public:
    virtual bool validate(vector<Split*> splits, double amount) = 0;
    virtual vector<Split*> splitAmount(vector<Split*> splits, double amount) = 0;
};

class EqualSplit : public ExpenseSplit {
    public:
    EqualSplit() {}
    bool validate(vector<Split*> splits, double amount) {
        return true;
    }
    vector<Split*> splitAmount(vector<Split*> splits, double amount) {
        vector<Split*> newSplits;
        double splitAmount = amount / splits.size();
        for (auto split : splits) {
            double splitPercentage = 100 / splits.size();
            newSplits.push_back(new Split(split->getUser(), splitPercentage, splitAmount));
        }
        return newSplits;
    }
};

class PercentSplit : public ExpenseSplit {
    public:
    PercentSplit() {}
    bool validate(vector<Split*> splits, double amount) {
        return true;
    }
    vector<Split*> splitAmount(vector<Split*> splits, double amount) {
        vector<Split*> newSplits;
        for (auto split : splits) {
            double splitAmount = (amount * split->getPercentage()) / 100;
            newSplits.push_back(new Split(split->getUser(), split->getPercentage(), splitAmount));
        }
        return newSplits;
    }
};

class ExactSplit : public ExpenseSplit {
    public:
    ExactSplit() {}
    bool validate(vector<Split*> splits, double amount) {
        return true;
    }
    vector<Split*> splitAmount(vector<Split*> splits, double amount) {
        return new vector<Split*>(splits);
    }
};

enum ExpenseSplitType {
    EQUAL,
    PERCENT,
    EXACT
};

class SplitTypeFactory {
    public:
    static ExpenseSplit* getSplitType(ExpenseSplitType splitType) {
        if (splitType == ExpenseSplitType::EQUAL) {
            return new EqualSplit();
        } else if (splitType == ExpenseSplitType::PERCENT) {
            return new PercentSplit();
        } else if (splitType == ExpenseSplitType::EXACT) {
            return new ExactSplit();
        } else {
            return NULL;
        }
    }
};