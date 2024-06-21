#include <bits/stdc++.h>
#include <ctime>
using namespace std;

// Global date variable (assuming we start from a specific date)
time_t global_date = time(nullptr);

void advance_global_date(int days) {
    global_date += days * 24 * 60 * 60;
}

string get_date_string(time_t date) {
    tm* local_time = localtime(&date);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local_time);
    return string(buffer);
}

class BankAccount {
protected:
    int account_number;
    double balance;
    time_t open_date;
    vector<string> statements;

public:
    BankAccount(int acc_num, double opening_balance)
        : account_number(acc_num), balance(opening_balance) {
        open_date = global_date;
        statements.push_back("Account opened with balance: " + to_string(opening_balance) + " on " + get_date_string(open_date));
    }

    virtual ~BankAccount() = default;

    int get_account_number() const { return account_number; }
    double get_balance() const { return balance; }
    virtual void apply_interest(time_t current_date) = 0;

    void deposit(double amount) {
        balance += amount;
        statements.push_back("Deposit: " + to_string(amount) + " on " + get_date_string(global_date));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            statements.push_back("Withdrawal: " + to_string(amount) + " on " + get_date_string(global_date));
        } else {
            throw runtime_error("Insufficient funds");
        }
    }

    const vector<string>& get_statements() const { return statements; }
};

class SavingsAccount : public BankAccount {
private:
    double interest_rate;

public:
    SavingsAccount(int acc_num, double opening_balance, double rate)
        : BankAccount(acc_num, opening_balance), interest_rate(rate) {}

    void apply_interest(time_t current_date) override {
        // Calculate the number of days since the account was opened or last interest application
        double days_passed = difftime(current_date, open_date) / (60 * 60 * 24);
        if (days_passed >= 30) {
            // Apply interest for every full month
            double months = days_passed / 30;
            double interest = balance * interest_rate * (months / 12);
            balance += interest;
            statements.push_back("Interest applied: " + to_string(interest) + " on " + get_date_string(current_date));
            // Reset open_date to current_date after applying interest
            open_date = current_date;
        }
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(int acc_num, double opening_balance)
        : BankAccount(acc_num, opening_balance) {}

    void apply_interest(time_t current_date) override {
        // Checking accounts do not accumulate interest
    }
};

class User {
protected:
    string name;
    string username;
    string password;

public:
    User(const string& name, const string& username, const string& password)
        : name(name), username(username), password(password) {}

    virtual ~User() = default;

    string get_username() const { return username; }

    static User* login(const vector<User*>& users, const string& username, const string& password = "") {
        for (User* user : users) {
            if (user->username == username && (password.empty() || user->password == password)) {
                return user;
            }
        }
        return nullptr;
    }
};

class AccountHolder : public User {
private:
    vector<BankAccount*> accounts;

    static int generate_account_number() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(100000000, 999999999);
        return dis(gen);
    }

public:
    AccountHolder(const string& name, const string& username, const string& password)
        : User(name, username, password) {}

    ~AccountHolder() {
        for (BankAccount* account : accounts) {
            delete account;
        }
    }

    void create_account(const string& account_type, double opening_balance, double interest_rate) {
        int account_number = generate_account_number();
        if (account_type == "savings") {
            accounts.push_back(new SavingsAccount(account_number, opening_balance, interest_rate));
        } else if (account_type == "checking") {
            accounts.push_back(new CheckingAccount(account_number, opening_balance));
        } else {
            throw runtime_error("Invalid account type");
        }
    }

