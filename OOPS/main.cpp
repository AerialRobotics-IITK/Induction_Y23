#include<bits/stdc++.h>
using namespace std;


class BranchManager
{
public:
    string username = "chandra3";
    string password = "chandraISbest@123";

    void getStatementOfAccount(int accNum);
    void getAccountHolders();
    void fastforward();
};

int main(){
    cout << "Hello! Welcome to the Babu Bank of India (BBI)\n";
    cout << "Please select what you would like to do today\n";
    cout << "1. Login as Account-Holder\n";
    cout << "2. Don't have an account? Sign up here\n";
    cout << "3. Forgot your password. Reset here\n";
    cout << "4. Login as Bank-Manager\n";
    int ch;
    cin >> ch;
    string secpass, chpass1, chpass2, manusern, manpass;
    int chman;
    switch (ch)
    {
    case 1:
        cout << "Enter your username\n";
        cout << "Enter your password\n";
        //login process... verify if acc exists and login
        BankAccountHolder::getAccounts();
        break;
    
    case 2:
        cout << "Create a new account\n";
        cout << "Enter a valid username. Only letters numbers and underscores are allowed\n";
        BankAccountHolder::createAccount();
        cout << "Set your password\n";
        cin >> chpass1;
        cout << "Re-enter your password\n";
        cin >> chpass2;
        if(chpass1 == chpass2){
            BankAccountHolder::createPassword();
        }
        //add acc to list
        cout << "Success! Your account has been created. Please exit and login again to enter your account" << endl;
        break;

    case 3: 
        cout << "Enter your username" << endl;
        cout << "Please enter the numbers seen on the screen. 5g9hb833" << endl;
        cin >> secpass ;
        if (secpass == "5g9hb833") {
            // add lines from case 2
        }


    case 4:
        BranchManager man;
        cout << "Enter your manager username\n";
        cin >> manusern;
        if(man.username == manusern){
            cout << "Enter your password\n";
            cin >> manpass;
            if(man.password == manpass){
                cout << "Success! YOu have logged in as Branch Manager." << endl ;
                cout << "What would you like to do today?\n";
                cout << "1. Get statement of accounts\n";
                cout << "2. Get account holders\n";
                cout << "3. Fast Forward\n";
                cin >> chman;

            }
            else {
                cout << "Password did not match. Please try again." << endl ;
            }
        }
        else {
            cout << "No such user found. Try again." << endl ;
        }
        break;
    
    default:
        cout << "No such option found. Please try again." << endl;
        break;
    }

    return 0;
};
