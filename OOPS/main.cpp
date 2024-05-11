#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

using namespace std;

struct Date {
  int year;
  int month;
  int day;
};
typedef struct Date Date;

struct Transaction {
  string satement;
  Date date;
};

class BankAccount;
class BankAccountHolder;

const float SAVINGS_MIN = 100;
const float SAVINGS_TRANS_MAX = 10000;

int account_no_count = 0;
map<int, BankAccount> bank_accounts;
map<string, BankAccountHolder> account_holders;
vector<Transaction> transactions;

BankAccount *curr_account;
BankAccountHolder *curr_holder;

// Terminal Utils
void clrsrc() { cout << "\033[2J\033[1;1H"; }
void press_enter_to_continue() {
  cout << "(Press Enter to Continue)" << endl;
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cin.get();
}

Date get_current_date() {
  time_t currentTime = time(nullptr);

  // Convert current time to struct tm
  tm *timeinfo = localtime(&currentTime);

  Date curr_date;
  // Extract year, month, and day from timeinfo
  curr_date.year = timeinfo->tm_year + 1900; // years since 1900
  curr_date.month = timeinfo->tm_mon + 1;    // months since January [0, 11]
  curr_date.day = timeinfo->tm_mday;         // day of the month [1, 31]
  return curr_date;
}

class BankAccount {
public:
  int acc_no;
  int type;
  float balance;
  Date open_date;
  void withdraw(float amount) {
    if (amount <= balance) {
      balance -= amount;
    } else {
      throw invalid_argument("Not possible not enough balance");
    }
  };
  void deposit(float amount) { balance += amount; };
  void transfer(float amount, int acc_no) {
    BankAccount *to_acc = &bank_accounts[acc_no];
    if (amount <= balance) {
      balance -= amount;
      to_acc->balance += amount;
    } else {
      throw invalid_argument("Not possible not enough balance");
    }
  };
};

class SavingsAccount : public BankAccount {
public:
  float interest_rate;
  float getInterestRate() { return interest_rate; }

public:
  void setInterestRate(float rate) {
    if (interest_rate <= 6)
      interest_rate = rate;
    else
      throw invalid_argument("Interest rate cannot be higher than 6%");
  }
};

class CheckingAccount : public BankAccount {
public:
  float interest_rate;

public:
  void setInterestRate(float interest) { interest_rate = interest; }
};

class BankAccountHolder {
public:
  string Name;
  string Username;
  string passwd;
  vector<int> bankaccounts;
  void changepasswd(string pass) { passwd = pass; }
  vector<int> get_accounts() { return bankaccounts; }

public:
  int createAccount(int type, float start_amount, float interest) {
    try {
      switch (type) {
      case 1:
        if (start_amount < SAVINGS_MIN) {
          throw invalid_argument(
              "Opening Savings Account requires at least 100");
        }
        SavingsAccount saving_acc;
        saving_acc.acc_no = account_no_count + 1;
        saving_acc.type = 1;
        saving_acc.balance = start_amount;
        saving_acc.open_date = get_current_date();
        saving_acc.setInterestRate(interest);
        bankaccounts.push_back(saving_acc.acc_no);
        bank_accounts[saving_acc.acc_no] = saving_acc;
        break;
      case 2:
        CheckingAccount check_acc;
        check_acc.acc_no = account_no_count + 1;
        check_acc.type = 2;
        check_acc.balance = start_amount;
        check_acc.open_date = get_current_date();
        check_acc.setInterestRate(interest);
        bankaccounts.push_back(check_acc.acc_no);
        bank_accounts[check_acc.acc_no] = check_acc;
        break;
      }
    } catch (...) {
      cout << "Cannot create Account" << endl;
      press_enter_to_continue();
    }
    account_no_count++;
    return account_no_count;
  }
};

class BranchManager {
public:
  string username;
  string passwd;
  map<string, BankAccountHolder> get_account_holders() {
    return account_holders;
  }
};

int get_option_bw(int a, int b) {
  int opt;
  while (true) {
    cin >> opt;
    if (opt <= b && opt >= a)
      break;
    printf("Please enter a number between %d and %d\n", a, b);
  }
  return opt;
}

int who_you() {
  clrsrc();
  cout << "Who are you (Enter the number to select)" << endl;
  cout << "1. Bank Account Holder" << endl;
  cout << "2. Branch Manager" << endl;
  return get_option_bw(1, 2);
}

void create_new_account_holder() {
  string name;
  string username;
  string passwd;

  try {
    clrsrc();
    cout << "Enter your name" << endl;
    cin >> name;
    cout << "Enter your UserName" << endl;
    cin >> username;
    cout << "Enter your Password" << endl;
    cin >> passwd;
  } catch (...) {
    throw invalid_argument("Cannot get Account holder info");
    press_enter_to_continue();
  }
  try {
    BankAccountHolder acc_holder;
    acc_holder.Name = name;
    acc_holder.passwd = passwd;
    acc_holder.Username = username;
    account_holders[username] = acc_holder;
  } catch (...) {
    throw invalid_argument("Cannot add account holder");
    press_enter_to_continue();
  }
}

