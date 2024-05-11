#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

class BankAccount {
protected:
    std::string accountNumber;
    double balance;
    std::string openDate;
    std::vector<std::string> transactionHistory;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {
        srand(time(NULL));
        accountNumber = std::to_string(rand() % 1000000000 + 100000000);
        
        time_t now = time(0);
        openDate = ctime(&now);
    }

    virtual void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposit: " + std::to_string(amount));
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactionHistory.push_back("Withdrawal: " + std::to_string(amount));
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }

    virtual void displayStatement() {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
        std::cout << "Transaction History:" << std::endl;
        for (const auto& transaction : transactionHistory) {
            std::cout << transaction << std::endl;
        }
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    const std::vector<std::string>& getTransactionHistory() const {
        return transactionHistory;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(double initialBalance, double rate) : BankAccount(initialBalance), interestRate(rate) {
        if (rate > 0.06) {
            interestRate = 0.06; // Cap interest rate at 6%
        }
    }

    double getInterestRate() const {
        return interestRate;
    }

    void depositInterest() {
        double interest = balance * interestRate;
        deposit(interest);
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(double initialBalance) : BankAccount(initialBalance) {}

    double getInterestRate() const {
        throw std::invalid_argument("Checking accounts do not have an interest rate.");
    }
};

class BankAccountHolder {
private:
    std::string name;
    std::string username;
    std::string netBankingPassword;
    std::vector<BankAccount*> accounts;

public:
    BankAccountHolder(std::string n, std::string u, std::string p) : name(n), username(u), netBankingPassword(p) {}

    void createAccount(double initialBalance, bool isSavings) {
        if (isSavings) {
            accounts.push_back(new SavingsAccount(initialBalance, 0.04)); // taking example interest rate of 4%
        } else {
            accounts.push_back(new CheckingAccount(initialBalance));
        }
    }

    void deposit(int accountIndex, double amount) {
        accounts[accountIndex]->deposit(amount);
    }

    void withdraw(int accountIndex, double amount) {
        accounts[accountIndex]->withdraw(amount);
    }

    void displayStatement(int accountIndex) {
        accounts[accountIndex]->displayStatement();
    }

    int getNumAccounts() const {
        return accounts.size();
    }

    ~BankAccountHolder() {
        for (auto& account : accounts) {
            delete account;
        }
    }

    std::string getUsername() const {
        return username;
    }

    std::string getPassword() const {
        return netBankingPassword;
    }

    const std::vector<BankAccount*>& getAccounts() const {
        return accounts;
    }
};

class BranchManager {
private:
    std::string username;
    std::string password;
    std::vector<BankAccountHolder>* users;

    BranchManager() : username("admin"), password("admin123"), users(nullptr) {}

public:
    static BranchManager& getInstance() {
        static BranchManager instance;
        return instance;
    }

    void setUsers(std::vector<BankAccountHolder>* userList) {
        users = userList;
    }

    std::vector<std::string> getAccountHolders() {
        std::vector<std::string> accountHolders;
        if (users) {
            for (const auto& user : *users) {
                accountHolders.push_back(user.getUsername());
            }
        }
        return accountHolders;
    }

    std::vector<std::string> getStatementOfAccount(const std::string& accountNumber) {
        std::vector<std::string> statement;
        if (users) {
            for (const auto& user : *users) {
                for (const auto& account : user.getAccounts()) {
                    if (account->getAccountNumber() == accountNumber) {
                        statement.push_back("Account Holder: " + user.getUsername());
                        statement.push_back("Account Number: " + accountNumber);
                        statement.push_back("Balance: $" + std::to_string(account->getBalance()));
                        statement.push_back("Transaction History:");
                        for (const auto& transaction : account->getTransactionHistory()) {
                            statement.push_back(transaction);
                        }
                        return statement;
                    }
                }
            }
        }
        throw std::invalid_argument("Account not found.");
    }

    void fastForward(int days) {
        if (users) {
            for (auto& user : *users) {
                for (auto& account : user.getAccounts()) {
                    SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(account);
                    if (savingsAccount) {
                        savingsAccount->depositInterest();
                    }
                }
            }
        }
    }

    bool authenticate(const std::string& user, const std::string& pass) const {
        return (user == username && pass == password);
    }
};

void signUp(std::vector<BankAccountHolder>& users) {
    std::string username, password, name;
    std::cout << "Sign Up" << std::endl;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    users.push_back(BankAccountHolder(name, username, password));
    std::cout << "Sign Up Successful!" << std::endl;
}

void branchManagerMenu() {
    BranchManager& manager = BranchManager::getInstance();
    bool authenticated = false;
    std::string user, pass;

    std::cout << "Branch Manager Login" << std::endl;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;

    authenticated = manager.authenticate(user, pass);
    if (!authenticated) {
        std::cout << "Authentication failed!" << std::endl;
        return;
    }

    bool done = false;
    while (!done) {
        int choice;
        std::cout << "\nBranch Manager Operations:" << std::endl;
        std::cout << "1. List All Account Holders" << std::endl;
        std::cout << "2. Get Statement of Specific Account" << std::endl;
        std::cout << "3. Fast-Forward Time (Interest Calculation)" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::vector<std::string> holders = manager.getAccountHolders();
                std::cout << "\nAccount Holders:" << std::endl;
                for (const auto& holder : holders) {
                    std::cout << holder << std::endl;
                }
                break;
            }
            case 2: {
                std::string accountNumber;
                std::cout << "Enter the account number: ";
                std::cin >> accountNumber;
                try {
                    std::vector<std::string> statement = manager.getStatementOfAccount(accountNumber);
                    for (const auto& line : statement) {
                        std::cout << line << std::endl;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 3: {
                int days;
                std::cout << "Enter number of days to fast forward: ";
                std::cin >> days;
                manager.fastForward(days);
                std::cout << "Interest calculation completed!" << std::endl;
                break;
            }
            case 4:
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void mainMenu(std::vector<BankAccountHolder>& users) {
    std::string username, password;
    bool loggedIn = false;
    BankAccountHolder* currentUser = nullptr;

    while (!loggedIn) {
        int choice;
        std::cout << "\nWelcome to the Bank!" << std::endl;
        std::cout << "1. Sign Up" << std::endl;
        std::cout << "2. Login as User" << std::endl;
        std::cout << "3. Branch Manager Login" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                signUp(users);
                break;
            case 2: {
                std::cout << "Login" << std::endl;
                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cout << "Enter your password: ";
                std::cin >> password;

                for (auto& user : users) {
                    if (user.getUsername() == username && user.getPassword() == password) {
                        loggedIn = true;
                        currentUser = &user;
                        std::cout << "Login Successful!" << std::endl;
                        break;
                    }
                }
                if (!loggedIn) {
                    std::cout << "Incorrect username or password. Please try again." << std::endl;
                }
                break;
            }
            case 3:
                branchManagerMenu();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    bool done = false;
    while (!done) {
        int choice;
        std::cout << "\nWhat would you like to do?" << std::endl;
        std::cout << "1. Create Bank Account" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. View Statement" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char accountType;
                std::cout << "Create Bank Account" << std::endl;
                std::cout << "Enter 'S' for Savings or 'C' for Checking: ";
                std::cin >> accountType;
                double initialBalance;
                std::cout << "Enter initial balance: ";
                std::cin >> initialBalance;

                currentUser->createAccount(initialBalance, accountType == 'S' || accountType == 's');
                std::cout << "Account created successfully!" << std::endl;
                break;
            }
            case 2: {
                int index;
                double amount;
                std::cout << "Enter account index (0-based): ";
                std::cin >> index;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                currentUser->deposit(index, amount);
                std::cout << "Deposit successful!" << std::endl;
                break;
            }
            case 3: {
                int index;
                double amount;
                std::cout << "Enter account index (0-based): ";
                std::cin >> index;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                currentUser->withdraw(index, amount);
                std::cout << "Withdrawal successful!" << std::endl;
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter account index (0-based): ";
                std::cin >> index;
                currentUser->displayStatement(index);
                break;
            }
            case 5:
                currentUser = nullptr;
                done = true;
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

int main() {
    std::vector<BankAccountHolder> users;
    BranchManager& manager = BranchManager::getInstance();
    manager.setUsers(&users);

    while (true) {
        mainMenu(users);
    }

    return 0;
}
