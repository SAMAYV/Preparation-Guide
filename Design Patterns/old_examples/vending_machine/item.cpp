enum ItemType {
    COKE,
    SPRITE,
    FANTA
}

class Item {
    ItemType type;
    int price;
    public:
    Item(ItmeType type, int price) {
        this->type = type;
        this->price = price;
    }
    int getPrice() {
        return this->price;
    }
};

class ItemShelf {
    Item* item;
    int count;
    public:
    ItemShelf(Item* item, int count) {
        this->item = item;
        this->count = count;
    }
    void addItem(Item* item) {
        this->count++;
    }
    void removeItem() {
        this->count--;
    }
};

class Inventory {
    // Key is codeNumber
    map<int, ItemShelf*> itemShelves;
    public:
    Inventory() {
        this->itemShelves = map<int, ItemShelf*>();
    }
    void addItem(Item* item, int codeNumber) {
        if (this->itemShelves[codeNumber] == NULL) {
            this->itemShelves[codeNumber] = new ItemShelf(item, 1);
        }
        else {
            this->itemShelves[codeNumber]->addItem(item);
        }
    }
    void updateItemCount(int codeNumber) {
        this->itemShelves[codeNumber]->removeItem();
    }
};