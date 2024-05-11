#include<iostream>
#include<list>
#include<string>
using namespace std ; 




    // get the current time 
const auto now = std::chrono::system_clock::now();      
// transform the time into a duration since the epoch 
const auto epoch   = now.time_since_epoch();      
// cast the duration into seconds 
int seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);



int balancecap= 10000000;


class BankAccount {
    public:
    int transfer();
    int deposit();
    int withdraw();
    int getBalance();
    int Accountnumber; 
    int opendate;
    protected:
    int balance;
     list<string> transaction;
};

int BankAccount::deposit(){
    int deposit;
    cout <<"Write the amount you want to deposit"<<endl;
    return balance+deposit;
}

int BankAccount::withdraw(){
    int withdraw;
    cout <<"Write the amount you want to deposit"<<endl;
    return balance-withdraw;
}

int BankAccount::getBalance(){
    return balance;
}

class Savingaccount : BankAccount {
    int interestrate;
public:
    bool isopen;
    int getInterestRate();
    Savingaccount();
    void closeSavingaccount(); 
    void setInterestRate(int rate);
    
};

void Savingaccount::closeSavingaccount( ){
    string response;
    std::cout<<"Do you want to close this bank account. Reply in Y/N"<<endl;
    std::cin >> response ; 
    if (response=="Y"){
      isopen = false ; 
 }
}

int Savingaccount::getInterestRate(){
    interestrate = 0.0000000000001*balance + 0.006*(seconds/(3600*24)) ;
    if (interestrate<6){
    return interestrate;
}
    else {
        return 6;
    }
}

Savingaccount::Savingaccount(){
    isopen = true ;
    std::cout<<"New Savingaccount account created."<<endl;
} 

void Savingaccount::setInterestRate(int rate){
    interestrate=rate;
}
class Currentaccount:BankAccount{
    int interestrate;
    public:
    bool isopen;
    void closeCurrentaccount(); 
    int getInterestRate();
    Currentaccount();
};

void Currentaccount::closeCurrentaccount( ){
    string response ;
    std::cout<<"Do you want to close this bank account. Reply in Y/N"<<endl;
    std::cin >> response ; 
    if (response=="Y"){
      isopen = false ; 
 }
}

int Currentaccount::getInterestRate(){
    return interestrate;
}


Currentaccount::Currentaccount(){
    std::cout<<"New Currentaccount account created."<<endl;
} 



class Bankaccntholder{
    public:
    void get(string pass , string user);
    void changepassword();
    void createaccount() ;
    void setAccountDetails(BankAccount* accnt) ;
    int getAccountNumber();
    list<BankAccount> ownaccounts();
    BankAccount* accountDetails;
    string password;
    string username;
    string name ;
    string setpass();
    string setuser();
   
   
    private:
    list<BankAccount> ownaccounts;
    string username;
    string Netbankingpass;
    

    
};

 list<Bankaccntholder> accounts;

 int Bankaccntholder::getAccountNumber() const {
    if (accountDetails) {
        return accountDetails->Accountnumber;
    }
    return -1; // Indicate no account associated
}

 void Bankaccntholder::changepassword(){
    string username , password ; 
    cout <<"what is your username ?"<<endl;
    cin>>username;
    cout<<"what do you want to change the password to ?"<<endl;
    cin>>password;
      for (auto& account : accounts) {
        if (account.username == username) {
            account.password = password;
            break; 
        }
    }
}
 

  void Bankaccntholder::setAccountDetails(BankAccount* accnt) {
    accountDetails = accnt;
  }

list<BankAccount> Bankaccntholder::ownaccounts(){
    return ownaccounts;
}

void Bankaccntholder::get(string pass,string user){
        password = pass; 
        username = user ; 
}



void Bankaccntholder::createaccount(){
    
    int point=0;
    Bankaccntholder BAH;
    BankAccount BA;
    std::cout<<"Do you already have an account ? Type Y/N"<<endl;
    string ans;
    std::cin>>ans;
    std::cout<<"Please type in username password "<<endl;
        string user,pass;
        std::cin >> user >> pass;
     std::cout<<"Please type in opening Bank Balance "<<endl;
    while(1){
     int balance ;
     int flag=0;
     std::cin >> balance ;
    if (balance>balancecap){
     cout<<"You are exceeding maximum allowed balance in a bank account "<<endl;
     flag++;
    }
    if(flag==0){break;}

    }
    if (ans=="N"){
        
    while(1){
        int flag=0;
        for (const auto& account : accounts) {
        
        if (user == account.username ){
            std::cout<<"Such an account already exists . Enter new username ."<<endl;
            flag++;
            break;
             
        }
      
       
      }  if(flag==0){break;}
        std::cout<<"Please type in username password "<<endl;
        string user,pass;
        std::cin >> user >> pass;
        std::cout<<"Please type in opening Bank Balance "<<endl;
     while(1){
     int balance ;
     int flag=0;
     std::cin >> balance ;
    if (balance>balancecap){
     cout<<"You are exceeding maximum allowed balance in a bank account "<<endl;
     flag++;
    }
    if(flag==0){break;}

    }
    }

        if (point==0){
        BAH.get(pass,user);
        BA.Accountnumber= accounts.size() + 1 ;
        point++;
        accounts.push_back(BAH);
      
        }
    
        else{
           int flag = 0 ;
        for (const auto& account : accounts) {
        if (user == account.username && pass==account.password){
            BAH= account;
            flag++;
            break;
        }
       
      }
      if (flag==0){
        std::cout<<"There is no such account . Please make new account.Restart the program"<<endl;
      }
      }

     
    
      
      
        
    }
     std::cout<<"do you want to open savings account or checking accountor not open any account "<<endl;
      string reply;
      std::cin>>reply;
      if (reply=="savings account"){
          Savingaccount SA ;
          BAH.ownaccounts().push_back(SA);
      }

      else if(reply=="current account"){
          Currentaccount CA ;
         BAH.ownaccounts().push_back(CA);
      }
}




class BranchManager{
    static BranchManager * Instance;
    BranchManager();

    public:
        void fastforward(int days);
        static BranchManager* getBM();
        void getAccountHolders();
        void getStatementofAccount();
        
};

BranchManager* Branchmanager :: Instance=nullptr;

void BranchManager::fastforward(){
    int days;
     cout <<"How many days do you wanna skip"<<endl;
     cin>>days;
    seconds=seconds - days*3600;
}

BranchManager::BranchManager(){
    std::cout<<"New BranchManager account created."<<endl;
}

BranchManager*BranchManager::getBM()
{
    if (Instance== nullptr){
        Instance=new BranchManager();
    }
    return Instance;
}

void BranchManager::getAccountHolders(){
    std::cout << "Bank Accounts:" << endl;
for (const auto& account : accounts) {
     std::cout << "Account Number: " << account.getAccountNumber() << endl;

}
}

void BranchManager::getStatementofAccount(){
    std::cout << "Bank Accounts:" << endl;
for (const auto& account : accounts) {
     std::cout << "Bank Statement: " << account.getbalance() << endl;

}

}