void create_account() {
  clrsrc();
  cout << "Select Account type" << endl
       << "1. Savings Account" << endl
       << "2. Checking Account" << endl;
  int opt = get_option_bw(1, 2);
  try {
    cout << "Enter Start Balance" << endl;
    float start_bal;
    cin >> start_bal;
    cout << "Enter Interest Rate" << endl;
    float interest;
    cin >> interest;
    int acc_no = curr_holder->createAccount(opt, start_bal, interest);
    cout << "Account Created with acc. no: " << acc_no << endl;
    press_enter_to_continue();
  } catch (...) {
    throw invalid_argument("");
  }
}
void select_account() {
  int acc_no;
  try {
    cout << "Enter Account no: ";
    cin >> acc_no;
    curr_account = &bank_accounts[acc_no];
  } catch (...) {
    cout << "Cannot Find Bank account" << endl;
    press_enter_to_continue();
  }
}
void transfer_money() {
  int ben_acc_no;
  float amount;
  try {
    cout << "Enter Account no(Beneficiary): ";
    cin >> ben_acc_no;
    cout << "Enter Amount to be tranferred: ";
    cin >> amount;
  } catch (...) {
    cout << "Cannot Find Bank account" << endl;
    press_enter_to_continue();
  }
  try {
    curr_account->transfer(amount, ben_acc_no);
  } catch (...) {
    cout << "Cannot transfer amount" << endl;
    press_enter_to_continue();
  }
}
void view_balance() {
  int acc_no;
  try {
    printf("Account Balance is: %f\n", curr_account->balance);
    press_enter_to_continue();
  } catch (...) {
    cout << "Cannot Find Bank account" << endl;
  }
}
void delete_account() {
  try {
    int acc_no = curr_account->acc_no;
    curr_holder->bankaccounts.erase(
        std::remove(curr_holder->bankaccounts.begin(),
                    curr_holder->bankaccounts.end(), acc_no),
        curr_holder->bankaccounts.end());
    bank_accounts.erase(acc_no);
    cout << "Account Deleted" << endl;
  } catch (...) {
    cout << "No such Account" << endl;
  }
  press_enter_to_continue();
}

void login_acc_holder() {
  string username;
  string passwd;

  try {
    clrsrc();
    cout << "Enter your UserName" << endl;
    cin >> username;
    cout << "Enter your Password" << endl;
    cin >> passwd;
  } catch (...) {
    throw invalid_argument("Cannot get Account holder info");
    press_enter_to_continue();
  }

  try {
    curr_holder = &account_holders[username];
    if (curr_holder->passwd == passwd) {
      cout << "You are logged in" << endl;
    } else {
      throw invalid_argument("Username or password invalid");
      press_enter_to_continue();
    }
  } catch (...) {
    throw invalid_argument("Username or password invalid");
    press_enter_to_continue();
  }

  clrsrc();
  cout << "What Operation You want to perform" << endl
       << "1. Create Account" << endl
       << "2. Transfer Amount" << endl
       << "3. View Balance" << endl
       << "4. View Statements" << endl
       << "5. Delete Account" << endl;
  int opt = get_option_bw(1, 5);
  switch (opt) {
  case 1:
    try {
      create_account();
    } catch (...) {
      cout << "Cannot create account" << endl;
      press_enter_to_continue();
    }
    break;
  case 2:
    select_account();
    transfer_money();
    break;
  case 3:
    select_account();
    view_balance();
    break;
  case 4:
    select_account();
    break;
  case 5:
    select_account();
    delete_account();
    break;
  }
}

int main() {
  BranchManager branch_manager;
  branch_manager.username = "root";
  branch_manager.passwd = "root";
  bool quit = false;
  while (!quit) {
    int user_type = who_you();
    if (user_type == 1) {
      clrsrc();
      cout << "1. New User" << endl << "2. Existing User" << endl;
      int opt = get_option_bw(1, 2);
      if (opt == 1) {
        try {
          create_new_account_holder();
        } catch (...) {
          cout << "Cannot new create account holder" << endl;
          press_enter_to_continue();
        }
      } else {
        try {
          login_acc_holder();
        } catch (...) {
          cout << "Cannot login" << endl;
          press_enter_to_continue();
        }
      }
    } else {
    }
    clrsrc();
    cout << "Do you want to quit?" << endl
         << "0. No" << endl
         << "1. Yes" << endl;
    cin >> quit;
  }
}
