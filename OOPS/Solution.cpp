#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
int addedmonths = 0;
typedef struct date{
    int Day;
    int Month;
    int Year;
}Date;
Date GlobalDate = {1,1,2024};
typedef struct Accounts{
    int AccountNo;
    int type;
}Accounts;

enum TransactionType{Deposit, Withdraw, Transfer};

typedef struct statement{
    Date date;
    TransactionType Type;
    float Amount;
}Statement;


 
// Making a set that stores unique usernames and passwords, so that no two account holders have the same username.
set <string> Usernames;

class SavingAccount{
    float InterestRate;
    public :
    float getInterestRate(void){
        return InterestRate;
    }
    
    public :
    void setInterestRate(float newRate){
        if (newRate<0){
            printf("Cannot have interest rate less than 0%%, it's your loss.\n");
            return;
        }
        if (newRate<=6.0){
            InterestRate = newRate;
            printf("Updated Interest Rate\n");
            return ;
        }
        printf("Sneaky Sneaky!! Interest rate cannot be greater than 6%%\n");

    }
};

class CheckingAccount{
    public :
    float getInterestRate(void){
        throw std::invalid_argument("There is no Interest Rate for current Account");
    }

};

class BankAccount:public SavingAccount,public CheckingAccount {
    private:
    friend class BranchManager;
    friend class AccountHolder;
    static int AccountNo;
    protected:
    int MyAccountNo;
    float Balance;
    Date OpeningDate = GlobalDate;
    int AccountType;

    vector <Statement> statements;
    public:
    int ReturnAccountNo(void){
        return MyAccountNo;
    }
    BankAccount(void){
        AccountNo++;
        MyAccountNo = AccountNo;
        cout<<"What type of Account? \n(1)Savings\n(2)Current\nChoose option: ";
        cin>>AccountType;
        if (AccountType==1){
            float rate;
            cout<<"What should be your interest rate?";
            cin>> rate;
            SavingAccount::setInterestRate(rate);
        }
        while (Balance<1000){

        cout<<"Enter the amount you want to initially add(min 1000 Rs): ";
        cin>>Balance;

        if (Balance<1000){
            cout<<"Sorry, Not Possible , please add more balance\n";
        }
        }
    }
    float interestRate(void){
        if (AccountType==1){
            return SavingAccount::getInterestRate() ;
        }
        return 0;
    }
    void getInterestRate(void){
        if (AccountType==1){
            printf("Interest Rate : %f",SavingAccount::getInterestRate()) ;

        }
        else{
        try
        {
            printf("Interest Rate : %f",CheckingAccount::getInterestRate()) ;
            /* code */
        }
        catch(const std::exception& e)
        {
            cout<<"Sorry , no interest rate in case of current account\n";
        }
        }
        return;
        
    }
    void deposit(float amount){
        statements.push_back({GlobalDate,Deposit,amount});
        
        Balance+=amount;
    }
    void withdraw(float amount){
        statements.push_back({GlobalDate,Withdraw,amount});
        Balance-=amount;
    }
    void transfer(float amount){
        statements.push_back({GlobalDate,Transfer,amount});
        Balance+=amount;
    }

};

vector <BankAccount> AllAccounts;
class AccountHolder{
    private:
    friend AccountHolder *Login(string);
    string Name , passwd;
    vector<int> AccountNos;
    public :
        string UserName;
    AccountHolder(void){
        cout<<"Enter your name: ";
        cin>>this->Name;

        cout<<"Enter a username for you: ";
        cin>>this->UserName;
        while(Usernames.find(UserName)!=Usernames.end()){
            cout<<"Username already taken, try another one: ";
            cin>>this->UserName;
        }
        Usernames.insert(UserName);
        cout<<"Set a secure Password: ";
        cin>>this->passwd;

    }
    void changePasswd(void ){
        cout<<"Enter the new password: ";
        cin>>this->passwd;
        cout<<"Password change successful!!"<<endl;
    }
    void CreateAccount(){

        AllAccounts.emplace_back();
        AccountNos.emplace_back(AllAccounts.back().MyAccountNo); 
    }
    vector<int> getAccounts(void ){
        return AccountNos;
    }     


};

map<string, AccountHolder> Holders; 
AccountHolder * Login(string username){ 
    map<string,AccountHolder> ::iterator iter;
    int FoundUsrName = 0;
    // map<string,AccountHolder> Holder(Holders);
    for(iter= Holders.begin();iter!=Holders.end();iter++){
        if ((*iter).first==username){
            string password;
            cout<<"Enter your supper secret password: ";
            cin>>password;
            if ((*iter).second.passwd==password){
                cout<<"Login successful!!\n";
                AccountHolder * ptr = &((*iter).second);
                return ptr;
            }
            cout<<"Wrong Password!"<<endl;
        }
        return NULL;
    }
    return  NULL;
    
};
class BranchManager;
// int LoginManger(string, BranchManager *);

