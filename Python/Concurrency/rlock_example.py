import threading

class BankAccount:
    def __init__(self, balance):
        self.balance = balance
        self.lock = threading.RLock()  # Use RLock for nested calls
    
    def deposit(self, amount):
        with self.lock:
            self.balance += amount
            print(f"Deposited ${amount}, balance: ${self.balance}")
    
    def withdraw(self, amount):
        with self.lock:
            if self.balance >= amount:
                self.balance -= amount
                print(f"Withdrew ${amount}, balance: ${self.balance}")
                return True
            return False
    
    def transfer_to(self, other_account: 'BankAccount', amount):
        """Nested locking - withdraw calls lock, deposit calls lock"""
        with self.lock:  # Outer lock
            if self.withdraw(amount):  # Inner lock (same lock!)
                other_account.deposit(amount)  # Other account's lock
                print(f"Transfer of ${amount} complete")
                return True
            return False

# Test
account1 = BankAccount(1000)
account2 = BankAccount(500)

account1.transfer_to(account2, 200)