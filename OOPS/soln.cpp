#include <iostream>
#include <vector>
using namespace std;
void ahlogin();
void ahsignup();
void bmlogin();
void changepassword();
void Accmenu();
void bmmenu();
string bmusername = "Popat";
string bmpwd="Popat123";
class accholder{
    public:
    string name;
    string username;
    string password;
    vector<int> acclist;
    void getAccounts();
    // void changePasswd();
    // void createAccount();
};
accholder A[100];
int nUser=0;
class acc{
    public:
    string AccNo;
    int Balance=0;
    string Opendate;
    void deposit(int deposit){Balance=Balance+deposit;};
    void withdraw(int withdraw){Balance=Balance-withdraw;};
    void transfer();
};
acc B[100];
int nAcc;
class savingsacc:public acc{
private:
    int interestrate;
    
public:
    int transferlim=40000;
    int getir(){return interestrate;};
    void setir(){
        if(Balance<=500000){interestrate = 4;}
        else if((Balance>500000)&&(Balance<=500000)){interestrate=7;}
        else if((Balance>500000)&&(Balance<=500000)){interestrate=7;}
        else if((Balance>1000000)&&(Balance<=50000000)){interestrate=5;}
        else if((Balance>50000000)&&(Balance<=500000000)){interestrate=4.5;}
        else if(Balance>500000000){interestrate=7;}
    }
};
class currentacc:public acc{
private:
    int interestrate;
    
public:
    int transferlim=5000000000;
    int getir(){ return 0;};
};
void startmenu(){
    cout<< "Hello! Welcome to SBI(Shrey's Bank of India)"<<'\n'<<"Please choose your method of Entry"<<'\n'<<"1. Account Holder Signup\n2.Account Holder Login\n3.Bank Manager Login"<<endl;
    int i;
    cin>>i;
    if(i==1){ahsignup();}
    else if(i==2){ahlogin();}
    else if(i==3){bmlogin();}
    else{cout<<"Invalid Option selected"<<endl;}
}
void ahsignup(){
    string Name,Username, pwd;
    cout<<"Please enter your Name"<<endl;
    cin>>Name;
    A[nUser].name=Name;
    while(1)
    {
        int valid=1;
        cout<<"Please enter a username"<<endl;
        cin>>Username;
        for (int i=0;i<nUser;i++){
            if(Username==A[i].username){valid=0;}
        }
        if(valid==1){
            A[nUser].username=Username;
            break;
        }
        else
        {
            cout<<"Username is not unique, Please try some other username";
        }
        
    }
    cout<<"Create a password"<<endl;
    cin>>pwd;
    A[nUser].password=pwd;
    
    nUser=nUser+1;
    ahlogin();
}
void ahlogin(){
    string Username, Password;
    int UserNo;
    while(1){
        int valid=0;
        cout<<"Enter Your Username"<<endl;
        cin>>Username;
        for(int i=0;i<nUser;i++){
            if(Username==A[i].username){UserNo=i; valid=1; break;}
        }
        if(valid=1){break;}
        cout<<"You have entered an incorrect Username"<<endl;
    }
    while(1){
        cout<<"Enter Your Password"<<endl;
        cin>>Password;
        if(Password==A[UserNo].password){ahmenu(UserNo);break;}
        cout<<"Incorrect Password"<<'\n';
    }
}
void bmlogin(){
    string Username, Password;
    while(1){
        cout<<"Enter Your Username"<<endl;
        cin>>Username;
            if(Username==bmusername){ break;}
        cout<<"You have entered an incorrect Username";
    }
    while(1){
        cout<<"Enter Your Password"<<endl;
        cin>>Password;
        if(Password==bmpwd){bmmenu();break;}
        cout<<"Incorrect Password"<<endl;
    }
}

