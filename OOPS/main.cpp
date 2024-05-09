#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

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
public:
  int acc_no;
  float balance;
  Date open_date;
  void withdraw(float amount) {
    if (amount <= balance) {
      printf("Ammount %f has been withdrawn\n", amount);
      balance -= amount;
    } else {
      cout << "Not possible not enough balance" << endl;
    }
  };
  void deposit(float amount) {
    printf("Ammount %f has been deposited\n", amount);
    balance += amount;
  };
  void transfer(float amount, int acc_no){};
};

class SavingsAccount : private BankAccount {
public:
  float interest_rate;
  float getInterestRate() { return interest_rate; }
  void setInterestRate(float rate) { interest_rate = rate; }
};

class CheckingAccount : private BankAccount {
public:
  float interest_rate;
};

class BankAccountHolder {
public:
  string Name;
  string Username;
  string passwd;
};

class BranchManager {
public:
  string username;
  string passwd;
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
  if (user_type == 1) {
  } else {
  }
}
