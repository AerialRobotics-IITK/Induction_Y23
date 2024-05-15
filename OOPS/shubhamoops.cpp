#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class Account {
public:
    Account(const string& accountType, int openingAmount)
        : accountType(accountType), balance(openingAmount) {}

    string getAccountType() const { return accountType; }
    int getBalance() const { return balance; }
    void deposit(int amount) { balance += amount; }

private:
    string accountType;
    int balance;
};

class User {
public:
    User(const string& name, const string& username, const string& password, const string& accountNumber, const Account& account)
        : name(name), username(username), password(password), accountNumber(accountNumber), account(account) {}

    string getName() const { return name; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getAccountNumber() const { return accountNumber; }
    const Account& getAccount() const { return account; }

private:
    string name;
    string username;
    string password;
    string accountNumber;
    Account account;
};

class UserDatabase {
public:
    UserDatabase(vector<User>& users, vector<string>& accountNumbers) : users(users), accountNumbers(accountNumbers) {}

    bool findUser(const string& username, const string& password, User*& foundUser) {
        for (auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                foundUser = &user;
                return true;
            }
        }
        return false;
    }

    void addUser(const User& user, const string& accountNumber) {
        users.push_back(user);
        accountNumbers.push_back(accountNumber);
    }
    const vector<User>& getUsers() const {
        return users;
    }

private:
    vector<User>& users;
    vector<string>& accountNumbers;
};

class SignUp {
public:
    SignUp(UserDatabase& UserDatabase, vector<string>& accountNumbers)
        : UserDatabase(UserDatabase), accountNumbers(accountNumbers) {}

    void signUp() {
        string name, username, password, accountType;
        int openingAmount;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        do {
            cout << "Enter username: ";
            getline(cin, username);
        } while (!CheckUnique(username));

        cout << "Enter password: ";
        getline(cin, password);

        cout << "Enter account type (Savings/Current): ";
        getline(cin, accountType);

        cout << "Enter opening amount: ";
        cin >> openingAmount;

        string accountNumber = generateAccountNumber();
        Account account(accountType, openingAmount);
        User newUser(name, username, password, accountNumber, account);
        UserDatabase.addUser(newUser, accountNumber);
        cout << "Sign up successful! Your account number is: " << accountNumber << endl;
    }

private:
    UserDatabase& UserDatabase;
    vector<string>& accountNumbers;

    bool CheckUnique(const string& username) {
        for (const auto& user : UserDatabase.getUsers()) {
            if (user.getUsername() == username) {
                cout << "Username already exists. Please choose a different one." << endl;
                return false;
            }
        }
        return true;
    }

    string generateAccountNumber() {
        string accountNumber;
        static const char digits[] = "0123456789";
        const int numDigits = 9;
        uniform_int_distribution<int> distribution(0, 9);
        mt19937 engine(static_cast<unsigned int>(time(0)));
        bool unique = false;

        do {
            accountNumber.clear();
            for (int i = 0; i < numDigits; ++i) {
                accountNumber += digits[distribution(engine)];
            }
            if (find(accountNumbers.begin(), accountNumbers.end(), accountNumber) == accountNumbers.end()) {
                unique = true;
            }
        } while (!unique);

        return accountNumber;
    }
};

class LogIn {
public:
    LogIn(UserDatabase& UserDatabase) : UserDatabase(UserDatabase) {}

    void logIn() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User* foundUser = nullptr;

        if (UserDatabase.findUser(username, password, foundUser)) {
            cout << "Login Successful! Welcome, " << foundUser->getName() << "." << endl;
            cout << "Your account number is: " << foundUser->getAccountNumber() << endl;
            cout << "Account Type: " << foundUser->getAccount().getAccountType() << endl;
            cout << "Balance: " << foundUser->getAccount().getBalance() << endl;
        } else {
            cout << "Incorrect username or password. Please try again." << endl;
        }
    }

private:
    UserDatabase& UserDatabase;
};

int main() {
    int option;
    vector<User> users;
    vector<string> accountNumbers;

    UserDatabase UserDatabase(users, accountNumbers);

    SignUp SignUp(UserDatabase, accountNumbers);
    LogIn LogIn(UserDatabase);

    //BRANCH MANAGER LOGIN DETAILS
    const string BMUsername = "manager";
    const string BMPassword = "manager";

    while (true) {
        cout << "-----------WELCOME------------" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login as User" << endl;
        cout << "3. Login as Branch Manager" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1) {
            SignUp.signUp();
        } else if (option == 2) {
            LogIn.logIn();
        } else if (option == 3) {
            string username, password;
            cout << "Enter branch manager username: ";
            cin >> username;
            cout << "Enter branch manager password: ";
            cin >> password;
            if (username == BMUsername && password == BMPassword) {
                cout << "Login Successful! Welcome, Branch Manager." << endl;
                while (true) {
                    cout << "-----------BRANCH MANAGER MENU------------" << endl;
                    cout << "1. Show all accounts" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Enter your option: ";
                    cin >> option;
                    if (option == 1) {
                        cout << "List of all accounts:" << endl;
                        for (const auto& user : users) {
                            cout << "Name: " << user.getName() << ", Account Number: " << user.getAccountNumber() << endl;
                        }
                    } else if (option == 2) {
                        cout << "...Exiting Branch Manager mode..." << endl;
                        break; 
                    } else {
                        cout << "Invalid. Please try again." << endl;
                    }
                }
            } else {
                cout << "Incorrect username or password. Please try again." << endl;
            }
        } else if (option == 4) {
            cout << "Thank you for visiting!" << endl;
            return 0;
        } else {
            cout << "Invalid. Please try again." << endl;
        }
    }

    return 0;
}



