enum AccountType {
    SAVINGS,
    CURRENT
}

class Account {
    int balance, accountNumber;
    public:
    Account(int balance) {
        this->accountNumber = rand() % 1000000;
        this->balance = balance;
    }
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
    virtual void transfer(int amount) = 0;
    int getBalance() {
        return balance;
    };
    int getAccountNumber() {
        return accountNumber;
    }
}

class SavingsAccount : public Account {
    public:
    SavingsAccount(int balance) : Account(balance) {}
    void deposit(int amount) {
        balance += amount;
    }
    void withdraw(int amount) {
        balance -= amount;
    }
}

class CurrentAccount : public Account {
    CurrentAccount(int balance) : Account(balance) {}
    public:
    void deposit(int amount) {
        balance += amount;
    }
    void withdraw(int amount) {
        balance -= amount;
    }
}

class BankService {
    map<int, Account> bankAccounts;
    public:
    BankService() {
        this->bankAccounts = new map<int, Account>();
    }
    int createAccount(AccountType accountType, int amount) {
        Account* account;
        if (accountType == AccountType.SAVINGS) {
            account = new SavingsAccount();
        } else if (accountType == AccountType.CURRENT) {
            account = new CurrentAccount();
        } else {
            cout << "Invalid account type" << endl;
        }
        if (account != NULL) {
            bankAccounts[account->getAccountNumber()] = account;
        }
        return -1;
    }
    void transfer(int fromAccountNumber, int toAccountNumber, int amount) {
        Account* fromAccount = bankAccounts[fromAccountNumber];
        Account* toAccount = bankAccounts[toAccountNumber];
        fromAccount->withdraw(amount);
        toAccount->deposit(amount);
    }
}

void main() {
    BankService* bankService = new BankService();
    int savingsAccountNumber = bankService->createAccount(AccountType.SAVINGS, 1000);
    int currentAccountNumber = bankService->createAccount(AccountType.CURRENT, 1000);
    bankService->transfer(savingsAccountNumber, currentAccountNumber, 500);
    return 0;
}