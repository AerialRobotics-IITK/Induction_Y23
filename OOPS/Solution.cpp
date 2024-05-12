#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
typedef struct date
{
    int Day;
    int Month;
    int Year;
} Date;
Date GlobalDate = {1, 1, 2024};
typedef struct Accounts
{
    int AccountNo;
    int type;
} Accounts;

enum TransactionType
{
    Deposit,
    Withdraw,
    Transfer
};
const float maxBalance = 5000000;
typedef struct statement
{
    Date date;
    TransactionType Type;
    float Amount;
} Statement;

// Making a set that stores unique usernames and passwords, so that no two account holders have the same username.
set<string> Usernames;

class SavingAccount
{
    float InterestRate;

public:
    float getInterestRate(void)
    {
        return InterestRate;
    }

public:
    void setInterestRate(float newRate)
    {
        if (newRate < 0)
        {
            printf("Cannot have interest rate less than 0%%, it's your loss.\n");
            return;
        }
        if (newRate <= 6.0)
        {
            InterestRate = newRate;
            printf("Updated Interest Rate\n");
            return;
        }
        printf("Sneaky Sneaky!! Interest rate cannot be greater than 6%%\n");
    }
};

class CheckingAccount
{
public:
    float getInterestRate(void)
    {
        throw std::invalid_argument("There is no Interest Rate for current Account");
    }
};

class BankAccount : public SavingAccount, public CheckingAccount
{
private:
    friend class BranchManager;
    friend class AccountHolder;
    static int AccountNo;

protected:
    int MyAccountNo;
    float Balance;
    Date OpeningDate = GlobalDate;
    int AccountType;

    vector<Statement> statements;

public:
    float CurrentBalance(void)
    {
        return Balance;
    }
    int ReturnAccountNo(void)
    {
        return MyAccountNo;
    }
    BankAccount(void)
    {
        AccountNo++;
        MyAccountNo = AccountNo;
        cout << "What type of Account? \n(1)Savings\n(2)Current\nChoose option: ";
        cin >> AccountType;
        while (Balance < 1000 || Balance>maxBalance)
        {

            cout << "Enter the amount you want to initially add(min 1000 Rs): ";
            cin >> Balance;

            if (Balance<1000){
                cout << "Sorry, Not Possible , please add more balance\n";
            }
            else if (Balance >= 1000 || Balance<=maxBalance)
            {
                if (AccountType == 1)
                {
                    float rate;
                    // cout << "What should be your interest rate?";
                    // cin >> rate;
                    if (Balance<50000){
                        rate = 3;
                    }
                    else if(Balance<500000){
                        rate = 5;
                    } 
                    else if (Balance<maxBalance){
                        rate = 6;
                    }
                    SavingAccount::setInterestRate(rate);}
                }
            else {
                cout<<"Exceeded Maximum possible Balance (Rs"<<maxBalance<<"), please store less!!\n";
            }
            }

        }
    float interestRate(void)
    {
        if (AccountType == 1)
        {
            return SavingAccount::getInterestRate();
        }
        return 0;
    }
    void getInterestRate(void)
    {
        if (AccountType == 1)
        {
            printf("Interest Rate : %f", SavingAccount::getInterestRate());
        }
        else
        {
            try
            {
                printf("Interest Rate : %f", CheckingAccount::getInterestRate());
                /* code */
            }
            catch (const std::exception &e)
            {
                cout << "Sorry , no interest rate in case of current account\n";
            }
        }
        return;
    }
    void deposit(float amount)
    {
        if (Balance+amount>maxBalance){
            cout<<"Cannot store more than Rs"<<maxBalance<<"in one account, amount not deposited\nTransaction Failed\n";
            return;
        }
        statements.push_back({GlobalDate, Deposit, amount});

        Balance += amount;
    }
    void withdraw(float amount)
    {
        if (Balance-amount<1000){
            cout<<"Cannot store less than Rs"<<1000<<"in one account, amount not withdrawn\nTransaction Failed\n";
            return;
        }
        statements.push_back({GlobalDate, Withdraw, amount});
        Balance -= amount;
    }
    void transfer(float amount)
    {
        if (Balance-amount<1000){
            cout<<"Cannot store less than Rs"<<1000<<"in one account, amount not transferred\nTransaction Failed\n";
            return;
        }
        statements.push_back({GlobalDate, Transfer, amount});
        Balance += amount;
    }
};

