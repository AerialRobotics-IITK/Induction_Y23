#include <bits/stdc++.h>
#include <ncurses.h>
#include <fstream>

#define GET_TIME_MS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define IS_CHAR(c, str) (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_' || str.find(c)<str.length()


int ncurses_menu(std::vector<std::string> choices){
    int len = choices.size(), mode;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
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
                else if(choice == 10 && result.size()){
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
                else if (choice == 127 && result.size()) {
                    result.pop_back();
                    result_masked.pop_back();
                }
                else if(choice == 10 && result.size()){
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

float ncurses_double_input(std::string prompt){
    std::string result;    
    while(1){
        clear();
        printw("%s%s", prompt.c_str(),result.c_str());
        
        refresh(); // Print the prompt
        auto choice = getch();
        if (choice >= '0' && choice <= '9' || choice == '.'){
            if((choice == '.' && std::count(result.begin(), result.end(), '.') <1) || (std::distance(std::find(result.begin(), result.end(), '.'), result.end())<=2))
                result.push_back(choice);
        }
        else if (choice == 127) {
            if(result.size())
                result.pop_back();
        }
        else if(choice == 10 && result.size()){
            break;
        }
    }
    return std::stof(result);
    

}


int ncurses_int_input(std::string prompt){
    std::string result;    
    while(1){
        clear();
        printw("%s%s", prompt.c_str(),result.c_str());
        
        refresh(); // Print the prompt
        auto choice = getch();
        if (choice >= '0' && choice <= '9'){
            if(result.size() < 8)
                result.push_back(choice);
        }
        else if (choice == 127) {
            if(result.size())
                result.pop_back();
        }
        else if(choice == 10 && result.size()){
            break;
        }
    }
    return std::stoi(result);
}



namespace RaviBank{
    class Bank{
        public:
            class AccountHolder;
            class BankAccountManager;
            class Account;
            struct Transaction;
            enum class TransactionType {
                DEPOSIT,
                WITHDRAW, 
                TRANSFER_SEND,
                TRANSFER_RECEIVE
            };
        private:
            
            

            int account_id = 0;
            
            std::string manager_username = "RaviArora", manager_pwd = "ThisIsRavisBank";
            std::vector<AccountHolder*> holders;
            std::vector<Account*> accounts;
            std::vector<Transaction*> bank_transactions;
        public:
            /*TODO - Remove dependance on manager_username and manager_password*/
            Bank(std::string _manager_username, std::string _manager_pwd):
                manager_username(_manager_username),
                manager_pwd(_manager_pwd),
                bank_manager(manager_username, manager_pwd){};

            // Create Bank Object from data file
            Bank(std::string _filepath);


            

            /* Account holder functions*/
            bool registerHolder(std::string name, std::string username, std::string pwd);
            bool loginHolder(std::string username, std::string pwd);
            bool loginHolder(int id, std::string pwd);
            AccountHolder* getLoggedInHolder();
            int createAccount(int type);

            /*Account functions*/
            Account* getAccount(int account_no);


            
            
            /*Account manager functions*/
            bool loginManager(std::string username, std::string pwd);

            /*Account functions*/
            bool deposit(int account_no, double amount);
            bool deposit(Account* account, double amount);
            bool withdraw(int account_no, double amount);
            bool transfer(int account_no, double amount, int receiver_account_no);

            void logout();

            

            
            

        private:
            bool managerLoggedIn = false;
            AccountHolder* loggedInSession = nullptr;
            
            
            AccountHolder* getAccountHolder(std::string username);
            AccountHolder* getAccountHolder(int account_id);
            
        public:
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
                Transaction* deposit(double amount);
                Transaction* withdraw(double amount);
                Transaction* transfer(double amount, Account* transfer_account);
                void receive(double amount, int sender_account_no);

                std::vector<Transaction*> get_statement();



            protected:
                int account_no;
                double balance;
                uint64_t open_time;
                std::vector<std::pair<TransactionType, std::pair<double, uint64_t>>> transaction_history;
                std::vector<Transaction*> transactions;
                
        };
        class SavingsAccount : public Account {
            public:
                SavingsAccount(int _account_no, double _balance):
                    Account(_account_no, _balance)
                {
                    interest_rate = 6;
                };
                double interest_rate;
            
        };

        class CurrentAccount : public Account {
            public:
                CurrentAccount(int _account_no, double _balance):
                    Account(_account_no, _balance)
                {
                    interest_rate = 6;
                };

            private:
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
                
                Account* createAccount(int account_no, int type);
                Account* createAccount(int account_no, double balance, int type);

                Account* getAccount(int account_no);
                std::vector<Account*> getAccounts();
                

                bool changePassword(std::string old_pwd, std::string new_pwd);
                
            private:
                std::vector<Account*> accounts;
        };

        typedef struct Transaction{
            TransactionType tt;
            double amount;
            int64_t timestamp;
            int transaction_owner_account_no;
            int related_account_no; // Using account number since account might be deleted

        } Transaction;
        

        // AccountHolder* getAccount(std::string username){
        //     for(auto it:holders){
        //         if(username == it->username){
        //             return it;
        //         }
        //     }
        // }
        
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

    bool read_data_file(std::string filepath){
        std::ifstream filestream(filepath, std::ios::in);
        std::string line, manager_username, manager_password;
        typedef struct HolderData{
            int _id;
            std::string _name;
            std::string _username;
            std::string _pwd;
        } HolderData;
        std::vector<HolderData> holderData;
        std::vector<int> accountNos;

        bool success = true;
        int line_number = 0;
        while(getline(filestream, line)){
            if(line_number == 0){
                manager_username = line;
            }
            else if(line_number == 1){
                manager_password = line;
            }
            else{
                if(line == "~h"){
                    bool holder_read_success = false;
                    int holder_line = 0;
                    HolderData holder;
                    while(getline(filestream, line)){
                        if(holder_line == 0){
                            try{
                                holder._id = std::stoi(line);
                                accountNos.push_back(holder._id);
                            }
                            catch(std::exception err){
                                return false;
                            }
                        }
                        else if(holder_line == 1){
                            try{
                                /*TODO - Verify name*/
                                holder._name = line;
                            }
                            catch(std::exception err){
                                return false;
                            }
                        }
                        else if(holder_line == 2){
                            try{
                                /*TODO - Verify name*/
                                holder._username = line;
                            }
                            catch(std::exception err){
                                return false;
                            }
                        }
                        else if(holder_line == 3){
                            try{
                                /*TODO - Verify name*/
                                holder._username = line;
                                holder_read_success = true;
                                break;
                            }
                            catch(std::exception err){
                                return false;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    if(!holder_read_success){
                        holderData.push_back(holder);
                        return false;
                    }
                }
                else if(line == "~a"){

                }
            }
        }
    }

    // Bank::Bank(std::string _filepath){
        
    // }

    
    Bank::Account* Bank::AccountHolder::createAccount(int account_no, int type = 0){
            if(type == 0){
                Account* new_account = new Account(account_no, 0);
                accounts.push_back(new_account);
                return new_account;
            }
            else{
                SavingsAccount* new_account = new SavingsAccount(account_no, 0);
                accounts.push_back(new_account);
                return new_account;
            }
        }
        Bank::Account* Bank::AccountHolder::createAccount(int account_no, double balance, int type = 0){
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

        Bank::Transaction* Bank::Account::deposit(double amount){
            this->balance+=amount;
            transaction_history.push_back({TransactionType::DEPOSIT,{amount, GET_TIME_MS}});
            Transaction* transaction = new Transaction{TransactionType::DEPOSIT, amount, GET_TIME_MS, this->account_no, -1};
            transactions.push_back(transaction);
            return transaction;
        }

        Bank::Transaction* Bank::Account::transfer(double amount, Account* transfer_account){
            if(amount <= balance){
                this->balance-=amount;
                transaction_history.push_back({TransactionType::TRANSFER_SEND,{amount, GET_TIME_MS}});
                transfer_account->receive(amount, this->account_no);
                Transaction* transaction = new Transaction{TransactionType::TRANSFER_SEND, amount, GET_TIME_MS, this->account_no, transfer_account->get_account_no()};
                return transaction;
            }
            else{
                return nullptr;
            }
        }

        void Bank::Account::receive(double amount, int sender_account_no){
            this->balance+=amount;
            transaction_history.push_back({TransactionType::TRANSFER_RECEIVE,{amount, GET_TIME_MS}});
        }

        Bank::Transaction* Bank::Account::withdraw(double amount){
            if(amount <= balance){
                this->balance-=amount;
                transaction_history.push_back({TransactionType::WITHDRAW,{amount, GET_TIME_MS}});
                Transaction* transaction = new Transaction{TransactionType::WITHDRAW, amount, GET_TIME_MS, this->account_no, -1};
                transactions.push_back(transaction);
                return transaction;
            }
            else{
                return nullptr;
            }
        }

        std::vector<Bank::Transaction*> Bank::Account::get_statement(){
            return this->transactions;
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

        int Bank::createAccount(int type){
            assert(loggedInSession != nullptr);
            accounts.push_back(loggedInSession->createAccount(account_id++));
            return account_id-1;
        }

        Bank::Account* Bank::getAccount(int account_no){
            for(auto it:accounts){
                if(it->get_account_no() == account_no){
                    return it;
                }
            }
            return nullptr;
        }

        bool Bank::loginManager(std::string username, std::string pwd){
            if(bank_manager.username == username && bank_manager.pwd == pwd){
                managerLoggedIn = true;
                return true;
            }
            return false;
        }

        Bank::AccountHolder* Bank::getLoggedInHolder(){
            return this->loggedInSession;
        };

        bool Bank::deposit(int account_no, double amount){
            assert(loggedInSession != nullptr);
            Account* account = loggedInSession->getAccount(account_no);
            if(account != nullptr){
                auto transaction = account->deposit(amount);
                this->bank_transactions.push_back(transaction);
                return true;
            }
            else{
                return false;
            }

        }

        bool Bank::deposit(Account* account, double amount){
            assert(loggedInSession != nullptr);
            
            if(std::find(loggedInSession->getAccounts().begin(), loggedInSession->getAccounts().end() , account)!=loggedInSession->getAccounts().end()){
                auto transaction = account->deposit(amount);
                this->bank_transactions.push_back(transaction);
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
                auto transaction = account->withdraw(amount);
                if(transaction != nullptr){
                    this->bank_transactions.push_back(transaction);
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }

        bool Bank::transfer(int account_no, double amount, int receiver_account_no){
            assert(loggedInSession != nullptr);
            Account* account = loggedInSession->getAccount(account_no);
            Account* receiver_account = this->getAccount(receiver_account_no);
            if(account != nullptr && receiver_account != nullptr){
                auto transaction = account->transfer(amount, receiver_account);
                if(transaction != nullptr){
                    this->bank_transactions.push_back(transaction);
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }

        void Bank::logout(){
            managerLoggedIn = false;
            loggedInSession = nullptr;
        }
        std::vector<std::string> generate_statement_table(std::vector<Bank::Transaction*> transactions){
            const int num_cols = 5;
            std::vector<int> col_lengths(num_cols);
            std::vector<std::string> lines;
            std::vector<std::vector<std::string>> cols_coll;
            cols_coll.push_back({"Transaction Type", "Transaction Amount", "Timestamp", "Initiated Account No.", "Associated Account No."});
            for(int i =0;i!=5;i++){
                col_lengths[i] = cols_coll[0][i].size();
            }
            for(auto it:transactions){
                std::vector<std::string> cols(5);
                switch (it->tt){
                    case Bank::TransactionType::DEPOSIT:
                        cols[0] = "Deposit";
                        break;
                    case Bank::TransactionType::WITHDRAW:
                        cols[0] = "Withdraw";
                        break;
                    case Bank::TransactionType::TRANSFER_SEND:
                        cols[0] = "Transfer";
                        break;
                }
                char amt_str[15];
                snprintf(amt_str, 15, "%.2f", it->amount);
                cols[1] = std::string(amt_str);

                char timestamp_str[20];
                snprintf(timestamp_str, 20, "%ld", it->timestamp);
                cols[2] = std::string(timestamp_str);

                char acc_str_1[15];
                snprintf(acc_str_1, 20, "%d", it->transaction_owner_account_no);
                cols[3] = std::string(acc_str_1);

                
                if(it->related_account_no != -1){
                    char acc_str_2[15];
                    snprintf(acc_str_2, 20, "%d", it->related_account_no);
                    cols[4] = std::string(acc_str_2);
                }
                else{
                    cols[4] = "-";
                }
                
                std::ostringstream line;
                line << cols[0] << " " << cols[1] << " " << cols[2] << " " << cols[3] << " " << cols[4];
                // lines.push_back(line.str());
                cols_coll.push_back(cols);
                for(int i=0;i<5;i++){
                    col_lengths[i] = std::max(col_lengths[i], int(cols[i].size()));
                }
            }
            // std::string new_lines;
            for(auto it:cols_coll){
                char temp_buff[200];
                printf("Here");
                std::cout << "Here\n";
                // printf("%s\n", it[0].c_str());
                int space_sep = 4;
                snprintf(temp_buff, 200, "%*s%*s%*s%*s%*s%*s%*s%*s%*s", col_lengths[0],it[0].c_str(), space_sep, "", col_lengths[1],it[1].c_str(), space_sep, "" ,col_lengths[2],it[2].c_str(), space_sep, "", col_lengths[3],it[3].c_str(), space_sep, "", col_lengths[4],it[4].c_str());
                lines.push_back(std::string(temp_buff));
                // snprintf(temp_buff, 200, "%*s%s", );

            }

            return lines;
        }


}





void cli_client(){
    int mode=0;
    
    // RaviBank::AccountHolder* loggedInHolder = nullptr;
    RaviBank::Bank bank("RaviArora", "password");
    RaviBank::Bank::Account acct(10, 11);
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
            if(choice == 0){
                auto accounts = bank.getLoggedInHolder()->getAccounts();
                std::vector<std::string> menu_data = {"... Go Back"};
                for(auto it:accounts){
                    menu_data.push_back(std::string("Account No:")+std::to_string(it->get_account_no()));
                }
                int account_index = ncurses_menu(menu_data)-1;
                if(account_index+1){
                    auto account = accounts[account_index];
                    int account_action = ncurses_menu({"View Statement","View Balance", "Deposit", "Withdraw", "Transfer", "Close Account", "Cancel"});
                    account_action-=2;
                    if(account_action == -2){
                        std::cout << std::endl << std::endl;
                        ncurses_menu(RaviBank::generate_statement_table(account->get_statement()));
                        // for(auto it:RaviBank::generate_statement_table(account->get_statement())){
                        //     std::cout << it << std::endl;
                        // }
                        // return;

                    }
                    else if(account_action == -1){
                        char temp[100];
                        snprintf(temp, 100, "Balance: %.2f", account->get_balance());
                        ncurses_flash(temp);
                    }
                    else if(account_action == 0){
                        float amount = ncurses_double_input("Deposit amount: ");
                        if(bank.deposit(account, amount)){
                            char temp[100];
                            snprintf(temp, 100, "Successfully deposited %.2f", amount);
                            ncurses_flash(temp);
                        }
                        else{
                            ncurses_flash("Uh oh, unable to deposit to this account");
                        }
                    }
                    else if(account_action == 1){
                        float amount = ncurses_double_input("Withdraw amount: ");
                        if(bank.withdraw(account->get_account_no(), amount)){
                            char temp[100];
                            snprintf(temp, 100, "Successfully withdrew %.2f", amount);
                            ncurses_flash(temp);
                        }
                        else{
                            ncurses_flash("Unable to withdraw this amount. Ensure that you have enough balance");
                        }
                    }
                    else if(account_action == 2){
                        int transfer_account_no =  ncurses_int_input("Enter Receiver's Account number: ");
                        float amount = ncurses_double_input("Transfer amount: ");
                        if(bank.transfer(account->get_account_no(), amount, transfer_account_no)){
                            char temp[100];
                            snprintf(temp, 100, "Successfully transferred %.2f to account no. %d", amount, transfer_account_no);
                            ncurses_flash(temp);
                        }
                        else{
                            ncurses_flash("Failed to transfer. Ensure you have sufficient balance and the receivers account number is correct.");
                        }
                    }
                }
                
            }
            if(choice == 1){
                int type = ncurses_menu({"Savings", "Current", "Cancel"});
                int acc;
                switch (type){
                    case 0:
                        acc = bank.createAccount(0);
                        if(acc != -1){
                            ncurses_flash(std::string("Account created succesfully, account number is ")+ std::to_string(acc));
                        }
                        break;
                    case 1:
                        acc = bank.createAccount(0);
                        if(acc != -1){
                            ncurses_flash(std::string("Account created succesfully, account number is ")+ std::to_string(acc));
                        }
                        break;
                    case 2:
                        break;
                }
            }
            if(choice == 2){
                std::string old_password = ncurses_input_string("Old Password: ", true, " #!"); 
                std::string password = ncurses_input_string("New Password: ", true, " #!");
                std::string confirm_password = ncurses_input_string("Confirm Password: ", true, " #!");
                if (confirm_password == password){
                    if(bank.getLoggedInHolder()->changePassword(old_password, confirm_password)){
                        ncurses_flash("Password changed succsefully!");
                    }
                    else{
                        ncurses_flash("Failed to change password, old password doesn't match");
                    }
                    
                }
                else{
                    ncurses_flash("Confirmed password doesn't match, try again");
                    
                }
                
            }
            if(choice == 3){
                mode = 0;
                bank.logout();
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

int main(){
    initscr();
    noecho();
    cbreak();
    // printf("%*s", 6,"HelloRavi");
    try{
        std::cout << std::stoi("134f"); 
    }
    catch(std::exception err){
        printf("Hello");
    }
    // cli_client();
    endwin();
}
