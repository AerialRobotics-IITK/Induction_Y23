#include <iostream>
#include <vector>
#include <string>
#include<cmath>
#include<unordered_map>
#include <ctime>
using namespace std;

time_t now = time(0);
    tm *tmn = localtime(&now);
    int year = 1900 + tmn->tm_year;
    int month = 1 + tmn->tm_mon;
    int datee = tmn->tm_mday;

//Date format

class Date{
    public:
    int Day;
    int Month;
    int Year;
    Date(int day,int month,int year){
        Day = day;
        Month = month;
        Year =  year;
    }
    void show_date(){
        cout << Day << "/" << Month << "/" << Year << "\t";
    }
    void Change_date(int day,int month,int year){
        Day = day;
        Month = month;
        Year = year;
    }
};

Date today_date = Date(datee,month,year);

int global_account_no = 1;

//Statement format

class Statement{
    private:
    Date date_of_transaction;
    float Amount;
    string Description;
    string Type;
    public:
     Statement(Date date, float amount, string description, string type) :
        date_of_transaction(date), Amount(amount), Description(description), Type(type) {}
        
    void show_statement(){
        date_of_transaction.show_date();
        cout << Description << "\t" << Type << "\t" << Amount << "\n" ;
    }
};

//Class for a particular bank account

class Bank_Account{
    private:
    int Account_no;
    float Balance;
    Date Open_date;
    vector <Statement> statements;
    public:
    Bank_Account(int account_no, float balance, Date open_date) :
        Account_no(account_no), Balance(balance), Open_date(open_date) {}
        
        
    void show_details(){
        cout << "\n Account no. -" << Account_no << "\t Balance-" << Balance << "\n";
        cout << "\n Open date:";
        Open_date.show_date();
        cout <<endl;
    }
    void withdraw(float amount,string description){
        Balance -= amount;
        statements.push_back(Statement(today_date, amount, description, "withdraw"));
    }
    void deposit(float amount,string description){
        Balance += amount;
        statements.push_back(Statement(today_date, amount, description, "deposit"));
    }
    void show_all_statements(){
        int n = statements.size();
        cout << "\n Date of transfer \t Description \t Type \t Amount\n";
        for(int i=0;i<n;i++){
            statements[i].show_statement();
        }
    }
};


//Special type of bank account

class Saving_Bank_Account:public Bank_Account{
    private:
    float interest_rate;
    public:
    Saving_Bank_Account(int account_no = 0, float balance = 0, Date open_date= today_date) :
        Bank_Account(account_no, balance, open_date) {
        // Calculate interest rate
        interest_rate = 6 * (1 - exp(-balance / 2)); // Using exponential function
    }
};

class Current_Bank_Account:public Bank_Account{
    private:
    float interest_rate = 0;
    public:
    Current_Bank_Account(int account_no =0, float balance =0, Date open_date = today_date) :
        Bank_Account(account_no, balance, open_date) {}
};

//Class for complete account holding by a partiular user

class Account_holder{
    private:
    string Name;
    string Username;
    string Password;
    

    public:
    //database for accounts inside a particular user
    unordered_map < int , Saving_Bank_Account> saving_bank_accounts;
    unordered_map < int , Current_Bank_Account> current_bank_accounts;
    Account_holder(string name = " ",string username = " ",string password = " "){
        Name = name;
        Username = username;
        Password = password;
    }
    void show_name(){
        cout << "\nName-" << Name <<endl;
    }
    bool check_saving_account(int account_no){
        if(saving_bank_accounts.find(account_no)!=saving_bank_accounts.end()) return true;
        else return false; 
    }
    bool check_current_account(int account_no){
        if(current_bank_accounts.find(account_no)!=current_bank_accounts.end()) return true;
        else return false; 
    }
    void delete_saving_account(int account_no){
        auto it = saving_bank_accounts.find(account_no);
        if (it != saving_bank_accounts.end()) { 
            saving_bank_accounts.erase(it); 
        } 
    }
    void delete_current_account(int account_no){
        auto it = current_bank_accounts.find(account_no);
        if (it != current_bank_accounts.end()) { 
            current_bank_accounts.erase(it); 
        } 
    }
    int create_saving_account(float balance){
        saving_bank_accounts[global_account_no] = Saving_Bank_Account(global_account_no, balance, today_date);
        return global_account_no++;
    }
    int create_current_account(float balance){
        current_bank_accounts[global_account_no] = Current_Bank_Account(global_account_no, balance, today_date);
        return global_account_no++;
    }
    void get_accounts(){
        for(auto it : saving_bank_accounts){
            cout << "\nSaving accounts list\n";
            it.second.show_details();
        }
        for(auto it : current_bank_accounts){
            cout << "\nCurrent accounts list\n";
            it.second.show_details();
        }
    }
    void change_password(string password){
        Password = password;
    }
};

