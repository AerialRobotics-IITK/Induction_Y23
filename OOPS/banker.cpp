
// I have been having trouble integrating the various classes and components.
// I couldn't understand how to link them. However, I have made the various classes and tried to implement the logic.


#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> UsernamesInUses;               // Just a list of existing usernames and passwords and names.
vector<string> Names;
vector<string> Passwords;

double accountNumber = 100000000;            // I have started alloting the accnum in the order they are created, irrespective of the user creating it.

class Transaction {
private:
    string description;
    double amount;

public:
    Transaction(const string& desc, double& amt) : description(desc), amount(amt) {}

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
    Account(int accountnum, const string type, int paisa) : accnum(accountnum), accountType(type), amount(paisa) {}

    void deposit(double deposit);
    void withdraw(double withdraw);
    void getStatement();
    int getAccNum(){
        return accnum;
    };
    int getamount(){
        return amount;
    }
    string getAccType(){
        return accountType;
    }
};

class User {
private:
    string username;
    string password;
    vector<Account> accounts;

public:
    
    User(const string& uname) : username(uname) {}

    void addAccount(const Account& account) { accounts.push_back(account); };

    int getNumberOfAccounts(){
        return accounts.size();
    }

    int returnAccnum(int a){
        return accounts[a].getAccNum();
    }

    string returnAccType(int a){
        return accounts[a].getAccType();
    }

    void getaccountNumber(){
        cout << "You have the following accounts:" << endl;
        for(int i = 0; i < accounts.size(); i++){
            cout << (i+1) <<"."<< accounts[i].getAccNum() << endl;
        }
    }

    void getAccountStatement(int i){
        accounts[i].getStatement();
    }

    int getAccountBalance(int i){
        return accounts[i].getamount();
    }
    void depositInAccount(int i, double ammt){
        accounts[i].deposit(ammt);

    }
    void withdrawFromAccount(int i, double ammt){
        accounts[i].withdraw(ammt);
    }
};

void Account::deposit(double deposit) {
    amount += deposit;
    transactions.push_back(Transaction("Deposit", deposit));
}

