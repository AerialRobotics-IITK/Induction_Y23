#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <menu.h>
#include <ncurses.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

using namespace std;

struct transaction
{
    string type;
    double amount;
    string date;
    
    transaction(string type, double amount, string date)
    {
        this->type = type;
        this->amount = amount;
        this->date = date;
    }
};

class bankAccount
{
private:
    string accountNumber;
    double balance;
    string openDate;
    string type;
    vector<transaction> transactions;
    int interestRate;
public:
    bankAccount(string accountNumber, double balance, string openDate, string type, int interestRate)
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->openDate = openDate;
        this->type = type;
        this->interestRate = interestRate;
    }
    string getAccountNumber()
    {
        return accountNumber;
    }
    double getBalance()
    {
        return balance;
    }
    string getOpenDate()
    {
        return openDate;
    }
    string getType()
    {
        return type;
    }
    int getInterestRate()
    {
        return interestRate;
    } 
    void deposit(double amount)
    {
        balance += amount;
        transaction t("Deposit", amount, date());
        transactions.push_back(t);
    }
    void addInterest()
    {
        double interest = balance * interestRate / 100;
        balance += interest;
        transaction t("Interest", interest, date());
        transactions.push_back(t);
    }
    void withdraw(double amount)
    {
        if (balance - amount < 0)
        {
            cout << "Insufficient funds" << endl;
        }
        else
        {
            balance -= amount;
            transaction t("Withdraw", amount, date());
            transactions.push_back(t);
        }
    }   
    void viewTransactions()
    {
        //print row with table format with width 20
        cout << left << setw(20) << "Type" << left << setw(20) << "Amount" << left << setw(20) << "Date" << endl;
        for (auto t : transactions)
        {
            cout << left << setw(20) << t.type << left << setw(20) << t.amount << left << setw(20) << t.date << endl;
        }
    }
    string date(){
        auto t = std::time(nullptr);
        auto timePtr = std::localtime(&t);
        ostringstream oss;
        oss << std::put_time(timePtr, "%d/%m/%Y");
        return oss.str();
    }
};

class bankAccountHolder {
private:
    string name;
    string username;
    string password;
    vector<bankAccount> accounts;
public:
    bankAccountHolder(string name, string username, string password)
    {
        this->name = name;
        this->username = username;
        this->password = password;
    }
    string getName()
    {
        return name;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    void addAccount(bankAccount account)
    {
        accounts.push_back(account);
    }
    void viewAccounts()
    {
        cout << left << setw(20) << "Account Number" << left << setw(20) << "Balance" << left << setw(20) << "Open Date" << left << setw(20) << "Type" << endl;
        for (auto a : accounts)
        {
            cout << left << setw(20) << a.getAccountNumber() << left << setw(20) << a.getBalance() << left << setw(20) << a.getOpenDate() << left << setw(20) << a.getType() << endl;
        }
    }
};

class branchManager {
private:
    string username;
    string password;
    vector<bankAccountHolder> bankAccountHolders;
public:
    branchManager(string username, string password)
    {
        this->username = username;
        this->password = password;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    void addAccountHolder(bankAccountHolder accountHolder)
    {
        bankAccountHolders.push_back(accountHolder);
    }
    void viewAccountHolders()
    {
        cout << left << setw(20) << "Name" << left << setw(20) << "Username" << endl;
        for (auto a : bankAccountHolders)
        {
            cout << left << setw(20) << a.getName() << left << setw(20) << a.getUsername() << endl;
        }
    }
};

class savingsAccount : public bankAccount
{
private:
    int interestRate;
public:
    savingsAccount(string accountNumber, double balance, string openDate) : bankAccount(accountNumber, balance, openDate, "Savings", 5)
    {
        interestRate = 5;
    }
    void changeInterestRate(int rate)
    {
        interestRate = rate;
    }
    int getInterestRate()
    {
        return interestRate;
    }
};

class currentAccount : public bankAccount
{
public:
    currentAccount(string accountNumber, double balance, string openDate) : bankAccount(accountNumber, balance, openDate, "Current", 0)
    {
    }
    int getInterestRate()
    {
        return 0;
    }
};

void login(){
}

void createAccount(){ 
}

int main(){
    branchManager branchManager("admin", "admin");
    // cout << "Enter 1 to login or 2 to create account" << endl;
    // int option;
    // cin >> option;
    // if (option == 1){
    //     login();
    // }
    // else if (option == 2){
    //     createAccount();
    // }
    // else{
    //     cout << "Invalid option" << endl;
    // }
    char *choices[] = {
    "Login",
    "Register",
    (char *)NULL,
    };

    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(choices[i], "");
    }
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "Use arrow keys to navigate. Press Enter to select an option.");
    post_menu(my_menu);
    refresh();

    while((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: /* Enter */
                cur_item = current_item(my_menu);
                if(strcmp(item_name(cur_item), "Login") == 0) {
                    login();
                } else if(strcmp(item_name(cur_item), "Register") == 0) {
                    createAccount();
                }
                break;
        }
    }

    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();
}