vector<BankAccount> AllAccounts;
class AccountHolder
{
private:
    friend AccountHolder *Login(string);
    friend class BranchManager;
    string Name, passwd;
    vector<int> AccountNos;

public:
    string UserName;
    AccountHolder(const AccountHolder &other)
    {
        this->Name = other.Name;
        this->passwd = other.passwd;
        this->UserName = other.UserName;
    }
    AccountHolder(void){};
    AccountHolder(int num)
    {
        cout << "Enter your name: ";
        cin >> this->Name;

        cout << "Enter a username for you: ";
        cin >> this->UserName;
        while (Usernames.find(UserName) != Usernames.end())
        {
            cout << "Username already taken, try another one: ";
            cin >> this->UserName;
        }
        Usernames.insert(UserName);
        cout << "Set a secure Password: ";
        cin >> this->passwd;
    }
    void changePasswd(void)
    {
        cout << "Enter the new password: ";
        cin >> this->passwd;
        cout << "Password change successful!!" << endl;
    }
    void CreateAccount()
    {

        AllAccounts.emplace_back();
        AccountNos.emplace_back(AllAccounts.back().MyAccountNo);
    }
    vector<int> getAccounts(void)
    {
        return AccountNos;
    }
    void ListAccount(void)
    {
        vector<int> Accounts = this->getAccounts();
        printf("Following are the accounts owned by \n");
        cout << Name << endl;
        for (int x = 0; x < Accounts.size(); x++)
        {
            printf("%d \n", Accounts[x]);
        }
    }
    int RemoveAccount(int ACno)
    {
        AccountNos.erase(AccountNos.begin() + ACno);
    }
};

map<string, AccountHolder> Holders;
AccountHolder *Login(string username)
{
    map<string, AccountHolder>::iterator iter;
    int FoundUsrName = 0;
    // map<string,AccountHolder> Holder(Holders);
    for (iter = Holders.begin(); iter != Holders.end(); iter++)
    {
        if ((*iter).first == username)
        {
            string password;
            cout << "Enter your supper secret password: ";
            cin >> password;
            if ((*iter).second.passwd == password)
            {
                cout << "Login successful!!\n";
                AccountHolder *ptr = &((*iter).second);
                return ptr;
            }
            cout << "Wrong Password!" << endl;
            return NULL;
        }
    }
    cout << "User not found";
    return NULL;
};
class BranchManager;
// int LoginManger(string, BranchManager *);

int BankAccount::AccountNo = 0;
class BranchManager
{
    string Username;
    string Password;
    friend int LoginManager(string Username, BranchManager *ptr);

public:
    BranchManager(void)
    {
        cout << "Initializing Bank Manager's Account\n";
        sleep(0.5);
        cout << "Enter UserName: ";
        cin >> Username;
        while (Usernames.find(Username) != Usernames.end())
        {
            cout << "Username already taken, try another one: ";
            cin >> Username;
        }
        Usernames.insert(Username);
        cout << "Enter Password: ";
        cin >> Password;
    }
    void getStatementOfAccount(int AccountNo)
    {
        AccountNo--;
        // Considering all the accounts that I have made are stored in vector and accessing the accountNo via the AccountNo provided, to get statements.
        // return AllAccounts[AccountNo].statements;
        int size = AllAccounts[AccountNo].statements.size();
        for (int x = 0; x < size; x++)
        {
            cout << "Transaction id: " << x
                 << ", Date: " << AllAccounts[AccountNo].statements[x].date.Day << "/" << AllAccounts[AccountNo].statements[x].date.Month << "/" << AllAccounts[AccountNo].statements[x].date.Year
                 << ", Amount = " << AllAccounts[AccountNo].statements[x].Amount
                 << ", Type = " << AllAccounts[AccountNo].statements[x].Type << endl;
        }
    }
    void fastforward(void)
    {
        int days, months;
        cout << "Enter No of days to fast forward(Considering 30 days in a month):";
        cin >> days;
        cout << "Enter No of months to fast forward:";
        cin >> months;
        months += (days + GlobalDate.Day) / 30;
        GlobalDate.Day = (days + GlobalDate.Day) % 30 + 1;
        GlobalDate.Month += months;
        int size = AllAccounts.size();
        for (int x = 0; x < size; x++)
        {
            if (AllAccounts[x].AccountType == 1)
            {
                AllAccounts[x].Balance = AllAccounts[x].Balance * (1 + AllAccounts[x].interestRate() / 100 / 12 * months);
            }
        }
    }
    void getAccountHolders(void)
    {
        int size = Usernames.size();
        for (auto it = Usernames.begin(); it != Usernames.end(); ++it)
        {
            // std::cout << *it << " ";
            cout << "Name of Holder: " << Holders[*it].Name;
            Holders[*it].ListAccount();
        }
    }
};
int LoginManager(string Username, BranchManager *ptr)
{
    string Password;
    if (Username == ptr->Username)
    {
        cout << "Enter Password: ";
        cin >> Password;

        if (Password == ptr->Password)
        {
            printf("Logging you in , Boss!\n");
            return 1;
        }
        printf("Wrong Password\n");
        return 0;
    }
    printf("Wrong Username\n");
    return 0;
}