// database of account holders
    unordered_map <string , string> account_holder_id;
    unordered_map <string , Account_holder> account_holders;


class Branch_Manager{
    private:
    string Username = "Aerial_Bank";
    string Password = "bank";
    public:
    bool check_username(string username){
        return(username==Username);
    }
    bool check_password(string password){
        return(password==Password);
    }
    bool transfer_request(int account_no,float amount,string description){
        for(auto it = account_holders.begin();it!=account_holders.end();it++){
            if(it->second.check_current_account(account_no)){
                it->second.current_bank_accounts[account_no].deposit(amount,description);
                cout <<"\nTransfer done successfully";
                return true;
            }
            else if(it->second.check_saving_account(account_no)){
                it->second.saving_bank_accounts[account_no].deposit(amount,description);
                cout <<"\nTransfer done successfully";
                return true;
            }
            else continue;
        }
        cout << "\n No such account found";
        return false;
    }
    void show_account_details(int account_no){
        for(auto it = account_holders.begin();it!=account_holders.end();it++){
            if(it->second.check_current_account(account_no)){
                it->second.show_name();
                it->second.current_bank_accounts[account_no].show_details();
                it->second.current_bank_accounts[account_no].show_all_statements();
                return;
            }
            else if(it->second.check_saving_account(account_no)){
                it->second.show_name();
                it->second.saving_bank_accounts[account_no].show_details();
                it->second.saving_bank_accounts[account_no].show_all_statements();
                return;
            }
            else continue;
        }
        cout << "\n No such account found";
    }
    void list_of_all_accounts(){
        for(auto it =account_holders.begin();it!=account_holders.end();it++){
            for(auto it2 = it->second.saving_bank_accounts.begin();it2!=it->second.saving_bank_accounts.end();it2++){
                it2->second.show_details();
                cout << endl;
            }
            for(auto it2 = it->second.current_bank_accounts.begin();it2!=it->second.current_bank_accounts.end();it2++){
                it2->second.show_details();
                cout << endl;
            }
        }
    }
};
Branch_Manager Aerial_branch_manager;



