#include <iostream>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <cmath>
using namespace std;


tm getDate(){
    auto now = std::chrono::system_clock::now();
    time_t nowTime = std::chrono::system_clock::to_time_t(now);
    tm date = *localtime(&nowTime);
    return date;
}
string makeaccno(int i){
    return string(9 - static_cast<int>(floor(log10(abs(i)))) - 1, '0') + to_string(i);
};
int accno_cntr=1;
tm currdate=getDate(); //Global date variable
auto currtime=chrono::system_clock::now();

class BankAccount {
    protected:
    string AccountNo;
    double Balance;
    tm OpenDate;  
    vector<string> Statements;

    public:
        BankAccount(double b) {
            AccountNo= makeaccno(accno_cntr);
            accno_cntr++;
            Balance=b;
            OpenDate=currdate;
        };

        void deposit(double amount){ 
            Balance=Balance+amount;
            Statements.push_back("Deposit of Rs. "+ to_string(amount)+" on "+to_string(currdate.tm_mday)+"/"+to_string(currdate.tm_mon+1)+"/"+to_string(currdate.tm_year+1900));
            };
        void withdraw(double amount){ 
            if (Balance>amount){
                Balance=Balance-amount;
                Statements.push_back("Withdrawal of Rs. "+ to_string(amount)+" on "+to_string(currdate.tm_mday)+"/"+to_string(currdate.tm_mon+1)+"/"+to_string(currdate.tm_year+1900));
            }
            else{
                cout<<"Insufficient Balance!!"<<endl;
            }
        };
        void transfer(double amount, string traccno, string type){
            if (type=="S"){
                if (Balance>amount&&amount<30000){ //cap @ Rs30000
                    Balance=Balance-amount;
                    Statements.push_back("Transfer of Rs. "+ to_string(amount) +" to "+ traccno+" on "+to_string(currdate.tm_mday)+"/"+to_string(currdate.tm_mon+1)+"/"+to_string(currdate.tm_year+1900));
                }
                else if(Balance>amount&&amount>30000) {
                    cout<<"Limit Exceeded, Transaction upto Rs.30000 is allowed!!"<<endl;
                    sleep(3);
                }
                else{
                    cout<<"\nInsufficient Balance!!"<<endl;
                    sleep(3);
                }
            }
            else{
                if (Balance>amount){
                    Balance=Balance-amount;
                    Statements.push_back("Transfer of Rs. "+ to_string(amount) +" to "+ traccno+" on "+to_string(currdate.tm_mday)+"/"+to_string(currdate.tm_mon+1)+"/"+to_string(currdate.tm_year+1900));
                }
                else{
                    cout<<"Insufficient Balance"<<endl;
                }
            }
        }
        void getstatements(){
            cout<<"\n\n------TRANSACTION HISTORY------\n\n"<<endl;
            for(auto i: Statements) cout<<i<<endl;
        };
        double getbalance(){
            return Balance;
        };
        string getaccountno(){
            return AccountNo;
        };
        virtual string getaccounttype(){return "NULL";};
        virtual void payinterest() {};
};
class SavingsAccount : public BankAccount{
    double InterestRate;
    tm initialdate;

    public:
    //forward declaration
        void setinterestrate(){
            if (Balance<=100000) InterestRate=0.0025; //3% p.a.
            else if (Balance<=200000) InterestRate=0.0033; //4% p.a.
            else if (Balance<=400000) InterestRate=0.0042; //5% p.a.
            else InterestRate=0.005; //6% p.a.
        };
    
        SavingsAccount(double b) : BankAccount(b) {
            setinterestrate();
            initialdate=currdate;
        };  

        int getinterestrate() {
            return InterestRate;
        };
        void payinterest(){
            int inimonth= (initialdate.tm_mon+1), iniyear=(initialdate.tm_year+1900);
            int currmonth= (currdate.tm_mon+1), curryear=(currdate.tm_year+1900), nomonth;
            nomonth = currmonth-inimonth+(curryear-iniyear)*12;
            for (int i=0;i<nomonth;i++){
                Balance=Balance+Balance*InterestRate;
                setinterestrate();
                Statements.push_back("Interest Paid of Rs. "+ to_string(Balance*InterestRate)+" Balance= "+ to_string(Balance)+" InterestRate= "+to_string(InterestRate));
            };
            initialdate=currdate;
        };
        string getaccounttype(){return "Savings";};
};
class CheckingAccount : public BankAccount {
    
    public:
        CheckingAccount(double b) : BankAccount(b) {}

        double getInterestRate() const {
            return 0; //accounts have zero interest rate
        }
        string getaccounttype(){return "Current";};
};
class AccountHolder {
    public:
        string Name;
        string Username;
        string Password;
        vector<BankAccount*> ListOfAccounts;
        AccountHolder() {}
        AccountHolder(string name,string username,string password){
            Name=name;Username=username;Password=password;
        };

