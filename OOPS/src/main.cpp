#include <bits/stdc++.h>
#include <ncurses.h>

#define GET_TIME_MS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define IS_CHAR(c) (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_'
namespace RaviBank{
    // class Bank{
        // public:
        class AccountHolder;
        class BankAccountManager;
        int account_id = 0;
        std::string manager_username = "RaviArora", manager_pwd = "ThisIsRavisBank";
        std::vector<AccountHolder*> holders;

        enum class TransactionType {
            DEPOSIT,
            WITHDRAW, 
            TRANSFER
        };


        class BankAccountManager{
            public:
                static BankAccountManager *get_instance(){
                    if (manager == nullptr)
                    {
                        manager = new BankAccountManager();
                    }
                    return manager;
                };
            private:
                BankAccountManager();
                std::string username;
                std::string pwd;
                static BankAccountManager* manager;
        };
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

        int Account::get_account_no(){
            return this->account_no;
        };

        double Account::get_balance(){
            return this->balance;
        }

        bool Account::deposit(double amount){
            this->balance+=amount;
            transaction_history.push_back({TransactionType::DEPOSIT,{amount, GET_TIME_MS}});
            return true;
        }

        bool Account::transfer(double amount, Account& transfer_account){
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

        bool Account::withdraw(double amount){
            if(amount <= balance){
                this->balance-=amount;
                transaction_history.push_back({TransactionType::WITHDRAW,{amount, GET_TIME_MS}});
                return true;
            }
            else{
                return false;
            }
        }



        class AccountHolder {
            public:
                AccountHolder(int _id, std::string _name, std::string _username, std::string _pwd):
                name(_name),
                id(_id),
                username(_username),
                pwd(_pwd){};
                std::vector<Account*> getAccounts();
                Account* createAccount(int account_no);
                Account* createAccount(int account_no, double balance);
                bool changePassword(std::string old_pwd, std::string new_pwd);
            private:
                int id;
                std::string name, username;
                std::string pwd;
                std::vector<Account*> accounts;
        };

        Account* AccountHolder::createAccount(int account_no){
            Account* new_account = new Account(account_no, 0);
            accounts.push_back(new_account);
            return new_account;
        }
        Account* AccountHolder::createAccount(int account_no, double balance){
            Account* new_account = new Account(account_no, balance);
            accounts.push_back(new_account);
            return new_account;
        }
        std::vector<Account*> AccountHolder::getAccounts(){
            return accounts;
        }
        bool AccountHolder::changePassword(std::string old_pwd, std::string new_pwd){
            if(old_pwd == pwd){
                pwd = new_pwd;
                return true;
            }
            else{
                return false;
            }

        }

        AccountHolder* getAccount(std::string username){
            for(auto it:holders){
                if(username == it->username){
                    return it;
                }
            }
        }
        
        AccountHolder* registerAccount(std::string name, std::string username, std::string pwd){
            AccountHolder* new_account = new AccountHolder(account_id++, name, username, pwd);
            holders.push_back(new_account);
        }

        AccountHolder* loginAccount(std::string username, std::string pwd){

        }

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


    // };

}




void cli_client(){
    int mode=0;
    
    RaviBank::AccountHolder* loggedInHolder = nullptr;

    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    if(mode == 0){
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
        }
}

int main() {
    // printf("%d", -1%4);
    
    cli_client();
    // uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // std::cout << ms << " milliseconds since the Epoch\n";
}
