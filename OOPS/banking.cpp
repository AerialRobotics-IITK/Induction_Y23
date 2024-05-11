#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;

double MAX_BAL=100000000;//MAX BALANCE 10 cr

//TIME VARIATION
string date_curr(void){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [100];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,100,"%F",timeinfo);
    string a(buffer);
    return a;
}
string date_global_s=date_curr();
string date_global=date_curr();

string date_change(int m, int d, int y){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [100];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    timeinfo->tm_mday=d;
    timeinfo->tm_mon=m;
    timeinfo->tm_year=y;
    strftime (buffer,100,"%F",timeinfo);
    string a(buffer);
    return a;
}






long long int random_gen(){
    return rand()%900000000+100000000;
}




//ACCOUNTS CLASS
class Account{
    public:
        char type;
        long long int account_no;
        void deposit(double amt);
        void withdraw(double amt);
        void transfer(double amt,long long int account_1,long long int account_2);
        void show_statement(void);
        
    protected:
       
        double account_bal;
        string open_date;
        vector <pair<pair<string,double>,pair<string, double> > > account_st;
};
//FUNCTIONS OF ACCOUNT CLASS
void Account::deposit(double amt){
    account_bal=account_bal+amt;
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=account_bal;

    pair<string,double> stt_chg;
    stt_chg.first="DEPOSITED Rs";
    stt_chg.second=amt;

    pair<pair<string,double>,pair<string,double> > PAIR;

    PAIR.first=stt;
    PAIR.second=stt_chg;


    account_st.push_back(PAIR);
}
void Account::withdraw(double amt){
    account_bal=account_bal-amt;
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=account_bal;
    
    pair<string,double> stt_chg;
    stt_chg.first="WITHDRAWN Rs";
    stt_chg.second=amt;

    pair<pair<string,double>,pair<string,double> > PAIR;
    PAIR.first=stt;
    PAIR.second=stt_chg;

    account_st.push_back(PAIR);
}
void Account::transfer(double amt,long long int account_1,long long int account_2){
    cout<<"NOT AVAILABLE";
}
void Account::show_statement(void){
    for(int i=account_st.size()-1;i>=0;i--){
        cout<<i+1<<". "<<account_st[i].first.first<<" "<<account_st[i].second.first<<account_st[i].second.second<<" FINAL BAL:"<<account_st[i].first.second<<endl;
    }
}



//SAVINGS ACCOUNT
class Savings_Acc: public Account{
    public:
        Savings_Acc(long long int open_bal);
        float get_interest_rate(void);
        void set_interest_rate(void);

    private:
        float interest_rate;//IN PERCENTAGE
};
//constructor of SAVINGS
Savings_Acc::Savings_Acc(long long int open_bal){
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=open_bal;
    pair<string,double> stt_chg;
    stt_chg.first="DEPOSITED Rs";
    stt_chg.second=open_bal;
    
    pair<pair<string,double>,pair<string,double> > PAIR;
    PAIR.first=stt;
    PAIR.second=stt_chg;
    
    account_st.push_back(PAIR);
    account_no=random_gen();
    type='S';
    account_bal=open_bal;
    open_date=date_global;
}

//CURRENT ACCOUNT
class Current_Acc: public Account{
    public:
        Current_Acc(long long int open_bal);
        float get_interest_rate(void);
    
    private:
        float interest_rate=0;

};
//constructor of CURRENT
Current_Acc::Current_Acc(long long int open_bal){
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=open_bal;

    pair<string,double> stt_chg;
    stt_chg.first="DEPOSITED Rs";
    stt_chg.second=open_bal;

    pair<pair<string,double>,pair<string,double> > PAIR;

    PAIR.first=stt;
    PAIR.second=stt_chg;
    account_st.push_back(PAIR);
    account_no=random_gen();
    account_bal=open_bal;
    type='C';
    open_date=date_global;
}



