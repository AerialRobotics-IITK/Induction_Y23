#include<iostream>
#include<string.h>
#include <string>
#include <cstdlib> // For rand() function
using namespace std;

class Statement {
private:
    double amount;
    string transfer_type;
    double Amount_flow;

public:
    Statement(string desc, double amt) {
        transfer_type = desc;
        amount = amt;
    }
    void getDetails() {
        cout << "Description: " << transfer_type << endl;
        cout << "Amount: $" << amount << endl;
    }
};

class Bank_Account {
protected:
    string Account_type;
    double Balance;
    Statement** statements;
    int numStatements;

public:
    long Account_No;

    Bank_Account(int id, string type, double openingBalance) {
        Account_No = id; // Account number is provided during account creation
        Account_type = type;
        Balance = openingBalance;
        numStatements = 0;
        statements = new Statement*[100];
    }

    virtual ~Bank_Account() {
        for (int i = 0; i < numStatements; ++i) {
            delete statements[i];
        }
        delete[] statements;
    }

    string getAccountType() const {
        return Account_type;
    }

    void addStatement(const Statement& statement) {
        statements[numStatements++] = new Statement(statement);
    }

    void viewStatements() const {
        cout << "----- Statements for Account ID: " << Account_No << " -----" << endl;
        for (int i = 0; i < numStatements; ++i) {
            statements[i]->getDetails();
            cout << endl;
        }
    }

    void deposit(double amount);
    bool withdraw(double amount);
};

bool Bank_Account::withdraw(double amount) {
    if (Account_type == "Savings" && amount > 200000) {
        cout << "Savings account cannot withdraw more than 200000 at a time." << endl;
        return false;
    }

    if (Balance >= amount) {
        Balance -= amount;
        addStatement(Statement("Withdrawal", -amount));
        cout << "Withdrawal of " << amount << " successful. New balance: " << Balance << endl;
        return true;
    } else {
        cout << "Insufficient funds." << endl;
        return false;
    }
}

class Savings_Account : public Bank_Account {
private:
    float Interest_Rate;
    const int Upper_Transcation_Limit = 2000000;

public:
    Savings_Account(long accountNo) : Bank_Account(accountNo, "Savings", 0) {}

    float getInterestRate() {
        return Interest_Rate;
    }

    float setInterestRate(float interestrate) {
        if (interestrate > 6) {
            cout << "Max interest rate is 6";
        } else {
            Interest_Rate = interestrate;
        }
        return Interest_Rate;
    }

    ~Savings_Account() {}
};

class Current_Account : public Bank_Account {
private:
    const float Interest_Rate = 0;

public:
    Current_Account(long accountNo) : Bank_Account(accountNo, "Current", 0) {}

    float getInterestRate() {
        throw ("Interest Rate is 0");
    }

    ~Current_Account() {}
};

class Bank_Account_Holder {
private:
    string username;
    string password;
    Bank_Account** list;
    int capacity;
    int numofAccounts;

public:
    Bank_Account_Holder(string name, string passwd) {
        username = name;
        password = passwd;
        capacity = 100;
        numofAccounts = 0;
        list = new Bank_Account*[capacity];
    };

    void changepasswd(string passwd);
    void createAccount(string accounttype);

    Savings_Account* get_savingsAccount(long accountId);
    Current_Account* get_currentAccount(long accountId);
};

void Bank_Account_Holder::changepasswd(string passwd) {
    password = passwd;
}

void Bank_Account_Holder::createAccount(string accounttype) {
    if (numofAccounts < capacity) {
        long accountNo = rand() % 900000000 + 100000000; // Generate a random account number
        if (accounttype == "Savings") {
            list[numofAccounts++] = new Savings_Account(accountNo);
            cout << "Savings account created with account number: " << accountNo << endl;
        } else if (accounttype == "Current") {
            list[numofAccounts++] = new Current_Account(accountNo);
            cout << "Current account created with account number: " << accountNo << endl;
        }
    } else {
        cout << "Maximum account limit reached." << endl;
    }
}

Savings_Account* Bank_Account_Holder::get_savingsAccount(long accountId) {
    for (int i = 0; i < numofAccounts; ++i) {
        if (list[i]->Account_No == accountId && list[i]->getAccountType() == "Savings") {
            return dynamic_cast<Savings_Account*>(list[i]);
        }
    }
    return nullptr;
}

Current_Account* Bank_Account_Holder::get_currentAccount(long accountId) {
    for (int i = 0; i < numofAccounts; ++i) {
        if (list[i]->Account_No == accountId && list[i]->getAccountType() == "Current") {
            return dynamic_cast<Current_Account*>(list[i]);
        }
    }
    return nullptr;
}

void Bank_Account::deposit(double money) {
    Balance += money;
    addStatement(Statement("Deposit", money));
}

int main() {
    Bank_Account_Holder accountHolder("Ayush", "password123");

    // Main menu
    int choice;
    do {
        cout << "\nBanking System Menu\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. View Statements\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            accountHolder.createAccount("Savings");
        } else if (choice == 2) {
            accountHolder.createAccount("Current");
        } else if (choice == 3) {
            long accountNumber;
            double amount;
            string Accounttype;
            cout << "Enter account type Saving/Current: ";
            cin >> Accounttype;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (Accounttype == "Savings") {
                Savings_Account* account = accountHolder.get_savingsAccount(accountNumber);
                if (account != nullptr) {
                    account->deposit(amount);
                } else {
                    cout << "Savings account with given account number not found." << endl;
                }
            } else if (Accounttype == "Current") {
                Current_Account* account = accountHolder.get_currentAccount(accountNumber);
                if (account != nullptr) {
                    account->deposit(amount);
                } else {
                    cout << "Current account with given account number not found." << endl;
                }
            }
        } else if (choice == 4) {
            long accountNumber;
            double amount;
            string Accounttype;
            cout << "Enter account type Saving/Current: ";
            cin >> Accounttype;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (Accounttype == "Savings") {
                Savings_Account* account = accountHolder.get_savingsAccount(accountNumber);
                if (account != nullptr) {
                    account->withdraw(amount);
                } else {
                    cout << "Savings account with given account number not found." << endl;
                }
            } else if (Accounttype == "Current") {
                Current_Account* account = accountHolder.get_currentAccount(accountNumber);
                if (account != nullptr) {
                    account->withdraw(amount);
                } else {
                    cout << "Current account with given account number not found." << endl;
                }
            }
        } else if (choice == 5) {
            long accountNumber;
            string Accounttype;
            cout << "Enter account type Saving/Current: ";
            cin >> Accounttype;
            cout << "Enter account number: ";
            cin >> accountNumber;
            if (Accounttype == "Savings") {
                Savings_Account* account = accountHolder.get_savingsAccount(accountNumber);
                if (account != nullptr) {
                    account->viewStatements();
                } else {
                    cout << "Savings account with given account number not found." << endl;
                }
            } else if (Accounttype == "Current") {
                Current_Account* account = accountHolder.get_currentAccount(accountNumber);
                if (account != nullptr) {
                    account->viewStatements();
                } else {
                    cout << "Current account with given account number not found." << endl;
                }
            }
        } else if (choice == 6) {
            cout << "Have a good Day" << endl << "Exiting...";
        } else {
            cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
        }
    } while (choice != 6);

    return 0;
}