        void createaccount(double balance,string type){
            if (type=="S"){
                ListOfAccounts.push_back(new SavingsAccount(balance)); //TRY PUTTING & HERE
            }
            else {
                ListOfAccounts.push_back(new CheckingAccount(balance));//TRY PUTTING & HERE
            }
        }
        void getaccounts(){
            cout<<"Accounts of "<<Name<<"\n\n"<<endl;
            for ( auto& i: ListOfAccounts){
                cout<<"Account No: "<<i->getaccountno()<<", Account Type: "<<i->getaccounttype()<<", Balance: Rs"<<i->getbalance()<<endl;
            };       
            };
        void changepassword(){
            string newpass;
            cout<<"Enter the new password: "<<endl;
            cin>>newpass;
            Password=newpass;
        };
};

AccountHolder accholders[100];
int acnthldr_cntr=0;

class BranchManager {
    static BranchManager* instance;
    string Username;
    string Password;
    BranchManager() : Username("branch_manager") , Password("123") {};
public:
    static BranchManager* getinstance(){
        if (instance==NULL) instance = new BranchManager();
        return instance;
    };
    
    void setusername(string uname) {Username=uname;}
    void setpassword(string psd) {Password=psd;}
    string getusername() {return Username;}
    string getpassword() {return Password;}
    void getstatementofaccounts(string accno){
        for(int i=0;i<acnthldr_cntr;i++ ){
            for (auto& j:accholders[i].ListOfAccounts){
                if (j->getaccountno()==accno) j->getstatements();
            };
 
        };
    };
    void getaccountholders(){
        for(int i=0;i<acnthldr_cntr;i++) {
            accholders[i].getaccounts(); 
            cout<<"*************************************************************"<<endl;
        };     
    };
    void fastforward(int days){
        auto timetoadd= days * chrono::hours(24);
        auto newtime= currtime+timetoadd;
        currtime=newtime;

        time_t newdate=chrono::system_clock::to_time_t(newtime);
        struct tm *Newdate = localtime(&newdate);
        currdate.tm_mday=Newdate->tm_mday;
        currdate.tm_mon=Newdate->tm_mon;
        currdate.tm_year=Newdate->tm_year;
        //paying interests to the Account holders
        for(int i=0;i<acnthldr_cntr;i++){
            for (auto& j:accholders[i].ListOfAccounts){
                j->payinterest();
            };
        };

    };
};

BranchManager*  BranchManager::instance=NULL;

//forward declaration
void page1();
void page1_1();
void page1_2();
void page1_2_sl(int i);
void page1_3();

void page1() {
        system("clear");
        cout<<"press 1: Account holder Signup (New Users Should Signup First)"<<endl;
        cout<<"Press 2: Account holder Login"<<endl;
        cout<<"press 3: Bank Manager Login"<<endl;
        int n; cin>>n;
        if (n==1) page1_1();
        else if (n==2) page1_2();
        else page1_3();
        return;
};