int main(){
    

    //frontend
    int x;
    Front:
    cout << "\nEnter option no. \n 1.Signup for a account holder \n 2.Login as a account holder \n 3. Login as Branch manager" ;
    cin >> x ;
    if(x==1){
        string name;
        string username;
        string password1,password2;
        cout << "\nEnter name:";
        cin >> name ;
        cout << "\nEnter username:" ;
       cin >> username ;
        password:
        cout << "\nEnter password(Try to create a very strong password):" ;
        cin >> password1;
        cout << "\nConfirm your password:";
        cin >> password2;
        if(password1==password2){
            account_holder_id[username] = password1;
            account_holders[username] = Account_holder(name,username,password1);
            cout << "\nAccount holder successfully created\n Login to create your first bank account";
            goto Front;
        }
        else {
            cout << "\nPassword doesn't match,Try again!";
            goto password;
        }
    }
    if(x==2){
        cout << "\n Enter username:" ;
        string username;
        cin >> username;
        string password;
        cout << "\n Enter password:" ;
        cin >> password;
        if(account_holder_id[username]=="\0"){
            cout << "\nNo such account holder present in the Bank,please Signup first:" ;
            goto Front;
        }
        else if(account_holder_id[username]==password){
            cout << "\nSuccessfully logged in :)";
        }
        else {
            cout << "\nWrong password,Try again" ;
            goto Front;
        }
        Userpage:
        cout << "\n Welcome to your bank account Handle: \n Choose option you want to do \n 1.Create account\n 2.Change password \n 3.List of all accounts \n 4.Delete a account\n 5.Transaction in an account 6.Statement of an account\n 7.Exit/Logout";
        int y;
        cin >> y;
        if(y==1){
            accounts:
            cout << "\n Choose type of account- 1.Saving\t2.Current\t3.go back";
            int a;
            cin >> a;
            if(a==1){
                cout <<"\n Enter opening amount- ";
                float balance;
                cin >> balance;
                int account_no = account_holders[username].create_saving_account(balance);
                cout <<"\n New saving account successfully created.\n Your bank account no. is " <<account_no;
                goto Userpage;
            }
            else if(a==2){
                cout <<"\n Enter opening amount- ";
                float balance;
                cin >> balance;
                int account_no = account_holders[username].create_current_account(balance);
                cout <<"\n New current account successfully created.\n Your bank account no. is " <<account_no;
                goto Userpage;
            }
            else if(a==3){
                goto Userpage;
            }
            else {
                cout << "\n Choose valid option";
                goto accounts;
            }
        }
        else if(y==2){
            string password1,password2;
            cout << "\nEnter password(Try to create a very strong password):" ;
            cin >> password1;
            cout << "\nConfirm your password:";
            cin >> password2;
            if(password1==password2){
                account_holder_id[username] = password1;
                account_holders[username].change_password(password1);
                cout << "\nPassword successfulyy changed.";
                goto Userpage;
            }
            else {
                cout << "\nPassword doesn't match,Try again!";
                goto Userpage;
            }
        }
        else if(y==3){
            account_holders[username].get_accounts();
            goto Userpage;
        }
        else if(y==4){
            deleting:
            cout << "\n Choose type of account- 1.Saving\t2.Current\t3.go back";
            int a;
            cin >> a;
            if(a==1){
                cout << "\nEnter account no.:" ;
                int account;
                cin >> account;
                account_holders[username].delete_saving_account(account);
                cout << "\nAccount succesfully deleted.";
                goto Userpage;
            }
            else if(a==2){
                cout << "\nEnter account no.:" ;
                int account;
                cin >> account;
                account_holders[username].delete_current_account(account);
                cout << "\nAccount succesfully deleted.";
                goto Userpage;
            }
            else if(a==3) goto Userpage;
            else {
                cout << "\n wrong option,Try again.";
                goto deleting;
            }
        }
        else if(y==5){
            transaction:
            int type;
            cout << "\nEnter type of account for transaction\n 1.Saving \t 2.Current \t 3.Go back";
            cin >> type;


            if(type==1){
                int account_no;
                cout <<"\nEnter account no.:";
                cin >> account_no;
                if(!account_holders[username].check_saving_account(account_no)){
                    cout << "\n No such account present:";
                    goto transaction;
                }


                cout << "\nEnter transaction type \n 1.Withdraw \t 2.Deposit \t 3.Transfer \t 4.back";
                int  input;
                cin >> input;
                if(input==1){
                    
                    cout << "Enter amount:" ;
                    int amount_;
                    cin >> amount_;
                    if(amount_>100000){
                        cout << "\nTransaction limit exceeded: \n only below 100000 is allowed";
                        goto transaction;
                    }
                    string description;
                    cout << "\nEnter short description about the transfer WITHOUT SPACE";
                    cin >> description;
                    account_holders[username].saving_bank_accounts[account_no].withdraw(amount_,description);
                    cout << "Withdrawn done successfully";
                    goto Userpage;
                }
                else if(input==2){
                    
                    cout << "Enter amount:" ;
                    int amount_;
                    cin >> amount_;
                    if(amount_>100000){
                        cout << "\nTransaction limit exceeded: \n only below 100000 is allowed";
                        goto transaction;
                    }
                    string description;
                    cout << "\nEnter short description about the transfer WITHOUT SPACE";
                    cin >> description;
                    account_holders[username].saving_bank_accounts[account_no].deposit(amount_,description);
                    cout << "Deposit done successfully";
                    goto Userpage;
                }
                else if(input==3){
                    cout << "\nEnter bank account no. to which money is to be transferred";
                    int account2;
                    cin >> account2;
                    cout << "\n Enter amount";
                    float amount;
                    cin >> amount;
                    if(amount>100000){
                        cout << "\nTransaction limit exceeded: \n only below 100000 is allowed";
                        goto transaction;
                    }
                    cout << "\nGive description WITHOUT SPACE:";
                    string description;
                    cin >> description;
                    if(Aerial_branch_manager.transfer_request(account2,amount,description)){
                        account_holders[username].saving_bank_accounts[account_no].withdraw(amount,description);
                    };
                    goto Userpage;
                    goto Userpage;
                }
                else if(input==4){
                    goto Userpage;
                }
                else {
                    cout << "\n Wrong output,Try again.";
                    goto transaction;
                }
            }


            else if(type==2){
                int account_no;
                cout <<"\nEnter account no.:";
                cin >> account_no;
                if(!account_holders[username].check_current_account(account_no)){
                    cout << "\n No such account present:";
                    goto transaction;
                }


                cout << "\nEnter transaction type \n 1.Withdraw \t 2.Deposit \t 3.Transfer \t 4.back";
                int  input;
                cin >> input;
                if(input==1){
                    
                    cout << "Enter amount:" ;
                    int amount_;
                    cin >> amount_;
                    string description;
                    cout << "\nEnter short description about the transfer WITHOUT SPACE";
                    cin >> description;
                    account_holders[username].current_bank_accounts[account_no].withdraw(amount_,description);
                    cout << "Withdrawn done successfully";
                    goto Userpage;
                }
                else if(input==2){
                    
                    cout << "Enter amount:" ;
                    int amount_;
                    cin >> amount_;
                    string description;
                    cout << "\nEnter short description about the transfer WITHOUT SPACE";
                    cin >> description;
                    account_holders[username].current_bank_accounts[account_no].deposit(amount_,description);
                    cout << "Deposit done successfully";
                    goto Userpage;
                }
                else if(input==3){
                    cout << "\nEnter bank account no. to which money is to be transferred";
                    int account2;
                    cin >> account2;
                    cout << "\n Enter amount";
                    float amount;
                    cin >> amount;
                    cout << "\nGive description: WITHOUT SPACE";
                    string description;
                    cin >> description;
                    if(Aerial_branch_manager.transfer_request(account2,amount,description)){
                        account_holders[username].current_bank_accounts[account_no].withdraw(amount,description);
                    };
                    goto Userpage;
                }
                else if(input==4){
                    goto Userpage;
                }
                else {
                    cout << "\n Wrong output,Try again.";
                    goto transaction;
                }
            }
            else if(type==3){
                goto Userpage;
            }
            else{
                cout <<"\nWrong input,try again";
                goto transaction;
            }            
        }
        else if(y==6){
            statements:
            cout << "\nEnter type of account 1.Saving 2.Current 3.go back";
            int z;
            cin >> z;
            if(z==1){
                int account;
                cout << "\nEnter account no.";
                cin >> account;
                if(!account_holders[username].check_saving_account(account)){
                    cout << "\n No such account present:";
                    goto statements;
                }
                account_holders[username].saving_bank_accounts[account].show_all_statements();
                cout <<endl;
                goto Userpage;
            }
            else if(z==2){
                int account;
                cout << "\nEnter account no.";
                cin >> account;
                if(!account_holders[username].check_saving_account(account)){
                    cout << "\n No such account present:";
                    goto statements;
                }
                account_holders[username].current_bank_accounts[account].show_all_statements();
                cout <<endl;
                goto Userpage;
            }
            else if(z==3){
                goto Userpage;
            }
            else {
                cout << "\nwrong option try again";
                goto statements;
            }
        }
        else if(y==7){
            goto Front;            
        }
        else{
            goto Userpage;
        }
        
    }
    if(x==3){
        cout << "\nEnter Username:";
        string username;
        cin >> username;
        if(!Aerial_branch_manager.check_username(username)){
            cout << "\nWrong Username!";
            goto Front;
        }
        cout << "\nEnter Password:";
        string password;
        cin >> password;
        if(!Aerial_branch_manager.check_password(password)){
            cout << "\nWrong password!";
            goto Front;
        }
        Manager_front:
        cout << "\n Enter option no.- \n 1.Show account details \n 2.List of all accounts \n 3.Change date \n 4.go back";
        int input;
        cin >> input;
        if(input==1){
            cout << "\nEnter account no.:";
            int account_no;
            cin >> account_no;
            Aerial_branch_manager.show_account_details(account_no);
            goto Manager_front;
        }
        else if(input==2){
            Aerial_branch_manager.list_of_all_accounts();
        }
        else if(input==3){
            int new_date,new_month,new_year;
            cout << "\n Enter date";
            cin >> new_date;
            cout << "\n Enter month";
            cin >> new_month;
            cout << "\n Enter year";
            cin >> new_year;
            today_date.Change_date(new_date,new_month,new_year);
            cout << "\n Date successfully changed.";
            goto Manager_front;
        }
        else if(input==4){
            goto Front;
        }
        else {
            cout << "\n No such option,";
            goto Manager_front;
        }
    }
    else {
        cout << "\nNo such option" ;
        goto Front;
    }
    return 0;
}





