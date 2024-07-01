#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

static vector<string> UsernamesInUses;

class BranchManager {
    void statement (int accno){
        
    }
};

class BankAccHolder {
public:
    string name;
    string username;
    string password;
    vector<Account*> accounts;
};


// void makeAcc (double accnum, int opendepo, string username, string accountType){

//     Account accnu>;
//     accnum

// }




class Account : public BankAccHolder{
public:
    double accno;


private:
    string accountType;
    double balance;
    vector<Transaction> transactions; // List of transactions for this account
    void deposit(double amount, const string& description);



};  


void Account::deposit(double amount, const string& description) {
    balance += amount;
    transactions.push_back(Transaction(description,amount));
}

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
    cout << "Press your key: "; cin >> c;
    
    switch (c)
    {
    case 1:
        cout << "Enter your Username:" ; cin >> USERNAME;
        for (auto UsernamesInUse : UsernamesInUses){
            if (USERNAME == UsernamesInUse){
                cout << "Sorry, Username is already in use." << endl;
                main();
            }
        }
        UsernamesInUses.push_back(USERNAME);    
        cout << "Enter your name: "; cin >> NAME;
        cout << "Enter your password: "; cin >> PASS;
        break;
    case 2:
        cout << "Enter your Username:" ; cin >> USERNAME;
        cout << "Enter your password: "; cin >> PASS;
        
        
        break;
    default:
        main();
        break;
    }





    

}