#include <iostream>
#include <bits/stdc++.h>

using namespace std;

map<string, int> listu;
set<double> lista;

double generate_random_double()
{
    int i = 0, x = 0, a;
    while (i < 8)
    {
        a = rand() % 10;
        x = 10 * x + a;
        i++;
    }
    a = (rand() % 9) + 1;
    x = 10 * x + a;
    return x;
}

class User
{
public:
    class Account;

private:
    string name;
    string username;
    double password = 148;
    vector<Account> ListofAcc;

public:
    class Account
    {
    private:
        string Account_no;
        double balance = 0;
        string openDate;
        vector<string> transactions;

    public:
        friend void deposit(double num)
        {
            balance += num;
            transactions.push_back();
        }

        friend void withdraw(double num)
        {
            balance -= num;
        }

        void transfer() {}

        void displayBalance()
        {
            cout << "Balance: " << balance << endl;
        }

        void displayAccountNo()
        {
            string w = Account_no.substr(0, 8);
            cout << "AccountNo: " << w << endl;
        }
        void setBalance(double newBalance)
        {
            balance = newBalance;
        }
        void setAccountNo(string newAccountNo)
        {
            Account_no = newAccountNo;
        }
        double getBalance()
        {
            return balance;
        }
        Account() {}
    };
    class SavingsAccount : public Account
    {
    private:
        double interestRate = getBalance() * 0.0000050505;

    public:
        void displayInterestRate()
        {
            cout << "Interest Rate: " << interestRate << endl;
        }
        void setInterestRate()
        {
            interestRate = getBalance() * 0.0000050505;
        }
    };
    class CheckingAccount : public Account
    {
    private:
        double interestRate = 0;

    public:
        void displayInterestRate()
        {
            throw invalid_argument("Interest Rate is 0");
        }
    };
    void getAccount()
    {
        cout << "Accounts of this user: " << endl;
        for (auto accPtr = ListofAcc.begin(); accPtr != ListofAcc.end(); ++accPtr)
        {
            (*accPtr).displayAccountNo();
        }
    }
    void changePasswd(double new_pass)
    {
        password = new_pass;
    }

    void displayPasswd()
    {
        cout << "password: " << password << endl;
    }

    void displayUsername()
    {
        cout << "Username: " << username << endl;
    }

    int login(double num)
    {
        return password == num ? 1 : 0;
    }

    friend User createUser(string uname, double num);
    Account createAccount(string openDate, double principle, string accType)
    {

        double AccountNo = generate_random_double();
        while (lista.count(AccountNo) != 0)
        {
            AccountNo = generate_random_double();
        }
        lista.insert(AccountNo);
        if (accType == "savings")
        {
            SavingsAccount saveAccount;
            saveAccount.setBalance(principle);
            saveAccount.setAccountNo(to_string(AccountNo));
            ListofAcc.push_back(saveAccount);
            return saveAccount;
        }
        else if (accType == "checking")
        {
            CheckingAccount checkAccount;
            checkAccount.setBalance(principle);
            checkAccount.setAccountNo(to_string(AccountNo));
            ListofAcc.push_back(checkAccount);
            return checkAccount;
        }
        else
        {
            throw invalid_argument("Enter either savings or checking");
        }
    }

    User() {}
};

User createUser(string uname, double num)
{
    User temp;
    temp.password = num;
    if (listu[uname] == 0)
    {
        temp.username = uname;
        listu[uname]++;
    }
    else
    {
        listu[uname]++;
        int w = listu[uname];
        uname = uname + to_string(w);
        temp.username = uname;
    }
    return temp;
}

int main()
{
    User Adarsh = createUser("Adarsh", 148);
    // Adarsh.displayUsername();
    // Adarsh.displayPasswd();
    User::Account Sita = Adarsh.createAccount("14-08-2005", 148, "savings");
    User::Account Ram = Adarsh.createAccount("24-01-2006", 241, "checking");
    Adarsh.getAccount();
    User unik = createUser("unik", 138);
    // unik.displayUsername();
    // unik.displayPasswd();
    User::Account Sita1 = unik.createAccount("14-08-2005", 148, "checking");
    User::Account Ram1 = unik.createAccount("24-01-2006", 241, "savings");
    unik.getAccount();
    // cout << endl;
    // Adarsh.getAccount();
    // Ram.deposit(0);
    // Ram.displayBalance();
    // Sita.displayBalance();
    return 0;
}