    void close_account(int account_number) {
        auto it = find_if(accounts.begin(), accounts.end(), [account_number](BankAccount* account) {
            return account->get_account_number() == account_number;
        });
        if (it != accounts.end()) {
            delete *it;
            accounts.erase(it);
            cout << "Account closed successfully!" << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void change_password(const string& new_password) {
        password = new_password;
    }

    const vector<BankAccount*>& get_accounts() const {
        return accounts;
    }

    void view_statements() const {
        for (const BankAccount* account : accounts) {
            cout << "Statements for Account " << account->get_account_number() << ":" << endl;
            for (const string& statement : account->get_statements()) {
                cout << statement << endl;
            }
        }
    }

    void transfer_money(int from_account_number, int to_account_number, double amount, const vector<User*>& users) {
        BankAccount* from_account = nullptr;
        for (BankAccount* account : accounts) {
            if (account->get_account_number() == from_account_number) {
                from_account = account;
                break;
            }
        }

        if (!from_account) {
            throw runtime_error("Source account not found");
        }

        BankAccount* to_account = nullptr;
        for (User* user : users) {
            if (AccountHolder* holder = dynamic_cast<AccountHolder*>(user)) {
                for (BankAccount* account : holder->get_accounts()) {
                    if (account->get_account_number() == to_account_number) {
                        to_account = account;
                        break;
                    }
                }
            }
            if (to_account) {
                break;
            }
        }

        if (!to_account) {
            throw runtime_error("Destination account not found");
        }

        from_account->withdraw(amount);
        to_account->deposit(amount);
        cout << "Money transferred successfully!" << endl;
    }
};

class BranchManager : public User {
public:
    static BranchManager& get_instance(const string& username, const string& password) {
        static BranchManager instance(username, password);
        return instance;
    }

    void fast_forward_days(int days, vector<User*>& users) {
        advance_global_date(days);
        time_t current_date = global_date;

        for (User* user : users) {
            if (AccountHolder* holder = dynamic_cast<AccountHolder*>(user)) {
                for (BankAccount* account : holder->get_accounts()) {
                    account->apply_interest(current_date);
                }
            }
        }
    }

    string get_statement_of_account(const AccountHolder& holder, int account_number) const {
        for (const BankAccount* account : holder.get_accounts()) {
            if (account->get_account_number() == account_number) {
                string statements = "Statements for Account " + to_string(account_number) + ":\n";
                for (const string& statement : account->get_statements()) {
                    statements += statement + "\n";
                }
                return statements;
            }
        }
        throw runtime_error("Account not found");
    }

    vector<pair<string, int>> get_account_holders(const vector<User*>& users) const {
        vector<pair<string, int>> account_holders;
        for (const User* user : users) {
            if (const AccountHolder* holder = dynamic_cast<const AccountHolder*>(user)) {
                for (const auto& account : holder->get_accounts()) {
                    account_holders.emplace_back(holder->get_username(), account->get_account_number());
                }
            }
        }
        return account_holders;
    }

private:
    BranchManager(const string& username, const string& password)
        : User("Manager", username, password) {}
};

void cli() {
    vector<User*> users;
    users.push_back(&BranchManager::get_instance("manager", "manager_password"));

    while (true) {
        cout << "\nBanking System CLI" << endl;
        cout << "1. Account Holder Login/Sign-Up" << endl;
        cout << "2. Branch Manager Login" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 3) {
            break;
        }

        if (choice == 1) {
            cout << "1. Sign-Up" << endl;
            cout << "2. Login" << endl;

            int login_choice;
            cin >> login_choice;

            if (login_choice == 1) {
                string name, username, password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (any_of(users.begin(), users.end(), [&username](User* user) { return user->get_username() == username; })) {
                    cout << "Username already exists!" << endl;
                } else {
                    users.push_back(new AccountHolder(name, username, password));
                    cout << "Account holder registered successfully!" << endl;
                }
            } else if (login_choice == 2) {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                User* user = User::login(users, username, password);
                if (AccountHolder* holder = dynamic_cast<AccountHolder*>(user)) {
                    while (true) {
                        cout << "\nAccount Holder Menu" << endl;
                        cout << "1. Create Account" << endl;
                        cout << "2. Close Account" << endl;
                        cout << "3. View Statements" << endl;
                        cout << "4. Transfer Money" << endl;
                        cout << "5. Change Password" << endl;
                        cout << "6. Logout" << endl;

                        int holder_choice;
                        cin >> holder_choice;
                        if (holder_choice == 1) {
                            string account_type;
                            double opening_balance, interest_rate;
                            cout << "Enter account type (savings/checking): ";
                            cin >> account_type;
                            cout << "Enter opening balance: ";
                            cin >> opening_balance;

                            if (account_type == "savings") {
                                cout << "Enter interest rate: ";
                                cin >> interest_rate;
                            } else {
                                interest_rate = 0.0;
                            }

                            holder->create_account(account_type, opening_balance, interest_rate);
                            cout << "Account created successfully!" << endl;
                        } else if (holder_choice == 2) {
                            int account_number;
                            cout << "Enter account number: ";
                            cin >> account_number;
                            holder->close_account(account_number);
                        } else if (holder_choice == 3) {
                            holder->view_statements();
                        } else if (holder_choice == 4) {
                            int from_account_number, to_account_number;
                            double amount;
                            cout << "Enter your account number: ";
                            cin >> from_account_number;
                            cout << "Enter destination account number: ";
                            cin >> to_account_number;
                            cout << "Enter amount: ";
                            cin >> amount;

                            try {
                                holder->transfer_money(from_account_number, to_account_number, amount, users);
                            } catch (const exception& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        } else if (holder_choice == 5) {
                            string new_password;
                            cout << "Enter new password: ";
                            cin >> new_password;
                            holder->change_password(new_password);
                            cout << "Password changed successfully!" << endl;
                        } else if (holder_choice == 6) {
                            break;
                        }
                    }
                } else {
                    cout << "Invalid username or password!" << endl;
                }
            }
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            User* user = User::login(users, username, password);
            if (BranchManager* manager = dynamic_cast<BranchManager*>(user)) {
                while (true) {
                    cout << "\nBranch Manager Menu" << endl;
                    cout << "1. Get Statement of Account" << endl;
                    cout << "2. Get Account Holders" << endl;
                    cout << "3. Fast Forward Days" << endl;
                    cout << "4. Logout" << endl;

                    int mgr_choice;
                    cin >> mgr_choice;
                    if (mgr_choice == 1) {
                        string acc_holder_username;
                        int account_number;
                        cout << "Enter account holder username: ";
                        cin >> acc_holder_username;
                        cout << "Enter account number: ";
                        cin >> account_number;

                        try {
                            User* acc_holder_user = User::login(users, acc_holder_username);
                            if (AccountHolder* acc_holder = dynamic_cast<AccountHolder*>(acc_holder_user)) {
                                string statements = manager->get_statement_of_account(*acc_holder, account_number);
                                cout << statements << endl;
                            } else {
                                throw runtime_error("Account holder not found");
                            }
                        } catch (const exception& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    } else if (mgr_choice == 2) {
                        vector<pair<string, int>> account_holders = manager->get_account_holders(users);
                        for (const auto& holder : account_holders) {
                            cout << "Username: " << holder.first << ", Account Number: " << holder.second << endl;
                        }
                    } else if (mgr_choice == 3) {
                        cout << "Enter number of days to fast forward: ";
                        int days;
                        cin >> days;

                        manager->fast_forward_days(days, users);
                        cout << "Time fast forwarded by " << days << " days." << endl;
                    } else if (mgr_choice == 4) {
                        break;
                    }
                }
            } else {
                cout << "Invalid username or password!" << endl;
            }
        }
    }

    // Cleanup dynamically allocated memory
    for (User* user : users) {
        if (dynamic_cast<BranchManager*>(user) == nullptr) {
            delete user;
        }
    }
}

int main() {
    cli();
    return 0;
}
