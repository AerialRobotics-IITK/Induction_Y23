
// I have been having trouble integrating the various classes and components.
// I couldn't understand how to link them. However, I have made the various classes and tried to implement the logic.


#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> UsernamesInUses;
vector<string> Names;
vector<string> Passwords;
double accountNumber = 100000000;

class Transaction {
private:
    string description;
    double amount;

public:
    Transaction(const string& desc, double amt) : description(desc), amount(amt) {}

    string getDescription() const { 
        return description; 
        }
    double getAmount() const {
        return amount; 
        }
};

class Account {
private:
    string accountType;
    int accnum;
    double amount;
    vector<Transaction> transactions;

public:
    Account(int accountnum, const string& type) : accnum(accountnum), accountType(type), amount(0) {}

    void deposit(double deposit);
    void withdraw(double withdraw);
    void getStatement();
};

class User {
private:
    string username;
    string password;
    vector<Account> accounts;

public:
    User(const string& uname) : username(uname) {}

    void addAccount(const Account& account) { accounts.push_back(account); }
};

void Account::deposit(double deposit) {
    amount += deposit;
    transactions.push_back(Transaction("Deposit", deposit));
}

void Account::withdraw(double withdraw) {
    if (withdraw > amount) {
        cout << "Invalid withdrawal" << endl;
    } else {
        amount -= withdraw;
        transactions.push_back(Transaction("Withdrawal", withdraw));
    }
}

void Account::getStatement() {
    for (const auto& transaction : transactions) {
        cout << transaction.getDescription() << ": " << transaction.getAmount() << endl;
    }
}

int main (){
     int c;
     char choice;
    string NAME;
    string USERNAME;
    string PASS;

    while (true) {
        cout << "\t\t\t==================================================\t\t\t" << endl;
        cout << "\t\t\t         WELCOME TO PRASUN'S BANK OF INDIA        \t\t\t" << endl;
        cout << "\t\t\t            ---------------------------           \t\t\t" << endl;
        cout << "\t\t\t                       HOME                       \t\t\t" << endl;
        cout << "\t\t\t==================================================\t\t\t" << endl;
        cout << "For Registering yourself, press 1" << endl;
        cout << "For Account Holder Login, press 2" << endl;
        cout << "For Branch Manager Login, press 3" << endl;
        cout << "Press your choice: "; cin >> c;

        
            if(c == 1){
                cout << "Enter your Username:" ; cin >> USERNAME;
                for (const auto& user : UsernamesInUses) {                           //checking the uniquenesss of the username;
                    if (user == USERNAME) {
                        cout << "Sorry, Username is already in use." << endl;
                        main();
                    }
                }
                UsernamesInUses.push_back(USERNAME);
                cout << "Enter your name: "; cin >> NAME;
                Names.push_back(NAME);
                cout << "Enter your password: "; cin >> PASS;
                Passwords.push_back(PASS);
                User userObject(USERNAME);
                main();
            }
            
            
            else if(c == 2){
                int flag = 0;
                int arrayNumber = 0;
                cout << "Enter your Username:" ; cin >> USERNAME;

                for(auto UserNamesInUse : UsernamesInUses){                     
                    if(UserNamesInUse == USERNAME){
                        flag =1;
                        break;
                    }
                    else {
                        arrayNumber++;
                    }
                }

                if (!flag){
                    cout << "username not found" <<endl;
                    // system("CLS");
                    main();
                }

                cout << "Enter your password: "; cin >> PASS;
                
                if(Passwords[arrayNumber] != PASS){
                    cout << "Invalid Credentials" << endl;
                }
                
                else{
                    cout << "For Creating a new account, press N" << endl;
                    cout << "For Checking the balance of an existing account, press B" << endl;
                    cout << "For the statement of an existing account, press S" << endl;
                    cout << "For depositing in an existing account, press D" << endl;
                    cout << "For withdrawal from an existing account, press W" << endl;
                    cout << "For changing password,  press P" << endl;
                    cout << "Press your choice: "; cin >> choice;

                    if(choice == 'N'){
                        int response;
                        cout << "For a savings account, press 1" << endl;
                        cout << "For a checking/current account, press 2" << endl;
                        cout << "Press your choice: "; cin >> response;
                        if(response == 1){
                            Account userAccount(accountNumber++, "Savings");
                            
                        }
                        if(response == 2){
                            Account userAccount(accountNumber++, "Checking/Current");
                                                
                        }                        
                        else{
                            cout << "Invalid Choice";
                            main();
                        }


                    }
                    else if(choice == 'B'){

                    }
                    else if(choice == 'S'){

                    }
                    else if(choice == 'D'){

                    }
                    else if(choice == 'W'){

                    }
                    else if(choice == 'P'){

                    }
                    else {
                        cout << "Invalid choice" << endl;
                    }
                    main();
                }
            }
    }
    
}