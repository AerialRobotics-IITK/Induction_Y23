#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// global date variable to store the current date and time
time_t currentTime = time(nullptr);

// Class representing a transaction
class Transaction {
private:
    // "Deposit" or "Withdrawal" input for type
    string type; 
    double amount;
    double previousBalance;
    double currentBalance;
    time_t timestamp;

public:
    // Constructor
    Transaction(string _type, double _amount, double _prevBalance, double _curBalance) : type(_type), amount(_amount), previousBalance(_prevBalance), currentBalance(_curBalance) {
        timestamp = currentTime;
    }

    // Transaction details as a string
    string getDetails() const {
        string result = "Type: " + type + ", Amount: Rs." + to_string(amount);
        result += ", Previous Balance: Rs." + to_string(previousBalance) + ", Current Balance: Rs." + to_string(currentBalance);
        result += ", Timestamp: " + string(ctime(&timestamp));
        return result;
    }
};

// Class representing a bank account
class Account {
private:
    string accountNumber;
    double balance;
    string openingDate;
    vector<Transaction> statement;

public:
    // Constructor
    Account(double initialBalance) : balance(initialBalance) {
        generateAccountNumber();
        openingDate = string(ctime(&currentTime));
    }

    // Getter for account number
    string getAccountNumber() const { return accountNumber; }

    // Getter for balance
    double getBalance() const { return balance; }

    // Deposit
    void deposit(double amount) {
        double prevBalance = balance;
        balance += amount;
        Transaction deposit("Deposit", amount, prevBalance, balance);
        statement.push_back(deposit);
        cout << "Deposit of Rs." << amount << " successful. New balance: Rs." << balance << endl;
    }

    // Withdrawal
    void withdraw(double amount) {
        if (balance >= amount) {
            double prevBalance = balance;
            balance -= amount;
            Transaction withdrawal("Withdrawal", amount, prevBalance, balance);
            statement.push_back(withdrawal);
            cout << "Withdrawal of Rs." << amount << " successful. New balance: Rs." << balance << endl;
        } else {
            cout << "Insufficient funds. Withdrawal failed." << endl;
        }
    }

    // Method to get account statement
    void printStatement() const {
        cout << "Account Statement for Account Number: " << accountNumber << endl;
        for (const auto& transaction : statement) {
            cout << transaction.getDetails() << endl;
        }
    }

private:
    // Method to generate a random account number
    void generateAccountNumber() {
        static unordered_set<string> accountNumbers;
        while (true) {
            string newAccountNumber;
            for (int i = 0; i < 9; ++i) {
                // Generate a random 9 dig no.
                newAccountNumber += to_string(rand() % 10); 
            }
            if (accountNumbers.find(newAccountNumber) == accountNumbers.end()) {
                accountNumbers.insert(newAccountNumber);
                accountNumber = newAccountNumber;
                break;
            }
        }
    }
};

// Class representing a bank account holder
class BankAccountHolder {
private:
    string name;
    string username;
    string netBankingPassword;
    vector<Account*> accounts;

public:
    // Constructor
    BankAccountHolder(string _name, string _username, string _password) : name(_name), username(_username), netBankingPassword(_password) {}

    // For list of accounts
    vector<Account*> getAccounts() const { return accounts; }

    // Method to change net banking password
    void changePassword(string oldPassword, string newPassword) {
        if (oldPassword == netBankingPassword) {
            netBankingPassword = newPassword;
            cout << "Password changed successfully." << endl;
        } else {
            cout << "Incorrect old password. Password change failed." << endl;
        }
    }

    // Method to create a new account
    Account* createAccount(double initialBalance, string accountType) {
        Account* newAccount = new Account(initialBalance);
        cout << "New account created successfully. Account Number: " << newAccount->getAccountNumber() << endl;
        cout << "Account Type: " << accountType << endl;
        accounts.push_back(newAccount);
        return newAccount;
    }

   
    // Getter for name
    string getName() const { return name; }