void page1_1(){
    system("clear");
    string n,un,psd;
    cout<<"------ACCOUNT HOLDER SIGNUP------\n\n"<<endl;
    cout<<"Enter your name: ";
    cin>>n;
    cout<<"Enter your username: ";
    cin>>un;
    cout<<"Enter your password: ";
    cin>>psd;

    //check of unique username
    for (int i=0;i<acnthldr_cntr;i++){
        if (un==accholders[i].Username){
            cout<<"!!Username Already exist, TRY AGAIN!!"<<endl;
            sleep(2);
            page1_1();
        };
    };
    
    accholders[acnthldr_cntr]=AccountHolder(n,un,psd);
    acnthldr_cntr++;
    cout<<"\n***Sign Up Successful***\n"<<endl;
    cout<<"Going to the initial page in 2sec....."<<endl;
    sleep(2);
    page1();
    return;
};
void page1_2(){
    system("clear");
    string un,psd;
    cout<<"------ACCOUNT HOLDER LOGIN------\n\n"<<endl;
    cout<<"Enter your username: ";
    cin>>un;
    cout<<"Enter your password: ";
    cin>>psd;

    for(int i=0;i<acnthldr_cntr;i++){
        if (accholders[i].Username==un && accholders[i].Password==psd){
            cout<<"\nLogin Successfull\n";
            sleep(1);
            page1_2_sl(i);
            return;
        }
        else continue;
    };
    cout<<"***Invalid username or password***"<<endl;
    cout<<"   TRY AGAIN    "<<endl;
    sleep(2);
    page1_2();
    return;
};
void page1_2_sl(int i){
    system("clear");
    cout<<"Welcome "<<accholders[i].Name<<"\n\n"<<endl;
    cout<<"press 1: See all your accounts"<<endl;
    cout<<"Press 2: Change password"<<endl;
    cout<<"press 3: Create a new Savings Account"<<endl;
    cout<<"press 4: Create a new Current Account"<<endl;
    cout<<"press 5: Make Transacrions "<<endl;
    cout<<"press 6: Go Back to initial Page"<<endl;
    int n; cin>>n;
    if (n==1) {
        accholders[i].getaccounts();
        cout<<"You have 30sec to view...."<<endl;
        sleep(30);
        page1_2_sl(i);
    }
    else if (n==2) {
        accholders[i].changepassword();
        cout<<"\n\n***Password changed Successfully***"<<endl;
        sleep(3);
        page1_2_sl(i);
    }
    else if (n==3||n==4) {
        double b;
        cout<<"Enter opening Balance:";
        cin>>b;
        if (n==3) accholders[i].createaccount(b,"S");
        else accholders[i].createaccount(b,"C");
        cout<<"\n\n***Account Created Successfully***"<<endl;
        sleep(2);
        page1_2_sl(i);
    }
    else if (n==5){
        string accno;
        accholders[i].getaccounts();
        cout<<"\n\nEnter the Account No. in which you would like to make a transaction: ";
        cin>>accno;
        for ( auto& j: accholders[i].ListOfAccounts){
                if (j->getaccountno()==accno){
                    while(1){
                        system("clear");
                        cout<<"Accessing Account No: "<<j->getaccountno()<<", Account Type: "<<j->getaccounttype()<<", Balance: Rs"<<j->getbalance()<<"\n\n"<<endl;
                        cout<<"press 1: Deposit funds"<<endl;
                        cout<<"Press 2: Withdraw funds"<<endl;
                        cout<<"press 3: Transfer funds"<<endl;
                        cout<<"press 4: Get Transaction History"<<endl;
                        cout<<"press 5: Go back to previous Page "<<endl;
                        int n; cin>>n;
                        if (n==1){
                            double amt;
                            cout<<"Enter the amount to be Deposited: ";
                            cin>>amt;
                            j->deposit(amt);
                            sleep(1);
                        }
                        else if(n==2){
                            double amt;
                            cout<<"Enter the amount to be Withdrawn: ";
                            cin>>amt;
                            j->withdraw(amt);
                            sleep(1);
                        }
                        else if(n==3){
                            double amt;
                            string acno,type;
                            if (j->getaccounttype()=="Savings") type="S";
                            else type="C";
                            cout<<"Enter the amount to be Transferred: ";
                            cin>>amt;
                            cout<<"Enter the A/c no. to whom Rs."<<amt<<" will be transferred: ";
                            cin>>acno;
                            j->transfer(amt, acno, type);
                            sleep(1);
                        }
                        else if (n==4){
                            j->getstatements();
                            cout<<"\n\nGoing Back in 20sec..."<<endl;
                            sleep(20);
                        }
                        else {
                            page1_2_sl(i);
                        }
                    }
                }
                else continue;
            };   


    }
    else if (n==6){
        page1();
    }
};
void page1_3(){
    system("clear");
    string un,psd;
    BranchManager* manager = BranchManager::getinstance();
    cout<<"------BRANCH MANAGER LOGIN------\n\n"<<endl;
    cout<<"Enter the username: ";
    cin>>un;
    cout<<"Enter the password: ";
    cin>>psd;
    if (manager->getusername()==un && manager->getpassword()==psd) cout<<"\nLogin Successful\n";
    else {
        cout<<"Username or Password is incorrect TRY AGAIN"<<endl;
        sleep(2);
        page1_3();
    };
    sleep(2);
    while(1){
        system("clear");
        cout<<"press 1: Get Account Statements"<<endl;
        cout<<"Press 2: Get Account Holders"<<endl;
        cout<<"press 3: FastForward"<<endl;
        cout<<"press 4: Go Back to the Initial Page"<<endl;
        int n; cin>>n;
        if (n==1){
            string accno;
            cout<<"Enter The Account No.: ";
            cin>>accno;
            manager->getstatementofaccounts(accno);
            cout<<"\n\nGoing Back in 20sec..."<<endl;
            sleep(20);
        }
        else if (n==2) {
            manager->getaccountholders();
            cout<<"\n\nGoing Back in 20sec..."<<endl;
            sleep(20);
        }
        else if (n==3) {
            int days;
            cout<<"Enter the No. of days to be skipped: ";
            cin>>days;
            cout<<"\nDate Now: "<<currdate.tm_mday<<"/"<<currdate.tm_mon+1<<"/"<<currdate.tm_year+1900<<endl;
            manager->fastforward(days);
            cout<<"Date After FastForward: "<<currdate.tm_mday<<"/"<<currdate.tm_mon+1<<"/"<<currdate.tm_year+1900<<endl;
            cout<<"Interest Returns are credited to the Account holders and can be viewed in their respective account statements"<<endl;
            cout<<"\n\nGoing Back in 15sec..."<<endl;
            sleep(15);
        }
        else page1();
    };


};

int main(){
    page1();
    return 0;
};