//incomplete but whatever i was able to do
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_set>

using namespace std;
// transaction storing date amount and type
class Transaction {
public:
    string type;
    double amount;
    time_t date;

    Transaction(string t, double a, time_t d) : type(t), amount(a), date(d) {}
};

class BankAccount {
protected:
    int accountNumber;
    double balance;
    vector<Transaction> transactions; //vector storing all the transactions

public:
    BankAccount(int accNum, double openingBalance) : accountNumber(accNum), balance(openingBalance) {}

  

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, time(nullptr));
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Funds" << endl;
            return;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount, time(nullptr));
    }

    void transfer(BankAccount& toAccount, double amount) {
        if (amount > balance) {
            cout << "Insufficient Funds" << endl;
            return;
        }
        withdraw(amount);
        toAccount.deposit(amount);
        transactions.emplace_back("Transfer", amount, time(nullptr));
    }
    //gives statement by iterating in transactions vector
    void getStatement() const { 
        cout << "Statement:" << endl;
        for (const auto& transaction : transactions) {
            cout << transaction.type << ": $" << transaction.amount << " - " << ctime(&transaction.date);
        }
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int accNum, double openingBalance) : BankAccount(accNum, openingBalance) {}
};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(int accNum, double openingBalance) : BankAccount(accNum, openingBalance) {}
};

class BankAccountHolder {
private:
    string username;
    string password;
    vector<BankAccount> accounts;
    static unordered_set<string> allUsernames;

public:
//allUsernames holds all username entries making sure they are unique
    BankAccountHolder(string u, string p) : username(u), password(p) {
        if (allUsernames.find(u) != allUsernames.end()) {
            throw invalid_argument("Username already exists");
        }
        allUsernames.insert(u);
    }

    vector<BankAccount>& getAccounts() { 
        return accounts;
    }

    void changePassword(string newPassword) {
        password = newPassword;
    }

    void createAccount(string accountType, double openingBalance) {
        static int accountNumber = 100000000; // First account Number that will increment on adding accounts in system
        if (accountType == "savings") {
            accounts.emplace_back(accountNumber++, openingBalance);
        } else if (accountType == "checking") {
            accounts.emplace_back(accountNumber++, openingBalance);
        } else {
            cout << "Invalid Account Type" << endl;
            return;
        }
        cout << "Account created successfully. Account Number: " << accountNumber - 1 << endl;
    }

    bool checkCredentials(string u, string p) const {
        return username == u && password == p;
    }

    string getUsername() const {
        return username;
    }
};

unordered_set<string> BankAccountHolder::allUsernames;

class BranchManager {
private:
    string username;
    string password;

public:
    BranchManager(string u, string p) : username(u), password(p) {}

    bool login(string u, string p) const {
        return username == u && password == p;
    }

    void getAccountStatement(int accountNumber, vector<BankAccountHolder>& holders) const { 
        for (auto& holder : holders) { 
            for (auto& account : holder.getAccounts()) { 
                if (account.getAccountNumber() == accountNumber) {
                    account.getStatement();
                    return;
                }
            }
        }
        cout << "Account Not Found" << endl;
    }
};
bool accountLogin(vector<BankAccountHolder>& holders, const string& username, const string& password) {
    for (auto& holder : holders) {
        if (holder.checkCredentials(username, password)) {
            int choice;
            do {
                cout << "\nAccount Menu:" << endl;
                cout << "1. View Statements" << endl;
                cout << "2. Create Account" << endl;
                cout << "3. Change Password" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    for (const auto& account : holder.getAccounts()) {
                        account.getStatement();
                        cout << endl;
                    }
                } else if (choice == 2) {
                    string type;
                    double amount;
                    cout << "Enter account type (savings/checking): ";
                    cin >> type;
                    cout << "Enter initial balance: ";
                    cin >> amount;
                    holder.createAccount(type, amount);
                } else if (choice == 3) {
                    string newPassword;
                    cout << "Enter new password: ";
                    cin >> newPassword;
                    holder.changePassword(newPassword);
                    cout << "Password changed successfully." << endl;
                } else if (choice == 4) {
                    cout << "Exiting account menu." << endl;
                } else {
                    cout << "Invalid choice." << endl;
                }
            } while (choice != 4);
            return true;
        }
    }
    cout << "Invalid username or password." << endl;
    return false;
}

int main() {
    vector<BankAccountHolder> holders;

    holders.emplace_back("John Doe", "johndoe", "password1");
    holders.emplace_back("Jane Smith", "janesmith", "password2");

    int choice;
    string username, password;

    do {
        cout << "\nWelcome to the Banking System!" << endl;
        cout << "1. Account Login" << endl;
        cout << "2. Branch Manager Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (accountLogin(holders, username, password)) {
                cout << "Login successful." << endl;
            }
        } else if (choice == 2) {
            BranchManager manager("manager", "branch_password");
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (manager.login(username, password)) {
                cout << "Branch Manager Login Successful." << endl;
                int choice;
                do {
                    cout << "\nBranch Manager Menu:" << endl;
                    cout << "1. Get Account Statement" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (choice == 1) {
                        int accountNum;
                        cout << "Enter account number: ";
                        cin >> accountNum;
                        manager.getAccountStatement(accountNum, holders);
                    } else if (choice == 2) {
                        cout << "Exiting Branch Manager menu." << endl;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                } while (choice != 2);
            } else {
                cout << "Invalid username or password for Branch Manager." << endl;
            }
        } else if (choice == 3) {
            cout << "Exiting Banking System." << endl;
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 3);

    return 0;
}