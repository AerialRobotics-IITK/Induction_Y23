#include<bits/stdc++.h>
using namespace std;

class BankAccountHolder
{
private:
    /* data */
public:
    string name;
    string username;
    string password;
    //list of bank accounts

    string getAccounts();
    string changePassword();
    void createPassword();
    void createAccount();
};

class BankAccount
{
public:
    int accNo;
    int balance;
    //opendate
    //bank statement

    void deposit();
    void withdraw();
    void transfer();
};

class SavingsAccount : public BankAccount
{
private:
    float interestRate;
public:
    float getRate(){
        return interestRate;
    };
    void setRate(float newRate){
        interestRate = newRate;
        cout << "Updated interest rate is " << interestRate << endl;
    };
};

class CurrentAccount : public BankAccount
{
    int interestRate = 0;
    int getRate(){
        //try catch bs
    };
};


// string BankAccountHolder::getAccounts()
// {

// }

// string BankAccountHolder::changePassword()
// {

// }


int main()
{
    BankAccountHolder obj1;
    obj1.changePassword();
    return 0;

};
