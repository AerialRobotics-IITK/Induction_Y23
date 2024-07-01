#include <bits/stdc++.h>
using namespace std;

class Holder
{
    friend class BankAccount;
private:
    string name;
    string username;
    string password;


public:

   Holder(string name, string username, string password){
 		this->name = name;
 		this->username = username;
 		this->password = password;
 	}
    void signup(void)
    {
        cout << "Enter your name: ";
        string name;
        cin>>name;

        cout << "Enter your username: ";
        string username;
        cin>>username;
        cout << "Enter your password: ";
         string password;
        cin>>password;

    }
    
    void changepassword(void)
    {
        do
        {
            string initial_pass;
            cout << "Enter your initial password";
            cin>>initial_pass;
            
                cout << "Enter your new password";
                cin>>password;
                cout << "Password updated successfully";
               break;
            } while (1);
        
    }
    
    // void createAccount()
    // {
    //     int  c = rand() ;
    //     user_account.accountnumber = c;
    //     cout << "Minimimum fee to create a account=Rs.100\nEnter the money you want to deposit";
       
    //     double balance;
    //     cin >> balance;
    //     do
    //     {
    //         if (balance > 100)
    //         {
    //             user_account.Balance = balance;
    //             break;
    //         }
    //         else
    //         {
    //             cout << "Your balance is less than 100";
    //         }
    //     } while (1);
    //     cout<<"Your account is created successfully";
        
        
    // }
    string getUsername(void){
        return username;
    }
    string getPassword(void){
        return password;
    }
    friend class BankManager;
};


class BankAccount
{
    friend class Holder;
    private:
     int accountnumber;
    double Balance;
    // vector<string> transaction;
    // vector<string>& temp = transaction;
    string openingdate;

public:

  BankAccount(int accountnumber, int Balance, string openingdate){
		this->accountnumber = accountnumber;
		this->Balance = Balance;
		this->openingdate = openingdate;

	}
	
    void deposit(double amount)
    {
        cout << "Enter the amount you want you to deposit";
        cin >> amount;
        Balance += amount;
        
    }
    void withdraw(double amount)
    {
        cout << "Enter the amount you want to withdraw";
        cin >> amount;
        do
        {
            if ((Balance - amount) >= 100)
            {
                Balance -= amount;
              
                break;
            }
            else
            {
                cout << "Withdrawing this amount leaves lesser money than the minimum limit";
                
            }
        } while (1);
    }
    
    int getaccountnum(void){
        return accountnumber;
    }
    float getbalance(void){
        return Balance;
    }
    double *ret_balance()
    {
        return &Balance;
    }
  
    friend class BankManager;
};

vector<Holder> Listofholders ;
vector<BankAccount> listofaccounts;





int main(){
    int flag=0;
	while(!flag){
	
	cout<<"                JP Morgan Banking System"<<endl;
	cout<<"1. Login"<<endl;
	cout<<"2. Sign Up"<<endl;
	cout<<"Kindly enter which option u want to choose ( 1 or 2):";
	int value;
	cin>>value;

	if(value==1){
	    flag=1;
	    cout<<"Enter your name:";
	    string name;
	    cin>>name;
	    cout<<"Enter your username:";
	    string username;
	    cin>>username;
	    cout<<"Enter your password:";
	    string pass;
	    cin>>pass;
	    printf("\n");
	    Holder h1 = Holder(name,username,pass);
	    
	    cout<<"Enter W to withdraw, D to Deposit or L to Logout";
	    char ch;
	    cin>>ch;
	    if(ch=='W'){
	    	int amt;
	    	




	        
	        
	        
	        
	    }
}}}