//BANK HOLDER CLASS
class Bank_Holder{
    private:
        string name;
        string username;
        string password;
        vector <Account> accounts;
        vector <Savings_Acc> accounts_s;
        vector <Current_Acc> accounts_c;
    public:    
        Bank_Holder(string n,string u, string p);
        void get_Accounts(void);//DONE
        void changepasswd(string s1,string s2);
        void createAccount(char c,long long int amt);
        void accessAccount(char c,long long int account_no);
        bool checkAccess(string u,string p);//DONE
};
//CONSTRUCTOR of Bank_Account_Holder
Bank_Holder::Bank_Holder(string n,string u, string p){
    name=n;
    username=u;
    password=p;
}
//FUNCTION DEFINITIONS:
bool Bank_Holder::checkAccess(string u,string p){
    if((username==u)&&(password==p)){
        return true;
    }
    else{
        return false;
    }
}
void Bank_Holder::get_Accounts(){
    for(int i=0;i<accounts_s.size();i++){
            cout<<"SAVINGS ACCOUNT:";
            cout<<accounts_s[i].account_no<<endl;
    }
    for(int i=0;i<accounts_c.size();i++){
            cout<<"CURRENT ACCOUNT:";
            cout<<accounts_c[i].account_no<<endl;
    }
    cout<<endl<<endl;      
}   
void Bank_Holder::createAccount(char c,long long int amt){
    if(c=='S'||c=='s'){
        Savings_Acc acc_created(amt);
        accounts_s.push_back(acc_created);
    }
    else if(c=='C'||c=='c'){
        Current_Acc acc_created(amt);
        accounts_c.push_back(acc_created);
    }
    else{
        cout<<"Please enter valid input";
    }
}
void Bank_Holder::changepasswd(string s1,string s2){
    if(s2==s1){
        password=s1;
        cout<<"NEW PASSWORD SET SUCCESSFULLY";
    }
    else{
        cout<<"Passwords don't match";
    }

}
void Bank_Holder::accessAccount(char c,long long int account_no1){
    if(c=='S'||c=='s'){
        for(int i=0;i<accounts_s.size();i++){
            if(accounts_s[i].account_no==account_no1){
                cout<<"ACCESSING ACCOUNT WITH ACCOUNT NO:"<<account_no1<<endl<<endl;
                while(1){
                cout<<"You can perform the following functions:\n1.DEPOSIT MONEY\n2.WITHDRAW MONEY\n3.TRANSFER MONEY\n4.VIEW STATEMENT\n5.CLOSE ACCOUNT\n";
                cout<<"Please choose your operation(1/2/3/4/5/0->to exit):";
                char num;
                cin>>num;
                if(num=='1'){
                    cout<<"Enter the money to deposit:";
                    double amt_usr;
                    cin>>amt_usr;
                    accounts_s[i].deposit(amt_usr);
                }
                else if(num=='2'){
                    cout<<"Enter the money to withdraw:";
                    double amt_usr;
                    cin>>amt_usr;
                    accounts_s[i].withdraw(amt_usr);
                }
                else if(num=='3'){
                    accounts_s[i].transfer(0,0,0);
                }
                else if(num=='4'){
                    cout<<"SHOWING YOUR STATEMENT:\n";
                    accounts_s[i].show_statement();

                }
                else if(num=='5'){
                    cout<<"CLOSING YOUR ACCOUNT!!\n";
                    accounts_s.erase(accounts_s.begin()+i);

                }
                else if(num=='0'){
                    break;
                }
            }
            }
        }
    }
    else if(c=='C'||c=='c'){
         for(int i=0;i<accounts_c.size();i++){
            if(accounts_c[i].account_no==account_no1){
                cout<<"ACCESSING ACCOUNT WITH ACCOUNT NO:"<<account_no1<<endl<<endl;
                while(1){
                    cout<<"You can perform the following functions:\n1.DEPOSIT MONEY\n2.WITHDRAW MONEY\n3.TRANSFER MONEY\n4.VIEW STATEMENT\n5.CLOSE ACCOUNT\n";
                    cout<<"Please choose your operation(1/2/3/4/5/0->to exit):";
                    char num;
                    cin>>num;
                    if(num=='1'){
                        cout<<"Enter the money to deposit:";
                        double amt_usr;
                        cin>>amt_usr;
                        accounts_c[i].deposit(amt_usr);
                    }
                    else if(num=='2'){
                        cout<<"Enter the money to withdraw:";
                        double amt_usr;
                        cin>>amt_usr;
                        accounts_c[i].withdraw(amt_usr);
                    }
                    else if(num=='3'){
                        accounts_c[i].transfer(0,0,0);
                    }
                    else if(num=='4'){
                        cout<<"SHOWING YOUR STATEMENT:\n";
                        accounts_c[i].show_statement();

                    }
                    else if(num=='5'){
                        cout<<"CLOSING YOUR ACCOUNT!!\n";
                        accounts_c.erase(accounts_c.begin()+i);
                    }
                    else if(num=='0'){
                        break;
                    }

                }
            }
        }

    }
}




class BranchManager{
    private:
        string username;
        string password;
    public:
        BranchManager(string s1,string s2);
        void Fast_Fwd();
        void getStatement(long long int account_num);
        void getAccountHolders();
};

BranchManager::BranchManager(string s1,string s2){
    username=s1;
    password=s2;
}

