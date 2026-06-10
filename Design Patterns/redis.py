import os
import time
import pickle
from dataclasses import dataclass
from abc import ABC, abstractmethod
from threading import Thread, RLock


# ==========================================================
# Entry
# ==========================================================

@dataclass
class Entry:
    value: str
    expiry_time: float = time.time()


# ==========================================================
# In Memory Store
# ==========================================================

class KVStore(ABC):
    @abstractmethod
    def put(self, key, value):
        pass
    @abstractmethod
    def get(self, key):
        pass
    @abstractmethod
    def delete(self, key):
        pass
    @abstractmethod
    def expire(self, key, ttl_seconds):
        pass


class InMemoryStore(KVStore):
    def __init__(self):
        self.data = {}
        self.lock = RLock()

    def put(self, key, value):
        with self.lock:
            self.data[key] = Entry(value)

    def get(self, key):
        with self.lock:
            entry = self.data.get(key)

            if not entry:
                return None

            if self._expired(entry):
                del self.data[key]
                return None

            return entry.value

    def delete(self, key):
        with self.lock:
            self.data.pop(key, None)

    def expire(self, key, ttl_seconds):
        with self.lock:
            if key in self.data:
                self.data[key].expiry_time = (
                    time.time() + ttl_seconds
                )

    def cleanup_expired(self):
        with self.lock:
            expired = []
            for key, entry in self.data.items():
                if self._expired(entry):
                    expired.append(key)

            for key in expired:
                del self.data[key]

    def _expired(self, entry):
        return (
            entry.expiry_time is not None
            and entry.expiry_time < time.time()
        )


# ==========================================================
# AOF
# ==========================================================

class AOFPersistence:
    FILE = "appendonly.aof"

    def append(self, command):
        with open(self.FILE, "a") as f:
            f.write(command + "\n")

    def reset(self):
        open(self.FILE, "w").close()

    def replay(self, store: KVStore):
        if not os.path.exists(self.FILE):
            return

        with open(self.FILE) as f:
            for line in f:
                parts = line.strip().split()
                if not parts:
                    continue
                cmd = parts[0]
                if cmd == "PUT":
                    store.put(parts[1], parts[2])
                elif cmd == "DELETE":
                    store.delete(parts[1])
                elif cmd == "EXPIRE":
                    store.expire(parts[1], int(parts[2]))


# ==========================================================
# Snapshot
# ==========================================================

class SnapshotPersistence:
    FILE = "snapshot.rdb"

    def save(self, data):
        with open(self.FILE, "wb") as f:
            pickle.dump(data, f)

    def load(self):
        if not os.path.exists(self.FILE):
            return None
        with open(self.FILE, "rb") as f:
            return pickle.load(f)


# ==========================================================
# Persistence Manager
# ==========================================================

class PersistenceManager:
    def __init__(self):
        self.aof = AOFPersistence()
        self.snapshot = SnapshotPersistence()

    def log(self, command):
        self.aof.append(command)

    def recover(self, store):
        store.data = self.snapshot.load()
        self.aof.replay(store)

    def save_snapshot(self, store):
        self.snapshot.save(store.data)
        self.aof.reset()

# ==========================================================
# Snapshot Thread
# ==========================================================

class SnapshotWorker(Thread):
    def __init__(
        self,
        store,
        persistence,
        interval=30
    ):
        super().__init__(daemon=True)
        self.store = store
        self.persistence: PersistenceManager = persistence
        self.interval = interval

    def run(self):
        while True:
            time.sleep(self.interval)
            self.persistence.save_snapshot(self.store)


# ==========================================================
# Expiry Cleaner
# ==========================================================

class ExpiryCleaner(Thread):
    def __init__(self, store):
        super().__init__(daemon=True)
        self.store = store

    def run(self):
        while True:
            time.sleep(5)
            self.store.cleanup_expired()


# ==========================================================
# Redis Like DB
# ==========================================================

class RedisLikeDB:
    def __init__(self):
        self.store = InMemoryStore()
        self.persistence = PersistenceManager()
        self.persistence.recover(self.store)
        SnapshotWorker(self.store, self.persistence).start()
        ExpiryCleaner(self.store).start()

    def put(self, key, value):
        self.store.put(key, value)
        self.persistence.log(f"PUT {key} {value}")

    def get(self, key):
        return self.store.get(key)

    def delete(self, key):
        self.store.delete(key)
        self.persistence.log(f"DELETE {key}")

    def expire(self, key, ttl):
        self.store.expire(key, ttl)
        self.persistence.log(f"EXPIRE {key} {ttl}")


# ==========================================================
# CLI
# ==========================================================

def main():
    db = RedisLikeDB()

    print("\nMini Redis Started")
    print("------------------")
    print("PUT key value")
    print("GET key")
    print("DELETE key")
    print("EXPIRE key seconds")
    print("EXIT\n")

    while True:
        try:
            command = input("> ").strip()
            if not command:
                continue

            parts = command.split()
            op = (parts[0].upper())

            if op == "PUT":
                db.put(parts[1], parts[2])
                print("OK")
            elif op == "GET":
                print(db.get(parts[1]))
            elif op == "DELETE":
                db.delete(parts[1])
                print("OK")
            elif op == "EXPIRE":
                db.expire(parts[1], int(parts[2]))
                print("OK")
            elif op == "EXIT":
                print("Bye")
                break
            else:
                print("Unknown command")
        except Exception as e:
            print("Error:", e)


if __name__ == "__main__":
    main()