void Account::withdraw(double withdraw) {
    if (withdraw > amount) {
        cout << "Invalid withdrawal : Insufficient funds" << endl;
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

vector<User> Users;
vector<Account> ExistingAccounts;


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
        cout << "Press your choice: "; std::cin >> c;

        
            if(c == 1){
                cout << "Enter your Username:" ; std::cin >> USERNAME;
                for (const auto& user : UsernamesInUses) {                           //checking the uniquenesss of the username;
                    if (user == USERNAME) {
                        cout << "Sorry, Username is already in use." << endl;
                        main();
                    }
                }
                UsernamesInUses.push_back(USERNAME);
                cout << "Enter your name: "; std::cin >> NAME;
                Names.push_back(NAME);
                cout << "Enter your password: "; std::cin >> PASS;
                Passwords.push_back(PASS);
                Users.push_back(User(USERNAME));
                main();
            }
            
            
            else if(c == 2){
                int flag = 0;
                int arrayNumber = 0;
                cout << "Enter your Username:" ; std::cin >> USERNAME;

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

                cout << "Enter your password: "; std::cin >> PASS;
                
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
                    cout << "Press your choice: "; std::cin >> choice;

                    if(choice == 'N'){
                        int response;
                        cout << "For a savings account, press 1" << endl;
                        cout << "For a checking/current account, press 2" << endl;
                        cout << "Press your choice: "; std::cin >> response;
                        int rupaiya;
                        cout << "Enter your starting balance:"; std::cin >> rupaiya;
                        if(rupaiya>=1000){
                            if(response == 1){
                                Users[arrayNumber].addAccount(Account(accountNumber, "Savings", rupaiya));
                                // ExistingAccounts.push_back(Account(accountNumber++, "Savings", rupaiya));
                                cout << "Account successfully created" << endl;
                                
                            }
                            else if(response == 2){  
                                // cout << "Enter your starting balance:"; std::cin >> rupaiya;
                                Users[arrayNumber].addAccount(Account(accountNumber, "Checking/Current", rupaiya));
                                // ExistingAccounts.push_back(Account(accountNumber++, "Checking/Current", rupaiya));
                                cout << "Account successfully created" << endl;
                                                    
                            }                        
                            else{
                                cout << "Invalid Choice";
                                
                            }
                        }
                        else{
                            cout << "Insufficient amount!" << endl;   
                        }
                        main();
                    }
                    
                    else if(choice == 'B'){
                        int AN;
                        cout << "The Account Numbers are:" << endl;
                        Users[arrayNumber].getaccountNumber();
                        cout<< "Enter the Account Number: "; cin >> AN;
                        for(int i=0; i< Users[arrayNumber].getNumberOfAccounts();i++){
                            if(Users[arrayNumber].returnAccnum(i) == AN){
                                cout << "Current Balance" << Users[arrayNumber].getAccountBalance(i) << endl;
                            }
                        }
                        main();
                    }
                    
                    else if(choice == 'S'){
                        int AN;
                        Users[arrayNumber].getaccountNumber();
                        cout<< "Enter the Account Number:"; cin >> AN;
                        for(int i=0; i< Users[arrayNumber].getNumberOfAccounts();i++){
                            if(Users[arrayNumber].returnAccnum(i) == AN){
                                Users[arrayNumber].getAccountStatement(i);
                            }
                        }
                        main();
                    }
                    
                    else if(choice == 'D'){
                        int AN;
                        int depovalue;
                        Users[arrayNumber].getaccountNumber();
                        cout<< "Enter the Account Number:"; cin >> AN;
                        cout<< "Enter the deposit amount: "; cin >> depovalue;
                        int accountArrayNumber;
                        for(int i=0; i< Users[arrayNumber].getNumberOfAccounts();i++){
                            if(Users[arrayNumber].returnAccnum(i) == AN){
                                Users[arrayNumber].depositInAccount(i,depovalue);
                            }
                        }
                        main();

                    }
                    
                    else if(choice == 'W'){
                        int AN;
                        int withdrawalvalue;
                        Users[arrayNumber].getaccountNumber();
                        cout<< "Enter the Account Number:"; cin >> AN;
                        cout<< "Enter the deposit amount: "; cin >> withdrawalvalue;
                        int accountArrayNumber;
                        for(int i=0; i< Users[arrayNumber].getNumberOfAccounts();i++){
                            if(Users[arrayNumber].returnAccnum(i) == AN){
                                Users[arrayNumber].withdrawFromAccount(i,withdrawalvalue);
                            }
                        }
                        main();
                    }
                    
                    else if(choice == 'P'){
                        cout << "Enter your new password: "; cin >> Passwords[arrayNumber];
                        cout << "Password Successfully Changed!"<< endl;
                    }
                    
                    else {
                        cout << "Invalid choice" << endl;
                    }
                    main();
                }
            }

            else if(c == 3){
                string adminuser;
                string adminpass;
                cout << "Enter Admin Username: " ; cin >> adminuser;
                if(adminuser != "ADMIN123"){
                    cout << "INVALID USERNAME!" <<endl;
                    main();
                }
                cout << "Enter Admin Password: " ; cin >> adminpass;
                if(adminpass != "ADMIN123"){
                    cout << "INVALID CREDENTIALS" << endl;
                    main();
                }

                cout << "To get all Users and their accounts, press 1" << endl;
                cout << "To get Statement of an account, press 2" << endl;
                int response;
                cout << "Enter your choice: "; cin >> response;


                if(response == 1){
                    for(int i=0; i < Users.size(); i++){
                        cout << UsernamesInUses[i] << endl;
                        for(int j=0; j<Users[i].getNumberOfAccounts();j++){
                            cout << "    " << (j+1) << ". " << Users[i].returnAccnum(j) << " : " <<  Users[i].returnAccType(j) <<endl;
                        }
                        cout << endl;
                    }
                }

                else if(response == 2){
                    int AN;
                    int flag = 0;
                    int arrayNumber=0;
                    string AU;
                    cout << "Enter the account's username: "; cin >> AU;

                    for(auto UserNamesInUse : UsernamesInUses){                     
                        if(UserNamesInUse == AU){
                            flag =1;
                            break;
                        }
                        else {
                            arrayNumber++;
                        }
                    }

                    if (!flag){
                        cout << "USERNAME NOT FOUND" <<endl;
                        // system("CLS");
                        main();
                    }

                    Users[arrayNumber].getaccountNumber();
                    cout << endl;
                    cout << "Enter the Account Number: "; cin >> AN;
                    for(int i=0; i< Users[arrayNumber].getNumberOfAccounts();i++){
                        if(Users[arrayNumber].returnAccnum(i) == AN){
                            Users[arrayNumber].getAccountStatement(i);
                        }
                    }
                    main();
                }

                else{
                    cout << "Invalid Choice" << endl;
                    main();
                }

            }
    
    }
    
}