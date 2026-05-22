enum KnifeType {
    KNIFE_TYPE_1,
    KNIFE_TYPE_2
};

// Product
class Knife {
    int sharpness;
    public:
    virtual void sharpen() = 0;
};

// Concrete Product
class ChefKnifeType1 : public Knife {
    public:
    void sharpen() {
        cout << "Sharpening chef knife type 1" << endl;
    }
};

class ChefKnifeType2 : public Knife {
    public:
    void sharpen() {
        cout << "Sharpening chef knife type 2" << endl;
    }
};

class BudgetKnifeType1 : public Knife {
    public:
    void sharpen() {
        cout << "Sharpening budget knife type 1" << endl;
    }
};

class BudgetKnifeType2 : public Knife {
    public:
    void sharpen() {
        cout << "Sharpening budget knife type 2" << endl;
    }
};

// Creator
class KnifeStore {
    public:
    void orderKnife(KnifeType knifeType) {
        Knife* knife = createKnife(knifeType);
        knife->sharpen();
    }
    virtual Knife* createKnife(KnifeType knifeType) = 0;
};

// Concrete Creator
class ChefKnifeStore : public KnifeStore {
    public:
    Knife* createKnife(KnifeType knifeType) {
        if (knifeType == KnifeType.KNIFE_TYPE_1) {
            return new ChefKnifeType1();
        } else if (knifeType == KnifeType.KNIFE_TYPE_2) {
            return new ChefKnifeType2();
        }
    }
};

class BudgetKnifeStore : public KnifeStore {
    public:
    Knife* createKnife(KnifeType knifeType) {
        if (knifeType == KnifeType.KNIFE_TYPE_1) {
            return new BudgetKnifeType1();
        } else if (knifeType == KnifeType.KNIFE_TYPE_2) {
            return new BudgetKnifeType2();
        }
    }
};

void main() {
    KnifeStore* store = new ChefKnifeStore();
    store->orderKnife(KnifeType.KNIFE_TYPE_1);
}