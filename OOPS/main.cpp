#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

struct transaction {
    string type;
    double amount;
    string date;

    transaction(string type, double amount, string date) {
        this->type = type;
        this->amount = amount;
        this->date = date;
    }
};

class bankAccount {
private:
    string accountType;
    string accountNumber;
    double balance;
    string openDate;
    string type;
    vector<transaction> transactions;
    int interestRate;
public:
    bankAccount(string accountNumber, double balance, string openDate, string type, int interestRate, string accountType) {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->openDate = openDate;
        this->type = type;
        this->interestRate = interestRate;
        this->accountType = accountType;
    }
	
    string getAccountNumber() {
        return accountNumber;
    }
    string getAccountType() {
        return accountType;
    }
    double getBalance() {
        return balance;
    }
    string getOpenDate() {
        return openDate;
    }
    string getType() {
        return type;
    }
    int getInterestRate() {
        return interestRate;
    }
    vector<transaction> getTransactions() {
        return transactions;
    }
    void changeInterestRate(int rate) {
        if (accountType == "Current") {
            cout << "Interest rate cannot be changed for current account" << endl;
            return;
        }
        interestRate = rate;
    }
    void deposit(double amount) {
        balance += amount;
        transactions.push_back(transaction("Deposit", amount, date()));
    }
    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(transaction("Withdraw", amount, date()));
        }
        else {
            cout << "Insufficient balance" << endl;
        }
    }

    void viewTransactions() {
        cout << left << setw(20) << "Transaction Type" << setw(20) << "Amount" << setw(20) << "Date" << endl;
        for (int i = 0; i < transactions.size(); i++) {
            cout << left << setw(20) << transactions[i].type << setw(20) << transactions[i].amount << setw(20) << transactions[i].date << endl;
        }
    }
    string date() {
        auto t = time(nullptr);
        auto tmPtr = localtime(&t);
        ostringstream oss;
        oss << std::put_time(tmPtr, "%d-%m-%Y");
        return oss.str();
    }
};

class bankAccountHolder {
private:
    string name;
    string username;
    string password;
    vector<bankAccount> accounts;
public:
    bankAccountHolder(string name, string username, string password)
    {
        this->name = name;
        this->username = username;
        this->password = password;
    }
    string getName()
    {
        return name;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    vector<bankAccount> getAccounts() {
        return accounts;
    }
    void addAccount(bankAccount account)
    {
        accounts.push_back(account);
    }
    void viewAccounts()
    {
        cout << left << setw(20) << "Account Number" << left << setw(20) << "Balance" << left << setw(20) << "Open Date" << left << setw(20) << "Type" << endl;
        for (auto a : accounts)
        {
            cout << left << setw(20) << a.getAccountNumber() << left << setw(20) << a.getBalance() << left << setw(20) << a.getOpenDate() << left << setw(20) << a.getType() << endl;
        }
    }
};

class branchManager {
private:
    string username;
    string password;
public:
    branchManager(string username, string password) {
        this->username = username;
        this->password = password;
    }
    string getUsername() {
        return username;
    }
    string getPassword() {
        return password;
    }
    void changeInterestRate(bankAccount &account, int rate) {
        account.changeInterestRate(rate);
    }
};

void managerMenu(vector<bankAccountHolder> &bank, branchManager manager) {
    string choice;
    while (1) {
        cout << "1. Change interest rate" << endl;
        cout << "2. Get Statement" << endl;
        cout << "e. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == "1") {
            string accountNumber;
            int changeSuccess = 0;
            int rate;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter new interest rate: ";
            cin >> rate;
            for (int i = 0; i < bank.size(); i++) {
                for (int j = 0; j < bank[i].getAccounts().size(); j++) {
                    if (bank[i].getAccounts()[j].getAccountNumber() == accountNumber) {
                        manager.changeInterestRate(bank[i].getAccounts()[j], rate);
                        cout << "Interest rate changed successfully" << endl;
                        changeSuccess = 1;
                        break;
                    }
                }
            }
            if (changeSuccess == 0) {
                cout << "Account not found" << endl;
            }
        }
        else if (choice == "2") {
            string accountNumber;
            int accountFound = 0;
            cout << "Enter account number: ";
            cin >> accountNumber;
            for (int i = 0; i < bank.size(); i++) {
                for (int j = 0; j < bank[i].getAccounts().size(); j++) {
                    if (bank[i].getAccounts()[j].getAccountNumber() == accountNumber) {
                        bank[i].getAccounts()[j].viewTransactions();
                        accountFound = 1;
                        break;
                    }
                }
            }
            if (accountFound == 0) {
                cout << "Account not found" << endl;
            }
        }
        else if (choice == "e") {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
}

void accountHolderMenu(bankAccountHolder &holder) {
    string choice;
    while (1) {
        cout << "1. View accounts" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View transactions" << endl;
        cout << "5. Add Account" << endl;
        cout << "e. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == "1") {
            holder.viewAccounts();
        }
        else if (choice == "2") {
            string accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            for (auto &acc : holder.getAccounts()) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.deposit(amount);
                    cout << "Deposit successful" << endl;
                    break;
                }
            }
        }
        else if (choice == "3") {
            string accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            for (auto &acc : holder.getAccounts()) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.withdraw(amount);
                    break;
                }
            }
        }
        else if (choice == "4") {
            string accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;
            for (auto &acc : holder.getAccounts()) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.viewTransactions();
                    break;
                }
            }
        }
        else if (choice == "5") {
            string accountNumber;
            double balance;
            string openDate;
            string type;
            int interestRate;
            string accountType;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter balance: ";
            cin >> balance;
            cout << "Enter open date: ";
            cin >> openDate;
            cout << "Enter type: ";
            cin >> type;
            cout << "Enter interest rate: ";
            cin >> interestRate;
            cout << "Enter account type: ";
            cin >> accountType;
            for (auto &acc : holder.getAccounts()) {
                if (acc.getAccountNumber() == accountNumber) {
                    cout << "Account number already exists" << endl;
                    break;
                }
            }
            bankAccount account(accountNumber, balance, openDate, type, interestRate, accountType);
            holder.addAccount(account);
            cout << "Account added successfully" << endl;
        }
        else if (choice == "e") {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
}

void login(vector<bankAccountHolder> &bank, branchManager manager) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (username == manager.getUsername() && password == manager.getPassword()) {
        managerMenu(bank, manager);
    }
    else {
        for (auto &holder : bank) {
            if (holder.getUsername() == username && holder.getPassword() == password) {
                accountHolderMenu(holder);
                return;
            }
        }
        cout << "Invalid username or password" << endl;
    }
}

void signup(vector<bankAccountHolder> &bank, branchManager manager) {
    //implement signup
    string name, username, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    bankAccountHolder holder(name, username, password);
    bank.push_back(holder);
    cout << "Account created successfully" << endl;
}

int main() {
    vector<bankAccountHolder> bank;
    branchManager manager("manager", "manager");

    string choice;
    while (1) {
        cout << "Do you want to login or signup? (login/signup): ";
        cin >> choice;
        if (choice == "login") {
            login(bank, manager);
        }
        else if (choice == "signup") {
            signup(bank, manager);
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
