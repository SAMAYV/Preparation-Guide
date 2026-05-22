#include <shared_mutex>
#include <unordered_map>
#include <string>
#include <optional>
using namespace std;

class Cache {
private:
    mutable shared_mutex rwMutex;
    unordered_map<string, string> data;

public:
    optional<string> get(const string& key) {
        shared_lock lock(rwMutex);
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        return nullopt;
    }

    void put(const string& key, const string& value) {
        unique_lock lock(rwMutex);
        data[key] = value;
    }
};