int BankAccount::AccountNo = 0;
class BranchManager{
    string Username;
    string Password;
    friend int LoginManager(string Username,BranchManager *ptr);
    public:
    BranchManager(void){
        cout<<"Initializing Bank Manager's Account\n";
        sleep(0.5);
        cout<<"Enter UserName: ";
        cin>>Username;
        while(Usernames.find(Username)!=Usernames.end()){
            cout<<"Username already taken, try another one: ";
            cin>>Username;
        }
        Usernames.insert(Username);
        cout<<"Enter Password: ";
        cin>>Password;
    }
    vector <statement> getStatementOfAccount(int AccountNo){
        // Considering all the accounts that I have made are stored in vector and accessing the accountNo via the AccountNo provided, to get statements.
        return AllAccounts[AccountNo].statements; 
    }
    void fastforward(void){
        int days, months;
        cout<<"Enter No of days to fast forward(Consedering 30 days in a month):";
        cin>>days;
        cout<<"Enter No of months to fast forward:";
        cin>>months;
        months += (days+GlobalDate.Day)/30;
        GlobalDate.Day = (days+GlobalDate.Day)%30;
        GlobalDate.Month +=months;
        // addedmonths += months;
        int size  = AllAccounts.size();
        for (int x = 0;x<size;x++){
            if (AllAccounts[x].AccountType==1){
                AllAccounts[x].Balance=AllAccounts[x].Balance*(1+AllAccounts[x].interestRate()/100/12*months);
            }
        }

    }
};

int LoginManager(string Username,BranchManager *ptr){
    string Password;
    if (Username ==ptr->Username){
        cout<<"Enter Password: ";
        cin>>Password;

        if (Password==ptr->Password){
            printf("Logging you in , Boss!\n");
            return 1;
        }
        printf("Wrong Password\n");
        return 0;
    }
    printf("Wrong Username\n");
    return 0;
}

int main(){

    int userType;
    int Action = 0; //For account holder to login or signup
    string userName;
    AccountHolder *Current = NULL;
    BranchManager *TheOneAndOnly = NULL;
    BranchManager *IfLogin = NULL;
    int OutcomeOfLogin;
    while (userType!=3){
        cout<<"Knock Knock , who's there?"<<endl;
        cout<<"(1) Account Holder"<<endl;
        cout<<"(2) Branch Manager"<<endl;
        cout<<"(3) Exit"<<endl<<"Select (1/2/3): ";
        cin>>userType;
        if (userType==1){
            while(Action !=3){
                printf("(1)SignUp\n(2)Login\n(3)Exit\nChoose Option: ");
                cin>>Action;
                if (Action==2){
                    printf("Logging you in ...\nEnter your User-name:");
                    cin>>userName;
                    Current = Login(userName);
                    int Service =0;
                    if (Current!=NULL){
                    while (Service !=5)
                    {
                        cout<<"Following are the services you can avail:\n(1)Print list of accounts\n(2)Change Password\n(3)Create Account\n(4)Access a account\n(5)Exit\n";
                        cin>>Service;
                        if (Service==1){
                            vector<int> Accounts= Current->getAccounts();
                            printf("Following are the account nos of the accounts you hold\n");
                            for (int x = 0;x<Accounts.size();x++){
                                printf("%d\n",Accounts[x]);
                            }
                        }
                        else if (Service==2){
                            Current->changePasswd();
                        }
                        else if (Service==3){
                            Current->CreateAccount();
                        }
                        else if (Service==4){
                            int AccountNo;
                            cout<<"Enter Account Number\n";
                            cin>>AccountNo;
                            // Have to write code to check if the account belongs to holder , 
                            int size  = AllAccounts.size();
                            for (int x = 0;x<size;x++){
                                if (AllAccounts[x].ReturnAccountNo()==AccountNo){
                                    int InfoAccount = 0;
                                    float amount;
                                    while(InfoAccount!=5){
                                        cout<<"Can do following actions with your account:\n(1)Deposit\n(2)Withdraw\n(3)Transfer\n(4)Get Interest Rate\n(5)Exit\n";
                                        cin>>InfoAccount;
                                        if (InfoAccount==1){
                                            cout<<"Enter amount to deposit: ";
                                            cin>>amount;
                                            AllAccounts[x].deposit(amount);
                                    }
                                    else if (InfoAccount==2){
                                            cout<<"Enter amount to withdraw: ";
                                            cin>>amount;
                                            AllAccounts[x].withdraw(amount);
                                    }
                                    else if (InfoAccount==3){
                                            cout<<"Enter amount to Transfer: ";
                                            cin>>amount;
                                            AllAccounts[x].transfer(amount);
                                    }
                                    else if (InfoAccount==4){
                                            AllAccounts[x].getInterestRate();
                                                }
                                }
                            }
                            cout<<"Here's the infomation you need:-\n";
                        }
                    }
                    
                }
                }}
                else if (Action==1){
                    printf("inside:\n");
                    AccountHolder temp;
                    Holders[temp.UserName] = temp;
                }
                else if (Action==3){
                    break;
                }
            }
        }
        else if (userType==2)
        {
            if (TheOneAndOnly==NULL){
                BranchManager temp ;
                TheOneAndOnly = &temp;
            }
            else{
                cout<<"Logging you in...\nEnter UserName";
                cin>>userName;
                if (LoginManager(userName,TheOneAndOnly)){
                    IfLogin = TheOneAndOnly;
                }

            }
            if (IfLogin!= NULL){
                int action = 0;
                while(action!=4){
                    cout<<"Choose Service:\n(1)Get all statements\n(2)Fast Forward";
                    cin>>action;
                    if (action==1){
                        int AccountNo;
                        cout<<"Enter account No. :";
                        cin>>AccountNo;
                        vector<statement> statements = IfLogin->getStatementOfAccount(AccountNo);
                        int size = statements.size();
                        for(int x =0 ;x<size;x++){
                            printf("Transaction id :%d,Date:%d/%d/%d, Amount = %f,Type = %d \n",x,statements[x].date.Day,statements[x].date.Month,statements[x].date.Year,statements[x].Amount,statements[x].Type);
                        }
                    }
                    else if (action==2){
                        IfLogin->fastforward();
                    }

                }   
            }
        }
    }
    return 0;
}