int main()
{

    int userType;
    int Action = 0; // For account holder to login or signup
    string userName;
    AccountHolder *Current = NULL;
    BranchManager *TheOneAndOnly = NULL;
    BranchManager *IfLogin = NULL;
    int OutcomeOfLogin;
    while (userType != 3)
    {
        cout << "Knock Knock , who's there?" << endl;
        cout << "(1) Account Holder" << endl;
        cout << "(2) Branch Manager" << endl;
        cout << "(3) Exit" << endl
             << "Select (1/2/3): ";
        cin >> userType;
        // cout<<userType;
        if (userType == 1)
        {
            while (Action != 3)
            {
                printf("(1)SignUp\n(2)Login\n(3)Exit\nChoose Option: ");
                cin >> Action;
                if (Action == 2)
                {
                    printf("Logging you in ...\nEnter your User-name:");
                    cin >> userName;
                    Current = Login(userName);
                    int Service = 0;
                    cout << "reached here\n";
                    if (Current != NULL)
                    {
                        while (Service != 6)
                        {
                            cout << "Following are the services you can avail:\n(1)Print list of accounts\n(2)Change Password\n(3)Create Account\n(4)Access a account\n(5)Remove Account\n(6)Exit\n";
                            cin >> Service;
                            if (Service == 1)
                            {
                                Current->ListAccount();
                            }
                            else if (Service == 2)
                            {
                                Current->changePasswd();
                            }
                            else if (Service == 3)
                            {
                                Current->CreateAccount();
                            }
                            else if (Service == 4 || Service == 5)
                            {
                                int AccountNo;
                                cout << "Enter Account Number\n";
                                cin >> AccountNo;
                                // Have to write code to check if the account belongs to holder ,
                                int size = Current->getAccounts().size();
                                for (int y = 0; y < size; y++)
                                {
                                    if (Current->getAccounts()[y] == AccountNo)
                                    {
                                        size = AllAccounts.size();
                                        for (int x = 0; x < size; x++)
                                        {
                                            if (AllAccounts[x].ReturnAccountNo() == AccountNo)
                                            {
                                                if (Service == 4)
                                                {
                                                    int InfoAccount = 0;
                                                    float amount;
                                                    while (InfoAccount != 6)
                                                    {
                                                        cout << "Can do following actions with your account:\n(1)Deposit\n(2)Withdraw\n(3)Transfer\n(4)Get Interest Rate\n(5)Check Balance\n(6)Exit\n";
                                                        cin >> InfoAccount;
                                                        if (InfoAccount == 1)
                                                        {
                                                            cout << "Enter amount to deposit: ";
                                                            cin >> amount;
                                                            AllAccounts[x].deposit(amount);
                                                        }
                                                        else if (InfoAccount == 2)
                                                        {
                                                            cout << "Enter amount to withdraw: ";
                                                            cin >> amount;
                                                            AllAccounts[x].withdraw(amount);
                                                        }
                                                        else if (InfoAccount == 3)
                                                        {
                                                            cout << "Enter amount to Transfer: ";
                                                            cin >> amount;
                                                            AllAccounts[x].transfer(amount);
                                                        }
                                                        else if (InfoAccount == 4)
                                                        {
                                                            AllAccounts[x].getInterestRate();
                                                        }
                                                        else if (InfoAccount == 5)
                                                        {
                                                            cout << "Current Balance: " << AllAccounts[x].CurrentBalance();
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    Current->RemoveAccount(y);
                                                    AllAccounts.erase(AllAccounts.begin() + x);
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else if (Action == 1)
                {
                    // printf("inside:\n");
                    AccountHolder temp(1);
                    Holders[temp.UserName] = temp;
                }
                else if (Action == 3)
                {
                    break;
                }
            }
        }
        else if (userType == 2)
        {
            if (TheOneAndOnly == NULL)
            {
                BranchManager temp;
                TheOneAndOnly = &temp;
            }
            else
            {
                cout << "Logging you in...\nEnter UserName";
                cin >> userName;
                if (LoginManager(userName, TheOneAndOnly))
                {
                    IfLogin = TheOneAndOnly;
                }
            }
            if (IfLogin != NULL)
            {
                int action = 0;
                while (action != 4)
                {
                    // IfLogin->getAccountHolders();
                    cout << "Choose Service:\n(1)Get all statements\n(2)Fast Forward\n(3)Get account holders\n(4)Exit\nOption: ";
                    cin >> action;
                    if (action == 1)
                    {
                        int AccountNo;
                        cout << "Enter account No. :";
                        cin >> AccountNo;
                        IfLogin->getStatementOfAccount(AccountNo);
                    }
                    else if (action == 2)
                    {
                        IfLogin->fastforward();
                        printf("Updated Global Date: %d/%d/%d", GlobalDate.Day, GlobalDate.Month, GlobalDate.Year);
                    }
                    else if (action == 3)
                    {
                        IfLogin->getAccountHolders();
                    }
                }
            }
        }
    }
    return 0;
}