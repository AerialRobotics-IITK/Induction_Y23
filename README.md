// Induction_Y23
#include <iostream>
#include <string>
using namespace std;

class BankAccountHolder {
private:
    string name;
    string username;
    string netbankingpassword;
    long accno;

public:
    void setAccNo(long acc) {
        accno = acc;
    }

    void getStatementOfAccount(string name, double balance) {
        cout << "Enter the account name whose statements are required: " << name << endl;
        cout << "Current Balance: " << balance << endl;
        cout << "Transaction history" << endl;
    }

    void getAccountHolders(int listofaccounts) {
        cout << "NAME\nACCOUNT NUMBER" << endl;
        cout << name << "\n" << accno << endl;
    }

    void fastforward() {}

    void changepassword(string password) {
        netbankingpassword = password;
        cout << "Password Changed" << endl;
    }

    void createAccount(string name, string username) {
        cout << "Enter the name of Bank Account Holder: " << name << endl;
        cout << "Enter the bank account username: " << username << endl;
        cout << "Account is created." << endl;
    }
};

class BankAccount {
private:
    long accno;
    double balance;
    string opendate;
    string transactiontype;
    double depositAmount, withdrawAmount, transferAmount;

public:
    void deposit(double deposit) {
        cout << "Enter the amount you want to deposit: " << deposit << endl;
        balance = balance + deposit;
        cout << "Amount deposited." << endl;
    }

    void withdraw(double withdraw) {
        cout << "Enter the amount you want to withdraw: " << withdraw << endl;
        balance = balance - withdraw;
        cout << "Amount withdrawn." << endl;
    }

    void transfer(double transfer) {
        cout << "Enter the amount you want to transfer: " << transfer << endl;
        balance = balance - transfer;
        cout << "Amount transferred." << endl;
    }

    double getBalance() {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestrate;

public:
    void getInterestRate(double interest) {
        cout << "Enter the non-zero interest rate of bank: " << interest << "%" << endl;
        interestrate = interest;
    }

    void setInterestRate() {
        if (interestrate > 6.0)
            interestrate = 6.0;
    }
};

class CheckingAccount : public BankAccount {
private:
    double interestrate;

public:
    void getInterestRate() {}
};

int main() {
    string name, username, password;
    double amt; 
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter username: ";
    cin >> username;

    BankAccountHolder holder;
    holder.createAccount(name, username);

    cout << "Enter the new password: ";
    cin >> password;
    holder.changepassword(password);

    int listofaccounts;
    cout << "Enter list of accounts: ";
    cin >> listofaccounts;
    holder.getAccountHolders(listofaccounts);

    double balance = 0.0; // Initialize balance

    // Call getStatementOfAccount with balance
    holder.getStatementOfAccount(name, balance);

    char C;
    do {
        cout << "Type W for withdrawal \n Type T for transferring to another bank\n Type D for depositing \n Type C for closing account\n Type S for displaying balance: ";
        cin >> C;
        switch (C) {
            case 'D':
                cout << "Enter the amount to be deposited: ";
                cin >> amt;
                balance += amt; // Update balance
                break;
                case 'S':
                 holder.getStatementOfAccount(name, balance);
                 break;
            case 'T':
                cout << "Enter the amount to be transferred to: ";
                cin >> amt;
                balance -= amt; // Update balance
                break;
            case 'W':
                cout << "Enter the amount to be withdrawn: ";
                cin >> amt;
                balance -= amt; // Update balance
                break;
            case 'C':
                return 0;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (C != 'C');

    return 0;
}


