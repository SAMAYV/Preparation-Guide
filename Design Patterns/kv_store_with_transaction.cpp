// https://leetcode.com/discuss/post/279913/bloomberg-onsite-key-value-store-with-tr-kcrv/

class Transaction {
    public:
    map<int, int> store;
    Transaction* next;
    Transaction() {
        this->next = NULL;
    }
    map<int, int> getStore() {
        return this->store;
    }
    void addStore(map<int, int> store) {
        for (auto it : store) {
            this->store[it.first] = it.second;
        }
    }
};

class KVStoreWithTransaction {
    map<int, int> globalStore;
    Transaction* top;
    public:
    KVStoreWithTransaction() {
        this->top = NULL;
    }
    void begin() {
        // Create a new uncommited transaction and make it the top
        Transaction* temp = new Transaction();
        temp->next = this->top;
        this->top = temp;
    }
    void end() {
        // Remove the top uncommited transaction and delete it
        if (this->top != NULL) {
            Transaction* current = this->top;
            this->top = current->next;
            current->next = NULL;
            current->store.clear();
            delete current;
        }
    }
    void commit() {
        Transaction* current = this->top;
        Transaction* newTop = current->next;
        this->top = newTop;
        // If there is a uncommited transaction above this, add this transaction to that transaction
        if (newTop != NULL) {
            newTop->addStore(current->getStore());
        } 
        // If there is no uncommited transaction above this, add this transaction to the global store
        else {
            for (auto it : current->getStore()) {
                this->globalStore[it.first] = it.second;
            }
        }
        delete current;
    }
    void rollback() {
        // If there is a uncommited transaction, clear it
        if (this->top != NULL) {
            this->top->store.clear();
        }
    }
    int get(int key) {
        // If there is a uncommited transaction, return the value from that transaction
        Transaction* current = this->top;
        if (current != NULL) {
            return current->store[key];
        }
        return this->globalStore[key];
    }
    void set(int key, int value) {
        // If there is a uncommited transaction, add the key-value pair to that transaction
        Transaction* current = this->top;
        if (current != NULL) {
            current->store[key] = value;
        } else {
            this->globalStore[key] = value;
        }
    }
    void unset(int key) {
        Transaction* current = this->top;
        if (current != NULL) {
            current->store.erase(key);
        } else {
            this->globalStore.erase(key);
        }
    }
};

int main() {
    KVStoreWithTransaction* store = new KVStoreWithTransaction();
    store->set(1, 3);
    store->set(2, 4);
    store->set(3, 5);
    cout << store->get(1) << endl;
    cout << store->get(2) << endl;
    cout << store->get(3) << endl;
    store->begin();
    store->set(1, 6);
    store->set(2, 7);
    store->set(3, 8);
    cout << store->get(1) << endl;
    cout << store->get(2) << endl;
    cout << store->get(3) << endl;
    store->commit();
    cout << store->get(1) << endl;
    cout << store->get(2) << endl;
    cout << store->get(3) << endl;
    return 0;
}