void Fast_Fwd(string &s,string m,string d,string y){
    string cpy=s;
    s=date_change(stoi(m),stoi(d),stoi(y));






}
int main(){
    vector <Bank_Holder> Bank_Holder_list;
    vector <string> username_list;
    string user_bm_rl,user_bm_rl_pw;
    char a;
    cout<<"Hello, Bank Manager"<<endl;
    cout<<"Create your login_id by using new username and password"<<endl;
    cout<<"Create your branch manager username:";
    cin>>user_bm_rl;

    cout<<"Create your brnach manager password:";
    cin>>user_bm_rl_pw;

    BranchManager New(user_bm_rl,user_bm_rl_pw);

    cout<<"To Start the baking session please press E:";
    while(a!='E'){
        cin>>a;
    }
    cout<<"\n\n";

    while(1){
        cout<<"            #      Welcome to Banking Services!!      #"<<endl<<endl;
        cout<<"Do you want to LOGIN or SIGNUP(1/2):";
        char b;
        cin>>b;
        //SIGN UP WITH UNIQUE USERNAMES
        if(b=='2'){
            cout<<"                               SIGN UP "<<endl;
            cout<<"Please Enter your name:";
            string name;
            cin>>name;
            while(1){
                cout<<"Please enter a username:";
                string user_username;
                cin>>user_username;
                if(find(username_list.begin(),username_list.end(),user_username)!=username_list.end()){
                    cout<<"Username already in use."<<endl;
                    cout<<"Please enter new username."<<endl;
                    continue;
                }
                else{
                    username_list.push_back(user_username);
                    cout<<"Username set successfully!!"<<endl;
                    string pass;
                    string pass_chk;
                    while(1){
                        cout<<"Please Enter your password:";
                        cin>>pass;
                        cout<<"Renter your password:";
                        cin>>pass_chk;
                        if(pass==pass_chk){
                            cout<<"Password set successfully!!"<<endl;
                            break;
                        }
                        else{
                            cout<<"Passwords donot match, please renter them."<<endl;
                            continue;
                        }

                    }
                    //CREATING OBJECT OF USER AND STORING IT IN VECTOR
                    Bank_Holder Usr(name,user_username,pass);
                    Bank_Holder_list.push_back(Usr);
                    cout<<"You have successfully registered,\nPlease LOGIN to view your account\'s status."<<endl;
                    break;
                }
            }
        }
        
        //LOGIN 
        if(b=='1'){
            cout<<"                               LOGIN"<<endl;
            string login_usr,login_pw;
            cout<<"Enter your USERNAME:";
            cin>>login_usr;
            cout<<"Enter your PASSWORD:";
            cin>>login_pw;
            pair <string,string> a;
            for(int i=0;i<Bank_Holder_list.size();i++){
                if(Bank_Holder_list[i].checkAccess(login_usr,login_pw)){
                    int choice=50;
                    cout<<"SUCCESSFULLY LOGGED IN"<<endl;
                    while(choice!=0){    
                        cout<<"WHICH OPERATION DO YOU WANT TO PERFORM:\n1.Show all your accounts.\n2.Change password\n3.Create a new Account.\n4.Access Account by Account num.\n";
                        cout<<"Please choose any operation (1/2/3/4/0-TO EXIT)";
                        cin>>choice;

                        //LIST ALL ACCOUNTS
                        if(choice==1){
                           
                            Bank_Holder_list[i].get_Accounts();
                        }
                        //CHANGE PASSWORD
                        else if(choice==2){
                            string s1,s2;
                            cout<<"Please enter NEW PASSWORD:";
                            cin>>s1;
                            cout<<"Please re-enter NEW PASSWORD:";
                            cin>>s2;
                            Bank_Holder_list[i].changepasswd(s1,s2);
                        }
                        //CREATE NEW ACCOUNT
                        else if(choice==3){
                            cout<<"TYPES OF ACCOUNTS:\n1.SAVINGS(S)\n2.CURRENT(C)"<<endl;
                            cout<<"Choose type(S/C):";
                            char c;
                            cin>>c;
                            if(c=='S'||c=='s'){
                                cout<<"ENTER OPENING BALANCE AND DEPOSIT IT:"<<endl;
                                long long int amt;
                                while(1){
                                    cin>>amt;
                                    if(amt<=0){
                                        cout<<"Please enter non zero balance";
                                    }
                                    else{
                                        break;
                                    }
                                }
                                Bank_Holder_list[i].createAccount(c,amt);
                            }
                            else if(c=='c'||c=='C'){
                                cout<<"ENTER OPENING BALANCE AND DEPOSIT IT:"<<endl;
                                long long int amt;
                                while(1){
                                    cin>>amt;
                                    if(amt<=0){
                                        cout<<"Please enter non zero balance";
                                    }
                                    else{
                                        break;
                                    }
                                }
                                Bank_Holder_list[i].createAccount(c,amt);
                            }
                        }
                        //ACCESS A SPECIFIC ACCOUNT
                        else if(choice==4){
                            char u;
                            cout<<"Please Enter your account type(S/C):";
                            cin>>u;
                            long long int account_num;
                            cout<<"Please type your account number:";
                            cin>>account_num;
                            
                            
                            Bank_Holder_list[i].accessAccount(u,account_num);

                        }
                    
                    
                    }

                    break;
                }
                else{
                    cout<<"WRONG USERNAME OR PASSWORD"<<endl;
                    break;
                }
            }
            
            
        }
    
    
    
    }

    return 0;
}