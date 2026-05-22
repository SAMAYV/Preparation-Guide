#include<bits/stdc++.h>
using namespace std;

class Object {
    // Some resource intensive object
    public:
    int id;
    Object(int id) {
        cout << "Object " << id << " created" << endl;
        this->id = id;
    }
    void doWork() {
        cout << "Object " << this->id << " is doing work" << endl;
    }
};

class ObjectPool {
    queue<shared_ptr<Object>> pool;
    mutex poolMutex;
    int maxPoolSize;

    public:
    ObjectPool(int maxPoolSize) {
        this->maxPoolSize = maxPoolSize;
        for(int i = 0; i < maxPoolSize; i++) {
            this->pool.push(make_shared<Object>(i));
        }
    }

    shared_ptr<Object> aquireObject() {
        unique_lock<mutex> lock(this->poolMutex);
        if(this->pool.empty()) {
            return NULL;
        }
        shared_ptr<Object> obj = this->pool.front();
        cout << "Thread " << this_thread::get_id() << " aquired object " << obj->id << endl;
        this->pool.pop();
        return obj;
    }

    void releaseObject(shared_ptr<Object> obj) {
        unique_lock<mutex> lock(this->poolMutex);
        this->pool.push(obj);
        cout << "Thread " << this_thread::get_id() << " released object " << obj->id << endl;
    }
};

void worker(ObjectPool& pool) {
    for (int i = 0; i < 10; i++) {
        shared_ptr<Object> obj = pool.aquireObject();
        if(obj) {
            int worked_for = rand() % 100;
            obj->doWork();
            this_thread::sleep_for(chrono::milliseconds(worked_for));
            pool.releaseObject(obj);
        }
        else {
            cout << "Thread " << this_thread::get_id() << " could not aquire object" << endl;
        }
    }
}

int main() {
    ObjectPool pool(5);
    vector<thread> workers;
    for(int i = 0; i < 10; i++) {
        workers.push_back(thread(worker, ref(pool)));
    }
    for(auto& w: workers) {
        w.join();
    }
    return 0;
}