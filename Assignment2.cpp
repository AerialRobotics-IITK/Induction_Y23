#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

int accno=1;

class date{
    public:
        int day;
        int month;
        int year;

        date(int d,int m,int y){
            day=d;
            month=m;
            year=y;
        }
        void addmonths(int n){
            int newmonth=(month+n)/12;
            int newyear=
            if (newmonth==0) newmonth=12;
            month=newmonth;
            

        }
};

date curr(11,5,2024);

class Branch_Manager{
    private:
        std::string Username;
        std::string Password;
    public:
        int branchno;
        Branch_Manager(int n,string usr,string pswd){
            branchno=n;
            Username=usr;
            Password=pswd;
        }
        pair<string,float> getStatementofAccount(int){

        }
        void fastforward(int monthstoadd){
            curr.addmonths(monthstoadd);
        }
        int check(int n,string usr,string pswd){
            if (n==branchno && usr==Username && pswd==Password){
                return 1;
            }
            else{
                return 0;
            }
        }
};

Branch_Manager M1(1,"A","abc");
Branch_Manager M2(2,"B","def");
Branch_Manager M3(3,"C","ghi");
Branch_Manager M4(4,"d","jkl");
Branch_Manager arr[]={M1,M2,M3,M4};

class Bank_Account{
    public:
        int AccountNo=accno;
        float Balance=1000;
        date OpenDate=curr;
        vector<pair<string,float>> Transaction_History;

        void deposit(){
            float amount;
            cout << "\nEnter amount to deposit: ";
            cin >> amount;
            this->Balance+=amount;
            Transaction_History.push_back(make_pair("Deposit",amount));
        }
        void withdraw(){
            float amount;
            cout << "\nEnter amount to withdraw: ";
            cin >> amount;
            if (amount<=this->Balance){
                this->Balance-=amount;
                Transaction_History.push_back(make_pair("Withdraw",-amount));
            }
            else {cout << "\nAmount exceeds balance";}
        }
        ~Bank_Account();
};

class Bank_Account_Holder{
    public:
        int AccountNo;
        string Username;
        map <int,pair<string,Bank_Account>> accounts;
        void createAccount(){

        }
        
    private:
        string Password;
        void changePassword(){
            string newpswd;
            cout << "\nEnter new password: ";
            cin >> newpswd;
            this -> Password=newpswd;
        }
    
    public:
        Bank_Account_Holder(int n,string usr,string pswd){
            AccountNo=n;
            Username=usr;
            Password=pswd;
        }
        pair <string,string> get(){
            return make_pair(Username,Password);
        }
};

vector <Bank_Account_Holder> list;

const int limit=50;

class Savings_Account: public Bank_Account{
    public:
        static int NoofTransactions;
        float InterestRate=5;
        void getInterestRate(){
            printf("%f",this->InterestRate);
        }
        void setInterestRate(){
            float rate;
            if (rate>6) printf("\nInterest capped at 6%");
            else this->InterestRate=rate;
        }
};

class Current_Account: public Bank_Account{
    private:
        float rate=0;
    public:
        void getInterestRate(){
            printf("Interest rate is %f",rate);
        }
};


string usernames[]={};
int j=0;
int checkUsername(string usr){
    for (int i=0;i<=j;i++){
        if (usr==usernames[i]) return 0;
    }
    usernames[j++]=usr;
}


int main(){
    cout << "\nEnter 1 for manager login and 2 for client login: ";
    int opt;
    cin >> opt;
    if (opt==1){
        cout << "\nEnter branch number follwed by credentials for Bank Manager sign-in (Username,Password): ";
        int bno;
        string mun,mpswd;
        cin >> bno >> mun >> mpswd;
        int flag=0,i=0;
        for (;i<4;i++){
            if (arr[i].check(bno,mun,mpswd)){
                flag=1;
                break;
            }
            if (flag==1){
                cout << "\nLogin successful";
            }
            else{
                cout << "\nLogin failed";
            }
        }
        int choice;
        while (1){
            cout << "\nEnter 1 to fast forward and 0 to exit";
            cin >> choice;
            if (choice==0) break;
            else{
                int days;
                scanf("\nEnter number of days to fast-forward: %d",&days);
                Branch_Manager M=arr[i];
                M.fastforward(days);
            }

        }   
    }
    else{
        cout << "\nEnter 1 for Login and 2 if you wish to sign-up: ";
        int opt;
        string usr,pswd;
        if (opt==1){
            cout << "\nEnter username and password: ";
            cin >> usr >> pswd;
            int flag=0;
            int k=0;
            for (;k<list.size();k++){
                if (make_pair(usr,pswd)==list[k].get()) {
                    flag=1;
                    break;
                }
            }
            if (flag==0){
                cout << "\nInvalid Username or Password";
            }
            Bank_Account_Holder B=list[k];
        }
        else{
            while (1){
                cout << "\nEnter username: ";
                cin >> usr;
                if (checkUsername(usr)==0){
                    cout << "\nThat username is not available";
                }
                else{
                    cout << "\nEnter password: ";
                    cin >> pswd;
                }
            }
            Bank_Account_Holder B=Bank_Account_Holder(j,usr,pswd);
            list.push_back(B);
        }
        int k=0;
        for (;k<list.size();k++){
                if (make_pair(usr,pswd)==list[k].get()) {
                    break;
                }
        }
        Bank_Account_Holder B=list[k];
        while(1){
            cout << "\nOptions are: \n1. Open Savings Account(Minimum Balance 1000)\n2.open Current Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6.Get Statements\n7.Close account\n8. Exit\nEnter option number: ";
            int op;
            cin >> op;
            if (op==1){
                Savings_Account Acc;
                B.accounts[accno++]=make_pair("Savings_Account",Acc);
            }
            else if(op==2){
                Current_Account Acc;
                B.accounts[accno++]=make_pair("Current_Account",Acc);
            }
            else if(op==3){
                int n;
                scanf("\nEnter account number: %d",&n);
                if (B.accounts[n].first=="Savings_Account" && B.accounts[n].second.NoofTransactions==limit){
                    cout << "You have reached transaction limit";
                }
                B.accounts[n].second.deposit();
            }
            else if(op==4){
                int n;
                scanf("\nEnter account number: %d",&n);
                B.accounts[n].second.withdraw();
            }
            else if(op==5){
                int n1,n2;
                scanf("\nEnter account numbers to transfer from and to: %d",&n1,&n2);
                B.accounts[n1].second.withdraw();
                B.accounts[n2].second.deposit();
            }
            else if (op==6){
                for (auto it = B.accounts.begin(); it != B.accounts.end(); ++it) {

            }
            else if (op==7){
                int n;
                scanf("\nEnter account number: %d",&n);

            }
            else if (op==8){
                break;
            }

    }
        
    return 0;
}