    // Getter for username
    string getUsername() const { return username; }

    // Getter for net banking password
    string getNetBankingPassword() const { return netBankingPassword; }

    // Authentication using username and password
    bool authenticate(string _username, string _password) const {
        return (username == _username && netBankingPassword == _password);
    }
};

// Class representing a branch manager
class BranchManager {
private:
    static BranchManager* instance;
    string username;
    string password;

    // Private constructor to prevent instantiation
    BranchManager() : username("ARIITK"), password("ARIITK") {}

public:
    
    static BranchManager* getInstance() {
        if (!instance) {
            instance = new BranchManager();
        }
        return instance;
    }

    
    
};

// Initialize static member variable for BranchManager
BranchManager* BranchManager::instance = nullptr;

// Main function
int main() {
    
    srand(time(nullptr));

    bool running = true; // Variable to control the loop
    vector<BankAccountHolder> holders; // Collection of bank account holders
    
    // Loop for interactive menu
    while (running ) {
        cout << "Welcome to the Banking Management System!" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Change Password" << endl;
        cout << "4. Branch Manager Login" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(); 
        
        switch (choice) {
            case 1: {
                // Sign Up
                cout << "Sign Up option selected." << endl;
                string name, username, password;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your username: ";
                getline(cin, username);
                cout << "Set your net banking password: ";
                getline(cin, password);
                //bank account holder object
                BankAccountHolder newHolder(name, username, password);
                // add new holder to the collection
                holders.push_back(newHolder); 
                cout << "Account created successfully!" << endl;
                break;
            }
            case 2: {
                // Login
                cout << "Login option selected." << endl;
                string username, password;
                cout << "Enter your username: ";
                getline(cin, username);
                cout << "Enter your password: ";
                getline(cin, password);
                bool found = false;
                BankAccountHolder* loggedInHolder = nullptr;
                for (auto& holder : holders) {
                    if (holder.authenticate(username, password)) {
                    cout << "Login successful!" << endl;
                    loggedInHolder = &holder;
                    found = true;
                    break;
                    }
                }
                if (!found) {
                    cout << "Invalid username or password. Login failed." << endl;
                    break;
                }

                // Check if the user already has accounts
                vector<Account*> accounts = loggedInHolder->getAccounts();
                if (!accounts.empty()) {
                    cout << "You already have accounts. Skipping account creation..." << endl;
                     // displays options for account operations
                    cout << "Account creation successful!" << endl;
                    while (true) {
                        cout << "Options:" << endl;
                        cout << "1. Deposit" << endl;
                        cout << "2. Withdraw" << endl;
                        cout << "3. Check Balance" << endl;
                        cout << "4. View Statement" << endl;
                        
                        cout << "5. Exit" << endl;
                        cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore(); 

            switch (choice) {
                case 1: {
                    // Deposit
                    double depositAmount;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    cin.ignore(); 
                    accounts[0]->deposit(depositAmount);
                    break;
                }
                case 2: {
                    // Withdraw
                    double withdrawalAmount;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawalAmount;
                    cin.ignore(); 
                    accounts[0]->withdraw(withdrawalAmount);
                    break;
                }
                case 3: {
                    // Check Balance
                    cout << "Current Balance: Rs." << accounts[0]->getBalance() << endl;
                    break;
                }
                case 4: {
                    // View Statement
                    accounts[0]->printStatement();
                    break;
                }
                
                case 5: {
                    // Exit
                    cout << "Exiting account operations." << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
                }
            }
            if (choice == 5) {
                break;
            }
        }
        break;
    }
    
    // now if initially account was not created then the above whole if part will not be executed first 
    // Prompt the user to provide initial balance for the new account
    double initialBalance;
    cout << "Enter initial balance for the new account: ";
    cin >> initialBalance;
    cin.ignore();

    // Choose account type
    string accountType;
    cout << "Choose account type (1 for Savings, 2 for Current): ";
    int typeChoice;
    cin >> typeChoice;
    cin.ignore();
    if (typeChoice == 1) {
        accountType = "Savings";
    } else if (typeChoice == 2) {
        accountType = "Current";
    } else {
        cout << "Invalid choice. Defaulting to Savings account." << endl;
        accountType = "Savings";
    }

    // Create a new account for the logged-in user and adding to the holder
    Account* newAccount = loggedInHolder->createAccount(initialBalance, accountType);

    // Display options for account operations
    cout << "Account creation successful!" << endl;
    while (true) {
        cout << "Options:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. View Statement" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1: {
                // Deposit
                double depositAmount;
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                cin.ignore();
                newAccount->deposit(depositAmount);
                break;
            }
            case 2: {
                // Withdraw
                double withdrawalAmount;
                cout << "Enter amount to withdraw: ";
                cin >> withdrawalAmount;
                cin.ignore();
                newAccount->withdraw(withdrawalAmount);
                break;
            }
            case 3: {
                // Check Balance
                cout << "Current Balance: Rs." << newAccount->getBalance() << endl;
                break;
            }
            case 4: {
                // View Statement
                newAccount->printStatement();
                break;
            }
            
            case 5: {
                // Exit
                cout << "Exiting account operations." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
        if (choice == 5) {
            break;
        }
    }
    break;
}
        case 3: {
                // Change Password
                string username, oldPassword, newPassword;
                cout << "Enter your username: ";
                getline(cin, username);
                cout << "Enter your old password: ";
                getline(cin, oldPassword);
                cout << "Enter your new password: ";
                getline(cin, newPassword);
                // Find the user and change password
                bool found = false;
                for (auto& holder : holders) {
                    if (holder.getUsername() == username) {
                        holder.changePassword(oldPassword, newPassword);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "User not found. Password change failed." << endl;
                }

                break;
            }
        


            case 4: {
            // Branch Manager Login
            cout << "Branch Manager Login option selected." << endl;
            string username, password;
            cout << "Enter branch manager username: ";
            getline(cin, username);
            cout << "Enter branch manager password: ";
            getline(cin, password);
            // Check if branch manager login is successful
            if (username == "ARIITK" && password == "ARIITK>>>ERAIITK") {
                cout << "Branch Manager login successful!" << endl;

                // Get all accounts from the holders
                vector<Account*> accounts;
                for (const auto& holder : holders) {
                    for (const auto& acc : holder.getAccounts()) {
                        accounts.push_back(acc);
                    }
                }

                cout << "Select an option:" << endl;
                cout << "1. Get Statement of Account" << endl;
                cout << "2. Get Account Holders" << endl;
               
                cout << "Enter your choice: ";
                int branchManagerChoice;
                cin >> branchManagerChoice;
                cin.ignore(); 
        switch (branchManagerChoice) {
            case 1: {
                // Get Statement of Account
                string accountNumber;
                cout << "Enter account number: ";
                getline(cin, accountNumber);
                // Find the account using the printstatement method in account class to print statemnet here also for a particular account
                bool accountFound = false;
                for (const auto& holder : holders) {
                    for (const auto& acc : holder.getAccounts()) {
                        if (acc->getAccountNumber() == accountNumber) {
                            acc->printStatement();
                            accountFound = true;
                            break;
                        }
                    }
                    if (accountFound) {
                        break;
                    }
                }
                if (!accountFound) {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 2: {
                // Get Account Holders
                cout << "Account holders:" << endl;
                for (const auto& holder : holders) {
                    cout << "Name: " << holder.getName() << ", Username: " << holder.getUsername() << endl;
                    
                }
                break;
            }
            
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
    } else {
        cout << "Invalid username or password. Branch Manager login failed." << endl;
    }
    break;
}
            case 5: {
                // Exit
                cout << "Exiting the program........." << endl;
                running = false;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
    }

    // cleaning the dynamically allocated memory
    for (auto& holder : holders) {
        for (auto& acc : holder.getAccounts()) {
            delete acc;
        }
    }

    return 0;
}
