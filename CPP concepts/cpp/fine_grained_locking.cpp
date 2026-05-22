#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <string>
#include <memory>
using namespace std;

class TicketBookingFineGrained {
private:
    mutex locksMutex;
    // unique_ptr<mutex> is used to point to mutexes created on the heap.
    unordered_map<string, unique_ptr<mutex>> seatLocks;
    unordered_map<string, string> seatOwners;

    mutex& getLock(const string& seatId) {
        lock_guard<mutex> lock(locksMutex);
        if (seatLocks.find(seatId) == seatLocks.end()) {
            seatLocks[seatId] = make_unique<mutex>();
        }
        return *seatLocks[seatId];
    }
public:
    bool bookSeat(const string& seatId, const string& visitorId) {
        lock_guard<mutex> seatLock(getLock(seatId));
        if (seatOwners.find(seatId) != seatOwners.end()) {
            return false;
        }
        seatOwners[seatId] = visitorId;
        return true;
    }
    bool swapSeats(const string& visitor1, const string& seat1, const string& visitor2, const string& seat2) {
        // Always acquire locks in consistent order to prevent deadlock
        const string& first = seat1 < seat2 ? seat1 : seat2;
        const string& second = seat1 < seat2 ? seat2 : seat1;
        // scoped_lock acquires multiple locks without deadlock
        scoped_lock lock(getLock(first), getLock(second));
        // ... perform swap
        return true;
    }
};