void ahmenu(int un)
{
    while(1){
        cout<<"Greetings! Choose what you want to do from the following options"<<'\n'<<"1. Create New Account"<<'\n';
        cout<<"2. List Accounts"<<'\n'<<"3. Change Password"<<'\n';
        int i;
        cin>>i;
        switch(i){
            case(1):createacc(un); break;
            case(2):listacc(un); break;
            case(3):changepassword(un); break;
            default:cout<<"Invalid input"<<'\n'; break;
        }
        break;
    }
}
void changepassword(int un){
    string newpass, Password;
    while(1){
        cout<<"Enter Your Previous Password"<<'\n';
        cin>>Password;
        if(Password==A[un].password){
           cout<<"Enter Your New Password"<<'\n';
           cin>>newpass;
           A[un].password=newpass;
           break;
        }
        else{cout<<"Incorrect Password"<<endl;}
    }
    ahmenu(un);
}
void createacc(int un){
    int i;
    while(1){
        cout<<"Would you like your account to be a:"<<endl<<"1. Savings Account"<<endl<<"2. Current Account"<<endl;
        cin>>i;
        if(i==1)
        {
            int dep;
            savingsacc s;
            while(1){
                cout<<"Please deposit atleast 1000"<<endl<<"Enter amount to deposit"<<endl;
                cin>>dep;
                if(dep>=1000){
                    B[nAcc]=s;
                    B[nAcc].deposit(dep);
                    B[nAcc].AccNo=nAcc;
                    A[un].acclist.push_back(nAcc);//account number added to the account list vector of the user
                    cout<<"Account Succesfully created";
                    nAcc=nAcc+1;
                    break;
                }
                else{cout<<"Deposit below minimum"<<endl;}
            }
            break;

        } else if(i==2)
        {
            int dep;
            currentacc s;
            while(1){
                cout<<"Please deposit atleast 1000"<<endl<<"Enter amount to deposit"<<endl;
                cin>>dep;
                if(dep>=1000){
                    B[nAcc]=s;
                    B[nAcc].deposit(dep);
                    B[nAcc].AccNo=nAcc;
                    A[un].acclist.push_back(nAcc);//account number added to the account list vector of the user
                    cout<<"Account Succesfully created";
                    nAcc=nAcc+1;
                    break;
                }
                else{cout<<"Deposit below minimum"<<endl;}
            }
            break;

        }
        else{cout<<"invalid option"<<endl;}
    }
    

}
void listacc(int un){
    cout<<"Your Account List is as follows"<<endl;
    int j=1;
    for(auto i=A[un].acclist.begin();i!=A[un].acclist.end();i++)
    {
        cout<<"Account "<<j << " Account No."<< *i<<endl;
        j++;
    }
    cout<<"Choose Your Account using Account No."<<endl;
    int AccNo;
    cin>>AccNo;
    Accmenu(un,AccNo);
}
void Accmenu(int un, int an)
{
    while(1){
        cout<<"Greetings! Choose what you want to do from the following options"<<'\n'<<"1.Check Account balance"<<endl;
        cout<<"2. Deposit Money"<<'\n';
        cout<<"3. Withdraw Money"<<'\n'<<"4. Transfer Money"<<'\n'<<"5. Close Account";
        int i;
        cin>>i;
        switch(i){
            case(1):cout<< "Your Balance is" <<B[an].Balance<<endl; break;
            case(2):
            int dep;
            cout<<"Enter Deposit Amount"<<endl;
            cin>>dep;
            B[an].deposit(dep);
            break;
            case(3): 
            int dep;
            cout<<"Enter Withdraw Amount"<<endl;
            cin>>dep;
            B[an].withdraw(dep);break;
            case(4):
                int tan,amt;
                cout<<"Enter Target Account No."<<endl;
                cin>>tan;
                    cout<<"Enter Amount"<<endl;
                cin>>amt;
                B[an].withdraw(amt);
                B[tan].deposit(amt);
                
                break;
            case(5):
                A[un].acclist.erase(an);
            default:cout<<"Invalid input"<<'\n'; break;
        }
        break;
    }
}
void bmmenu(){
    while(1){
            cout<<"Greetings! Choose what you want to do from the following options"<<'\n'<<"1. Get Balance of Account"<<'\n';
            cout<<"2. List Accounts"<<'\n'<<"3. Check Fastforward"<<'\n';
            int i;
            cin>>i;
            switch(i){
                case(1):
                    int an;
                    cout<<"Enter Account Number"<<endl;
                    cin>>an;
                    cout<<"The Account Balance is "<<B[an].Balance<<endl; 
                    break;
                case(2):
                    cout<<"The list of Account Holder is as follows"<<endl;
                    for(int i=0;i<nUser;i++){
                        cout<<"Name "<<A[i].name<<endl;
                        listacc(i);
                    }
                     break;
                case(3):
                    cout<<"Specify the amount of months you would like to fastforward"; 
                    int time;
                    cin>> time;
                        for(int i=0;i<nAcc;i++){
                        
                    }
                    break;
                default: cout<<"Invalid Input"; break;
            }
            break;
        }
}
int main(){
    startmenu();
    return 0;
}