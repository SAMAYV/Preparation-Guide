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
class KnifeType1 : public Knife {
    void sharpen() {
        cout << "Sharpening knife type 1" << endl;
    }
};

class KnifeType2 : public Knife {
    void sharpen() {
        cout << "Sharpening knife type 2" << endl;
    }
};


// Creator
class KnifeStore {
    KnifeStore(KnifeStoreFactory* factory) {
        this->factory = factory;
    }
    void orderKnife(KnifeType knifeType) {
        Knife* knife = factory.createKnife(knifeType);
        knife->sharpen();
    }
};

// Factory
class KnifeStoreFactory {
    Knife* createKnife(KnifeType knifeType) {
        if (knifeType == KnifeType.KNIFE_TYPE_1) {
            return new KnifeType1();
        } else if (knifeType == KnifeType.KNIFE_TYPE_2) {
            return new KnifeType2();
        }
    }
}

void main() {
    KnifeStore* store = new KnifeStore(new KnifeStoreFactory());
    store->orderKnife(KnifeType.KNIFE_TYPE_1);
}