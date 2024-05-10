#include <bits/stdc++.h>
#include <ncurses.h>

#define GET_TIME_MS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define IS_CHAR(c, str) (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_' || str.find(c)<str.length()


int ncurses_menu(std::vector<std::string> choices){
    int len = choices.size(), mode;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    // printf("Hello");
    // printf("%d %d", xMax, yMax);
    // int cols = min(len+2, )
    WINDOW *menuwin = newwin(len+2, xMax-3, 2, 2);
    box(menuwin, 0, 0);
    refresh();
    
    
    wrefresh(menuwin);
    keypad(menuwin, true);
    int highlight = 0;
    while(1){
        for(int i=0;i!=len;i++){
            if(((highlight%len)+len)%len == i)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        auto choice = wgetch(menuwin);
        switch(choice){
            case KEY_UP:
                highlight-=1;
                break;
            case KEY_DOWN:
                highlight+=1;
                break;
            default:
                break;   
        }
        if (choice == 10){
            // printf("Here");
            mode = ((highlight%len)+len)%len;
            std::cout << highlight;
            break;
        }
    }
    clear();
    endwin();
    // printf("%d %d", xMax, yMax);
    return mode;
}

std::string ncurses_input_string(std::string prompt_text, bool masked = false, std::string extra_chars = std::string("")){
    if(!masked){
        std::string result;
        
            while(1){
                clear();
                printw("%s%s", prompt_text.c_str(),result.c_str());
                
                refresh(); // Print the prompt
                auto choice = getch();
                if (IS_CHAR(choice, extra_chars)){
                    result.push_back(choice);
                }
                else if (choice == 127) {
                    if(result.size())
                        result.pop_back();
                }
                else if(choice == 10){
                    break;   
                }
            }
            return result;
    }
    else{
        std::string result, result_masked;
        while(1){
                clear();
                printw("%s%s", prompt_text.c_str(),result_masked.c_str());
                refresh(); // Print the prompt
                auto choice = getch();
                if (IS_CHAR(choice, extra_chars)){
                    result.push_back(choice);
                    result_masked.push_back('*');
                }
                else if (choice == 127) {
                    result.pop_back();
                    result_masked.pop_back();
                }
                else if(choice == 10){
                    break;   
                }
            }
            
            return result;
    }

}

void ncurses_flash(std::string message){
    clear();
    printw(message.c_str());
    refresh();
    getch();
}

namespace RaviBank{
    class Bank{
        private:
            class AccountHolder;
            class BankAccountManager;
            class Account;
            enum class TransactionType {
                DEPOSIT,
                WITHDRAW, 
                TRANSFER
            };

            int account_id = 0;
            
            std::string manager_username = "RaviArora", manager_pwd = "ThisIsRavisBank";
            std::vector<AccountHolder*> holders;
            std::vector<Account*> accounts;
        public:
            /*TODO - Remove dependance on manager_username and manager_password*/
            Bank(std::string _manager_username, std::string _manager_pwd):
                manager_username(_manager_username),
                manager_pwd(_manager_pwd),
                bank_manager(manager_username, manager_pwd){};

            /* Account holder functions*/
            bool registerHolder(std::string name, std::string username, std::string pwd);
            bool loginHolder(std::string username, std::string pwd);
            bool loginHolder(int id, std::string pwd);
            bool createAccount(int type);
            
            /*Account manager functions*/
            bool loginManager(std::string username, std::string pwd);

            /*Account functions*/
            bool deposit(int account_no, double amount);
            bool withdraw(int account_no, double amount);
            bool transfer(int account_no, double amount, int receiver_account_no);




            void logout();

            
            

        private:
            bool managerLoggedIn = false;
            AccountHolder* loggedInSession = nullptr;
            
            
            AccountHolder* getAccountHolder(std::string username);
            AccountHolder* getAccountHolder(int account_id);
            
        class BankAccountManager{
            public:
                BankAccountManager(std::string _username, std::string _pwd):
                    username(_username),
                    pwd(_pwd){
                    };
                std::string username;
                std::string pwd;
            private:
                
                
                // static BankAccountManager* manager;
        };
        BankAccountManager bank_manager;
        class Account{
            public:
                Account(int account_no, double balance)
                {
                    this->account_no = account_no;
                    this->balance = balance;
                    this->open_time = GET_TIME_MS;
                };

                

                int get_account_no();
                double get_balance();
                bool deposit(double amount);
                bool transfer(double amount, Account& transfer_account);
                bool withdraw(double amount);


            protected:
                int account_no;
                double balance;
                uint64_t open_time;
                std::vector<std::pair<TransactionType, std::pair<double, uint64_t>>> transaction_history;
                
        };
        class SavingsAccount : public Account {
            public:
                double interest_rate;
        };

        



        class AccountHolder {
            public:
                AccountHolder(int _id, std::string _name, std::string _username, std::string _pwd):
                name(_name),
                id(_id),
                username(_username),
                pwd(_pwd){};

                /*Members*/
                std::string name, username;
                std::string pwd;int id;

                /*SECTION - Methods*/
                
                Account* createAccount(int account_no);
                Account* createAccount(int account_no, double balance);

                Account* getAccount(int account_no);
                std::vector<Account*> getAccounts();
                

                bool changePassword(std::string old_pwd, std::string new_pwd);
                
            private:
                std::vector<Account*> accounts;
        };

        

        AccountHolder* getAccount(std::string username){
            for(auto it:holders){
                if(username == it->username){
                    return it;
                }
            }
        }
        
        // AccountHolder* registerAccount(std::string name, std::string username, std::string pwd){
        //     AccountHolder* new_account = new AccountHolder(account_id++, name, username, pwd);
        //     holders.push_back(new_account);
        // }


    // }    

    // Account* loginCustomer(std::string username, std::string pwd){
    //     if(getAccount(username)->)
    // }

    // class Bank{
    //     public:
    //         Bank(std::string manager_username, std::string manager_pwd):
    //             bank_manager(manager_username, manager_pwd)
    //         {

    //         };
    //         bool loginCustomer();
    //         bool loginManager();
    //         bool createAccount();
    //     private:
    //         BankAccountManager bank_manager;
    //         std::vector<AccountHolder*> holders;


    };

    
    Bank::Account* Bank::AccountHolder::createAccount(int account_no){
            Account* new_account = new Account(account_no, 0);
            accounts.push_back(new_account);
            return new_account;
        }
        Bank::Account* Bank::AccountHolder::createAccount(int account_no, double balance){
            Account* new_account = new Account(account_no, balance);
            accounts.push_back(new_account);
            return new_account;
        }
        Bank::Account* Bank::AccountHolder::getAccount(int account_no){
            for(auto it:this->accounts){
                if(it->get_account_no() == account_no){
                    return it;
                }
            }
            return nullptr;
        }
        std::vector<Bank::Account*> Bank::AccountHolder::getAccounts(){
            return accounts;
        }


        bool Bank::AccountHolder::changePassword(std::string old_pwd, std::string new_pwd){
            if(old_pwd == pwd){
                pwd = new_pwd;
                return true;
            }
            else{
                return false;
            }

        }

        int Bank::Account::get_account_no(){
            return this->account_no;
        };

        double Bank::Account::get_balance(){
            return this->balance;
        }

        bool Bank::Account::deposit(double amount){
            this->balance+=amount;
            transaction_history.push_back({TransactionType::DEPOSIT,{amount, GET_TIME_MS}});
            return true;
        }

        bool Bank::Account::transfer(double amount, Account& transfer_account){
            if(amount <= balance){
                this->balance-=amount;
                transaction_history.push_back({TransactionType::TRANSFER,{amount, GET_TIME_MS}});
                transfer_account.deposit(amount);
                return true;
            }
            else{
                return false;
            }
        }

        bool Bank::Account::withdraw(double amount){
            if(amount <= balance){
                this->balance-=amount;
                transaction_history.push_back({TransactionType::WITHDRAW,{amount, GET_TIME_MS}});
                return true;
            }
            else{
                return false;
            }
        }
        Bank::AccountHolder* Bank::getAccountHolder(std::string username){
            for(auto it:holders){
                if(username == it->username){
                    return it;
                }
            }
            return nullptr;
        }
        Bank::AccountHolder* Bank::getAccountHolder(int id){
            for(auto it:holders){
                if(id == it->id){
                    return it;
                }
            }
            return nullptr;
        }

        bool Bank::registerHolder(std::string name, std::string username, std::string pwd){
            if(getAccountHolder(username) == nullptr){
                auto new_holder = new Bank::AccountHolder(account_id++, name, username, pwd);
                holders.push_back(new_holder);
                return true;
            }
            else{
                return false;
            }
        }
        bool Bank::loginHolder(std::string username, std::string pwd){
            if(getAccountHolder(username) != nullptr){
                if(getAccountHolder(username)->pwd == pwd){
                    loggedInSession = getAccountHolder(username);
                    return true;
                }
                else{
                    return false;
                }
            }
            return false;
        }
        bool Bank::loginHolder(int id, std::string pwd){
            if(getAccountHolder(id) != nullptr){
                if(getAccountHolder(id)->pwd == pwd){
                    loggedInSession = getAccountHolder(id);
                    return true;
                }
                else{
                    return false;
                }
            }
            return false;
        }

        bool Bank::createAccount(int type){
            assert(loggedInSession != nullptr);
            if(type){
                accounts.push_back(loggedInSession->createAccount(account_id++));
                return true;
            }
            else{
                return false;
            }

        }

        bool Bank::loginManager(std::string username, std::string pwd){
            if(bank_manager.username == username && bank_manager.pwd == pwd){
                managerLoggedIn = true;
                return true;
            }
            return false;
        }

        bool Bank::deposit(int account_no, double amount){
            assert(loggedInSession != nullptr);
            Account* account = loggedInSession->getAccount(account_no);
            if(account != nullptr){
                account->deposit(amount);
                return true;
            }
            else{
                return false;
            }

        }
        bool Bank::withdraw(int account_no, double amount){
            assert(loggedInSession != nullptr);
            Account* account = loggedInSession->getAccount(account_no);
            if(account != nullptr){
                return account->withdraw(amount);
            }
            else{
                return false;
            }
        }

        bool Bank::transfer(int account_no, double amount, int receiver_account_no){
            assert(loggedInSession != nullptr);
            Account* account = loggedInSession->getAccount(account_no);
            if(account != nullptr){
                return account->withdraw(amount);
            }
            else{
                return false;
            }
        }

        void Bank::logout(){
            managerLoggedIn = false;
            loggedInSession = nullptr;
        }


}





void cli_client(){
    int mode=0;
    
    // RaviBank::AccountHolder* loggedInHolder = nullptr;
    RaviBank::Bank bank("RaviArora", "password");
    initscr();
    noecho();
    cbreak();

    while(1){
        if (mode == 0){
            mode = 1 + ncurses_menu({"Login as Customer", "Register as New Customer", "Login as Bank Manager", "Quit"});
            printf("Done");
            // break;
        }
        else if (mode == 1){
            std::string username = ncurses_input_string("Username: ");
            std::string password = ncurses_input_string("Password: ");
            if (bank.loginHolder(username, password)){
                ncurses_flash("Login Successful");
                mode = 7;
            }
            else{
                ncurses_flash("Incorrect username or password");
            }

        }
        else if (mode == 2){
            std::string name = ncurses_input_string("Name: ", false, " '");
            if (name == ""){
                ncurses_flash("Empty name not allowed");
            }
            std::string username = ncurses_input_string("Username: ");
            std::string password = ncurses_input_string("Password: ", true, " #!");
            std::string confirm_password = ncurses_input_string("Confirm Password: ", true, " #!");
            if (confirm_password == password){
                mode = 0;
                bank.registerHolder(name, username, password);
                ncurses_flash("Registered succsefully! Proceed to login");
            }
        }
        else if (mode == 7){
            int choice = ncurses_menu({"Go to Acccounts", "Create Another Account","Change Password", "Logout"});
            if(choice == 1){
                int type = ncurses_menu({"Savings", "Current", "Cancel"});
                switch (type){
                    case 0:
                        bank.createAccount(0);
                        break;
                    case 1:
                        bank.createAccount(1);
                        break;
                    case 2:
                        break;
                }
            }
        }
    }
    /* if(mode == 0){
            WINDOW *menuwin = newwin(6, xMax-12, yMax-8, 4);
            box(menuwin, 0, 0);
            refresh();
            
            wrefresh(menuwin);
            keypad(menuwin, true);
            std::string choices[4] = {"LOGIN AS CUSTOMER", "LOGIN AS BANKER", "REGISTER" ,"QUIT"};
            int highlight = 0;
            while(1){
                for(int i=0;i!=4;i++){
                    if(((highlight%4)+4)%4 == i)
                        wattron(menuwin, A_REVERSE);
                    mvwprintw(menuwin, i+1, 1, choices[i].c_str());
                    wattroff(menuwin, A_REVERSE);
                }
                auto choice = wgetch(menuwin);
                switch(choice){
                    case KEY_UP:
                        highlight-=1;
                        break;
                    case KEY_DOWN:
                        highlight+=1;
                        break;
                    default:
                        break;   
                }
                if (choice == 10){
                    printf("Here");
                    mode = ((highlight%4)+4)%4+1;
                    std::cout << highlight;
                    break;
                }
            }
            clear();
            endwin();
            
        }
        if (mode == 1){
            char str[100];
            
            std::string username;
            std::string pwd, pwd_mask;
            while(1){
                clear();
                printw("Enter username: %s", username.c_str());
                refresh(); // Print the prompt
                auto choice = getch();
                if (IS_CHAR(choice)){
                    username.push_back(choice);
                }
                else if (choice == KEY_BACKSPACE) {
                    username.pop_back();
                }
                else if(choice == 10){
                    break;   
                }
            }
            printw(username.c_str());

            while(1){
                clear();

                printw("Enter password: %s", pwd_mask.c_str());
                refresh(); // Print the prompt
                auto choice = getch();
                if (IS_CHAR(choice) || choice == ' '){
                    pwd.push_back(choice);
                    pwd_mask.push_back('*');
                }
                else if (choice == KEY_BACKSPACE) {
                    pwd.pop_back();
                    pwd_mask.pop_back();
                }
                else if(choice == 10){
                    break;   
                }
            }
            printw(pwd.c_str());
            
            
            

            // printw("You entered: %s\n", str);

            refresh(); // Print the entered string
            getch();
            // WINDOW *menuwin = newwin(6, xMax-12, yMax-8, 3);
            // box(menuwin, 0, 0);
            // refresh();
            
            // wrefresh(menuwin);
            // keypad(menuwin, true);
            // std::string choices[2] = {"USERNAME", "PASSWORD"};
            // int highlight = 0;
            // while(1){
            //     for(int i=0;i!=2;i++){
            //         if(((highlight%4)+4)%4 == i)
            //             wattron(menuwin, A_REVERSE);
            //         mvwprintw(menuwin, i+1, 1, choices[i].c_str());
            //         wattroff(menuwin, A_REVERSE);
            //     }
            //     auto choice = wgetch(menuwin);
            //     switch(choice){
            //         case KEY_UP:
            //             highlight-=1;
            //             break;
            //         case KEY_DOWN:
            //             highlight+=1;
            //             break;
            //         default:
            //             break;   
            //     }
            //     if (choice == 10){
            //         printf("Here");
            //         highlight+=1;
            //         break;
            //     }
            // }
            // getch();
            // endwin();
        } */
}

int main() {
    // printf("%d", -1%4);
    
    // cli_client();
    initscr();
    noecho();
    cbreak();
    // std::cout << ncurses_input_string("Enter text: ", false, std::string("_ "));
    cli_client();
    endwin();
    
    // uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // std::cout << ms << " milliseconds since the Epoch\n";
}
