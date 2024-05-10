#include <chrono>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class BankAccount;
class BankAccountHolder;

const float SAVINGS_MIN = 100;
const float SAVINGS_TRANS_MAX = 10000;

int account_no_count = 0;
vector<BankAccount *> bank_accounts;
BankAccount *curr_account;
BankAccountHolder *curr_holder;

struct Date {
  int year;
  int month;
  int day;
};
typedef struct Date Date;

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
private:
  BankAccount *get_account(int acc_no) { return bank_accounts[acc_no - 1]; }

public:
  int acc_no;
  int type;
  float balance;
  Date open_date;
  void withdraw(float amount) {
    if (amount <= balance) {
      balance -= amount;
    } else {
      invalid_argument("Not possible not enough balance");
    }
  };
  void deposit(float amount) { balance += amount; };
  void transfer(float amount, int acc_no) {
    BankAccount *to_acc = get_account(acc_no);
    if (amount <= balance) {
      balance -= amount;
      to_acc->balance += amount;
    } else {
      invalid_argument("Not possible not enough balance");
    }
  };
};

class SavingsAccount : public BankAccount {
private:
  float interest_rate;
  float getInterestRate() { return interest_rate; }

public:
  void setInterestRate(float rate) {
    if (interest_rate <= 6)
      interest_rate = rate;
    else
      invalid_argument("Interest rate cannot be higher than 6%");
  }
};

class CheckingAccount : public BankAccount {
private:
  float interest_rate;

public:
  void setInterestRate(float interest) { interest_rate = interest; }
};

class BankAccountHolder {
public:
  string Name;
  string Username;
  string passwd;
  vector<BankAccount> bankaccounts;
  void changepasswd(string pass) { passwd = pass; }
  vector<BankAccount> get_accounts() { return bankaccounts; }

private:
  void createAccount(int type, float start_amount, float interest) {
    switch (type) {
    case 1:
      if (start_amount < SAVINGS_MIN) {
        invalid_argument("Opening Savings Account requires at least 100");
      }
      SavingsAccount saving_acc;
      saving_acc.acc_no = account_no_count + 1;
      saving_acc.type = 1;
      saving_acc.balance = start_amount;
      saving_acc.open_date = get_current_date();
      saving_acc.setInterestRate(interest);
      bankaccounts.push_back(saving_acc);
      bank_accounts.push_back(&saving_acc);
      break;
    case 2:
      CheckingAccount check_acc;
      check_acc.acc_no = account_no_count + 1;
      saving_acc.type = 2;
      check_acc.balance = start_amount;
      check_acc.open_date = get_current_date();
      check_acc.setInterestRate(interest);
      bankaccounts.push_back(check_acc);
      bank_accounts.push_back(&check_acc);
      break;
    }
    account_no_count++;
  }
};

class BranchManager {
public:
  string username;
  string passwd;
  vector<BankAccount *> get_accounts() { return bank_accounts; }
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
  cout << "Who are you (Enter the number to select)" << endl;
  cout << "1. Bank Account Holder" << endl;
  cout << "2. Branch Manager" << endl;
  return get_option_bw(1, 2);
}

int main() {
  int user_type = who_you();
  switch (user_type) {
  case 1:
    break;
  case 2:
    break;
  }
}
