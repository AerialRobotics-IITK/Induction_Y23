#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <stdio.h>
using namespace std;


static int ANum = 100000000;
vector<string> UsernamesInUses;
vector<string> Passwords;
vector<string> Names;
vector<Account> allAccounts;

class User {
public:
    string username;
    string password;
    vector<Account> accounts;

};

void getStatement(int accNumber){
    int arraynum = accNumber - 1000000000;
    int n = allAccounts[arraynum].transactions.size();
    for(int i =0; i<n;i++){
        cout << allAccounts[arraynum].transactions[i] << endl;
    }
    return;
};

class Account : public User {
public:
    string accountType;
    int accnum;
    double amount;
    vector<Transaction> transactions;

    Account(int accountnum, const string& type) : accnum(accountnum), accountType(type), amount(0) {}

    void addToList(){
        accounts.push_back(Account(accnum, accountType));
        allAccounts.push_back(Account(accnum, accountType));
    }

    void deposit(double deposit){
        amount += deposit;
        transactions.push_back(Transaction("Deposit", deposit));
    }

    void withdraw(double withdraw){
        if(withdraw > amount){
            cout << "Invalid withdraw" << endl;
        }
        else{
            amount -= withdraw;
            transactions.push_back(Transaction("Withdrawal", withdraw));
        }
    }
};


class Transaction {
private:
    string description;
    double amount;

public:
    Transaction(const string& desc, double amt) : description(desc), amount(amt) {}
};


int main(){
    int c;
    string NAME;
    string USERNAME;
    string PASS;


    cout << "\t\t\t=================================================\t\t\t" << endl;
    cout << "\t\t\t             WELCOME TO THE IITK BANK            \t\t\t" << endl;
    cout << "\t\t\t            --------------------------           \t\t\t" << endl;
    cout << "\t\t\t                       HOME                      \t\t\t" << endl;
    cout << "\t\t\t=================================================\t\t\t" << endl;
    cout << "For Registering yourself, press 1" << endl;
    cout << "For Account Holder Login, press 2" << endl;
    cout << "For Branch Manager Login, press 3" << endl;
    cout << "Press your choice: "; cin >> c;
    
    switch (c)
    {
    case 1:
        cout << "Enter your Username:" ; cin >> USERNAME;
        for (auto UsernamesInUse : UsernamesInUses){
            if (UsernamesInUse == USERNAME){
                cout << "Sorry, Username is already in use." << endl;
                main();
            }
        }
        UsernamesInUses.push_back(USERNAME);    
        cout << "Enter your name: "; cin >> NAME;
        Names.push_back(NAME);
        cout << "Enter your password: "; cin >> PASS;
        Passwords.push_back(PASS);
        main();
        break;                 //registering the new user in my username, password list.
    case 2:
        int arrayNumber = 0;
        cout << "Enter your Username:" ; cin >> USERNAME;
        cout << "Enter your password: "; cin >> PASS;
        for(auto UserNamesInUse : UsernamesInUses){                     //checking the uniquenesss of the username;
            if(UserNamesInUse == USERNAME){
                break;
            }
            else {
                arrayNumber++;
            }
        }

        if(Passwords[arrayNumber] != PASS){
            cout << "Invalid Credentials" << endl;
            main();
        }
        else{

        }

        
        
        break;
    default:
        main();
        break;
    }
}