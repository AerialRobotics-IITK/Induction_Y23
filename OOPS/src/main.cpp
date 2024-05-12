#include <bits/stdc++.h>
#include <ncurses.h>
#include <fstream>
#include <ctime>
#include <cmath>


#define GET_TIME time(NULL) + owner_bank->time_offset
#define DURATION_YEAR (365*DURATION_DAY)
#define DURATION_DAY 86400L
#define GET_TIME_MS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define IS_CHAR(c, str) (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_' || str.find(c)<str.length()
// #define POI printf("%d\n", __LINE__);
#define POI printf("i");

int ncurses_menu(std::vector<std::string> choices, bool heading = false, std::string prompt = ""){
    int len = choices.size(), mode;
    int xMax, yMax;
    clear();
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *menuwin = newwin(len+2, xMax-3, 2, 2);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);
    int highlight = 0;
    if(!heading){
    while(1){
        if(len){
            mvwprintw(menuwin, len+1, 1, prompt.c_str());
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
        else{
            getch();
            return -1;
            break;
        }
    }
    clear();
    endwin();
    // printf("%d %d", xMax, yMax);
    return mode;
    }
    else{
    len-=1;
    while(1){
        wattron(menuwin, A_REVERSE);
        mvwprintw(menuwin, len+2, 1, prompt.c_str());
        wattroff(menuwin, A_REVERSE);
        mvwprintw(menuwin, 0, 1, choices[0].c_str());
        if(len){
            for(int i=1;i<=len;i++){
                if(((highlight%len)+len)%len == i-1)
                    wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i, 1, choices[i].c_str());
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
                
                mode = ((highlight%len)+len)%len;
                
                break;
            }
        }
        else{
            getch();
            return -1;
            break;
        }
    }
    clear();
    endwin();
    return mode;
    }
}

std::string ncurses_input_string(std::string prompt_text, bool masked = false, std::string extra_chars = std::string("")){
    if(!masked){
        std::string result;
        
            while(1){
                clear();
                printw("%s%s", prompt_text.c_str(),result.c_str());
                
                refresh(); 
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
                refresh(); 
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

void ncurses_flash(std::string message, bool wait_key = true){
    clear();
    printw(message.c_str());
    refresh();
    if(wait_key){
        getch();
    }
}

double ncurses_double_input(std::string prompt){
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
    std::cout << "Result" << std::stod(result);
    return std::stod(result);
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



namespace WorldBank{
    
    
    double interest_rate_func(double balance){
        return 2.0 + 8.0*atan(balance/1000)/(2*M_PI);  
    }

    double compound_calculator(double balance, double rate, time_t duration, time_t compound_duration){
        int compounds = duration/compound_duration;
        std::cout << "Compounds: " << compounds << std::endl;
        
        return balance*pow(1+(rate/100), compounds);
        
    }
    class Bank{
        public:
            class AccountHolder;
            class BankAccountManager;
            class Account;

            enum class AccountType{
                SAVINGS,
                CURRENT
            };

            struct Transaction;
            enum class TransactionType {
                DEPOSIT,
                WITHDRAW, 
                TRANSFER,
                TRANSFER_RECEIVE
            };
            /*TODO - Move these to private*/
            std::string manager_username ,manager_pwd;
            std::vector<AccountHolder*> holders;
            std::vector<Account*> accounts;
            time_t time_offset = 0;
            
        private:
            int account_id = 0;
            std::vector<Transaction*> bank_transactions;
            static Bank* instance;
            // static Bank* instance;
            


        public:
            /*TODO - Remove dependance on manager_username and manager_password*/
            Bank(std::string _manager_username, std::string _manager_pwd):
                manager_username(_manager_username),
                manager_pwd(_manager_pwd),
                bank_manager(manager_username, manager_pwd, this){
                    /*TODO - Try to make it safer*/
                    // if(instance != nullptr){
                    //     delete instance;
                    // }
                    // instance = this;
                };

            // Create Bank Object from data file
            Bank(std::string _filepath);
            void fast_forward(time_t duration){
                this->time_offset += duration;
                std::cout << "Over" << "";
                for(auto it:accounts){
                    auto savings_ptr = dynamic_cast<SavingsAccount*>(it);
                    
                    if(savings_ptr!=nullptr){
                        savings_ptr->fast_forward_update();
                    }
                }
            }

            std::vector<Transaction*> get_transactions(){
                return this->bank_transactions;
            };


            // static Bank* get_instance(){
            //     return instance;
            // };
            /*File related*/
            bool write_to_file();

            bool loadHolder(int id, std::string name, std::string username, std::string pwd);
            bool load_account(int account_no, int owner_account_id, double balance, time_t timestamp, AccountType type);



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
                BankAccountManager(std::string _username, std::string _pwd, Bank* owner_bank):
                    username(_username),
                    pwd(_pwd){
                    };
                std::string username;
                std::string pwd;
                std::vector<std::string> generate_account_table(std::vector<Bank::Account*> accounts);
            private:
                Bank* owner_bank;
                
                
                
                // static BankAccountManager* manager;
        };
        BankAccountManager bank_manager;
        class Account{
            public:
                Account(int _account_no, double _balance, int _owner_account_id, Bank* _owner) :
                    account_no(_account_no), balance(_balance), owner_account_id(_owner_account_id), owner_bank(_owner)
                {
                    this->open_time = GET_TIME;
                    interest_rate = 0;
                };

                virtual AccountType get_account_type(){
                    return this->account_type;
                };
                virtual double get_interest_rate(){
                    return 0;
                };

                int get_account_no();
                double get_balance();
                Transaction* deposit(double amount);
                Transaction* withdraw(double amount);
                Transaction* transfer(double amount, Account* transfer_account);
                void receive(double amount, int sender_account_no, Transaction* transaction);
                std::vector<Transaction*> get_statement();





            protected:
                
                AccountType account_type;
                int account_no, owner_account_id;
                double balance;
                time_t open_time;
                Bank* owner_bank;
                double interest_rate = 0;
                std::vector<std::pair<TransactionType, std::pair<double, time_t>>> transaction_history;
                std::vector<Transaction*> transactions;
                
            friend class Bank;
            friend class BankAccountManager;
        };
        class SavingsAccount : public Account {
            public:
                SavingsAccount(int _account_no, double _balance, int _owner_account_id, Bank* owner):
                    Account(_account_no, _balance, _owner_account_id, owner)
                {
                    update_interest_rate();
                    this->last_updated = this->open_time;
                };
                void update_interest_rate(){
                    interest_rate = WorldBank::interest_rate_func(balance);
                }
                double get_interest_rate() override{
                    return interest_rate;
                }

                void fast_forward_update(){
                    
                    time_t virtual_time = GET_TIME;
                    time_t time_diff = virtual_time - last_updated;
                    balance = compound_calculator(balance, this->interest_rate, time_diff, DURATION_YEAR);
                    // std::cout << "\n Over here too: New Balance:" << balance << "\n Interest Rate:" << this->interest_rate  << std::endl;
                    
                    last_updated = last_updated + (time_diff/DURATION_YEAR) * DURATION_YEAR;
                };
            private:
                time_t last_updated;
                double interest_rate;
                
            
        };

        class CurrentAccount : public Account {
            public:
                CurrentAccount(int _account_no, double _balance, int _owner_account_id, Bank* _owner):
                    Account(_account_no, _balance, _owner_account_id, _owner)
                {
                    interest_rate = 0;
                };

            private:
                double interest_rate;
            
        };

        



        class AccountHolder {
            public:
                AccountHolder(int _id, std::string _name, std::string _username, std::string _pwd, Bank* _owner):
                name(_name),
                id(_id),
                username(_username),
                pwd(_pwd), owner_bank(_owner){};

                /*Members*/
                int id;
                std::string name, username;
                std::string pwd;
                

                /*SECTION - Methods*/
                
                Account* createAccount(int account_no, AccountType type);
                Account* createAccount(int account_no, double balance, AccountType type);

                Account* getAccount(int account_no);
                std::vector<Account*> getAccounts();
                

                bool changePassword(std::string old_pwd, std::string new_pwd);
                
            private:
                Bank* owner_bank;
                std::vector<Account*> accounts;

            friend class Bank;
        };

        typedef struct Transaction{
            TransactionType tt;
            double amount;
            time_t timestamp;
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

    
    
    Bank* read_data_file(std::string filepath){
        std::ifstream filestream(filepath, std::ios::in);
        std::string line, manager_username, manager_password;
        typedef struct HolderData{
            int _id;
            std::string _name;
            std::string _username;
            std::string _pwd;
        } HolderData;

        typedef struct Accountdata{
            int _account_no, _owner_account_id;
            double _balance;
            time_t _open_time;
            
        } AccountData;
        std::vector<HolderData> holder_data;
        std::vector<AccountData> account_data;
        std::vector<int> accountNos;

        bool success = true;
        int line_number = -1;
        
        while(getline(filestream, line)){
            line_number++;
            if(line_number == 0){
                manager_username = line;
                // std::cout << manager_username << std::endl;
            }
            else if(line_number == 1){
                manager_password = line;
                
            }
            else{
                POI
                if(line == "~h"){
                    bool holder_read_success = false;
                    int holder_line = -1;
                    HolderData holder;
                    while(getline(filestream, line)){
                        holder_line++;
                        if(holder_line == 0){
                            try{
                                holder._id = std::stoi(line);
                                accountNos.push_back(holder._id);
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(holder_line == 1){
                            try{
                                /*TODO - Verify name*/
                                holder._name = line;
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(holder_line == 2){
                            try{
                                /*TODO - Verify name*/
                                holder._username = line;
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(holder_line == 3){
                            try{
                                /*TODO - Verify name*/
                                holder._pwd = line;
                                holder_read_success = true;
                                break;
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    if(holder_read_success){
                        holder_data.push_back(holder);
                    }
                    else{
                        POI
                        return nullptr;
                    }
                }
                else if(line == "~a"){
                    bool account_read_success = false;
                    int account_reader_line = -1;
                    AccountData account;
                    while(getline(filestream, line)){
                        account_reader_line ++;
                        printf("%d\n", account_reader_line);
                        POI
                        if(account_reader_line == 0){
                            try{
                                account._account_no = std::stoi(line);
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(account_reader_line == 1){
                            try{
                                /*TODO - Verify name*/
                                account._owner_account_id = std::stoi(line);
                                if(std::find(accountNos.begin(), accountNos.end(), account._owner_account_id) == accountNos.end()){
                                    
                                    throw;
                                }
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(account_reader_line == 2){
                            try{
                                /*TODO - Verify name*/
                                account._balance = std::stod(line);
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                        }
                        else if(account_reader_line == 3){
                            POI
                            try{
                                /*TODO - Verify name*/
                                account._open_time = std::stol(line);
                            }
                            catch(std::exception err){
                                POI
                                return nullptr;
                            }
                            account_read_success = true;
                            break;
                        }
                        else{
                            POI
                            break;
                        }
                    }
                    POI
                    if(account_read_success){
                        POI
                        account_data.push_back(account);
                    }
                    else{
                        POI
                        return nullptr;
                    }
                }
                else{
                    break;
                }
            }
        }
        POI
        Bank* bank_ptr = new Bank(manager_username, manager_password);
        for(auto it:holder_data){
            POI
            bank_ptr->loadHolder(it._id, it._name, it._username, it._pwd);
        }
        for(auto it:account_data){
            POI
            bank_ptr->load_account(it._account_no, it._owner_account_id, it._balance, it._open_time, Bank::AccountType::CURRENT);
            POI
        }
        POI
        return bank_ptr;
    }

    // Bank::Bank(std::string _filepath){
        
    // }

    
    Bank::Account* Bank::AccountHolder::createAccount(int account_no, AccountType type){
            // if(type == 0){
            //     Account* new_account = new Account(account_no, 0, this->id);
            //     accounts.push_back(new_account);
            //     return new_account;
            // }
            // else{
                Account* new_account;
                if(type == AccountType::SAVINGS){
                    new_account = new SavingsAccount(account_no, 0, this->id, this->owner_bank);
                }
                else{
                    new_account = new CurrentAccount(account_no, 0, this->id, this->owner_bank);
                }
                accounts.push_back(new_account);
                return new_account;
            // }
        }
        Bank::Account* Bank::AccountHolder::createAccount(int account_no, double balance, AccountType type){
            Account* new_account;
            if(type == AccountType::SAVINGS){
                new_account = new SavingsAccount(account_no, 0, this->id, this->owner_bank);
            }
            else{
                new_account = new CurrentAccount(account_no, 0, this->id, this->owner_bank);
            }
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
            if((dynamic_cast<Bank::SavingsAccount*>(this) != nullptr)){
                dynamic_cast<Bank::SavingsAccount*>(this)->update_interest_rate();
            }
            transaction_history.push_back({TransactionType::DEPOSIT,{amount, GET_TIME}});
            Transaction* transaction = new Transaction{TransactionType::DEPOSIT, amount, GET_TIME, this->account_no, -1};
            transactions.push_back(transaction);
            return transaction;
        }

        Bank::Transaction* Bank::Account::transfer(double amount, Account* transfer_account){
            if(amount <= balance){
                this->balance-=amount;
                if((dynamic_cast<Bank::SavingsAccount*>(this) != nullptr)){
                    dynamic_cast<Bank::SavingsAccount*>(this)->update_interest_rate();
                }
                // transaction_history.push_back({TransactionType::TRANSFER_SEND,{amount, GET_TIME}});
                
                Transaction* transaction = new Transaction{TransactionType::TRANSFER, amount, GET_TIME, this->account_no, transfer_account->get_account_no()};
                transactions.push_back(transaction);
                transfer_account->receive(amount, this->account_no, transaction);
                return transaction;
            }
            else{
                return nullptr;
            }
        }

        void Bank::Account::receive(double amount, int sender_account_no, Transaction* transaction){
            this->balance+=amount;
            if((dynamic_cast<Bank::SavingsAccount*>(this) != nullptr)){
                dynamic_cast<Bank::SavingsAccount*>(this)->update_interest_rate();
            }
            // transaction_history.push_back(transaction);
            transactions.push_back(transaction);
        }

        Bank::Transaction* Bank::Account::withdraw(double amount){
            if(amount <= balance){
                this->balance-=amount;
                if((dynamic_cast<Bank::SavingsAccount*>(this) != nullptr)){
                    dynamic_cast<Bank::SavingsAccount*>(this)->update_interest_rate();
                }
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

        bool Bank::write_to_file(){
            std::ofstream file;
            try{
                file.open("./.bankdata", std::ios_base::out | std::ios_base::trunc);
            }
            catch(std::exception err){
                return false;
            }

            file << this->manager_username << std::endl;
            file << this->manager_pwd << std::endl;
            for(auto it:this->holders){
                file << "~h" << std::endl;
                file << it->id << std::endl;
                file << it->name << std::endl;
                file << it->username << std::endl;
                file << it->pwd << std::endl;
            }
            for(auto it:this->accounts){
                file << "~a" << std::endl;
                file << it->account_no << std::endl;
                file << it->owner_account_id << std::endl;
                file << it->balance << std::endl;
                file << it->open_time << std::endl;
            }
            
            file.close();
            return true;
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
        /*TODO - registration id*/
        bool Bank::loadHolder(int id, std::string name, std::string username, std::string pwd){
            if(getAccountHolder(username) == nullptr){
                auto new_holder = new Bank::AccountHolder(id, name, username, pwd, this);
                holders.push_back(new_holder);
                return true;
            }
            else{
                return false;
            }
        }

        bool Bank::load_account(int account_no, int owner_account_id, double balance, int64_t timestamp, AccountType type){
            Account* new_account = new SavingsAccount(account_no, balance, owner_account_id, this);
            new_account->open_time = timestamp;
            this->getAccountHolder(owner_account_id)->accounts.push_back(new_account);
            this->accounts.push_back(new_account);
            return true;
        }

        bool Bank::registerHolder(std::string name, std::string username, std::string pwd){
            if(getAccountHolder(username) == nullptr){
                while(getAccount(account_id)!=nullptr){
                    account_id++;
                }
                auto new_holder = new Bank::AccountHolder(account_id, name, username, pwd, this);
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
            while(getAccount(account_id)!=nullptr){
                account_id++;
            }
            if(type == 0){
                accounts.push_back(loggedInSession->createAccount(account_id, AccountType::SAVINGS));
            }
            else{
                accounts.push_back(loggedInSession->createAccount(account_id, AccountType::CURRENT));
            }
            
            return account_id;
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
            printf("970");
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
        std::vector<std::string> generate_holder_table(std::vector<Bank::AccountHolder*> holders){
            POI
            const int num_cols = 3;
            std::vector<int> col_lengths(num_cols);
            std::vector<std::string> lines;
            std::vector<std::vector<std::string>> cols_coll;
            cols_coll.push_back({"Account ID", "Name", "Username"});
            
            for(int i =0;i!=num_cols;i++){
                col_lengths[i] = cols_coll[0][i].size();
            }
            for(auto it:holders){
                std::vector<std::string> cols(num_cols);
                
                char id_str[15];
                snprintf(id_str, 15, "%d", it->id);
                cols[0] = std::string(id_str);
                cols[1] = std::string(it->name);
                cols[2] = std::string(it->username);
                
                // std::ostringstream line;
                // line << cols[0] << " " << cols[1] << " " << cols[2] << " " << cols[3] << " " << cols[4];
                
                cols_coll.push_back(cols);
                for(int i=0;i<num_cols;i++){
                    col_lengths[i] = std::max(col_lengths[i], int(cols[i].size()));
                }
                
            }
            
            for(auto it:cols_coll){
                char temp_buff[200];
                
                int space_sep = 4;
                snprintf(temp_buff, 200, "%*s%*s%*s%*s%*s", col_lengths[0],it[0].c_str(), space_sep, "", col_lengths[1],it[1].c_str(), space_sep, "" ,col_lengths[2],it[2].c_str());
                
                lines.push_back(std::string(temp_buff));

            }
            
            return lines;
        }

        std::vector<std::string> Bank::BankAccountManager::generate_account_table(std::vector<Bank::Account*> accounts){
            const int num_cols = 6;
            std::vector<int> col_lengths(num_cols);
            std::vector<std::string> lines;
            std::vector<std::vector<std::string>> cols_coll;
            cols_coll.push_back({"Account Type", "Account No", "Holder ID", "Balance", "Interest Rate", "Opening Timestamp"});
            for(int i =0;i!=num_cols;i++){
                col_lengths[i] = cols_coll[0][i].size();
            }
            for(auto it:accounts){
                std::vector<std::string> cols(num_cols);
                
                // TODO - if(is_savings)
                bool savings = false;
                if(dynamic_cast<Bank::SavingsAccount*>(it) != nullptr){
                    savings = true;
                    cols[0] = std::string("Savings");
                }
                else{
                    cols[0] = std::string("Current/Checking");
                }
                
                
                char account_no_str[20];
                snprintf(account_no_str, 20, "%d", it->account_no);

                char id_str[20];
                snprintf(id_str, 20, "%d", it->owner_account_id);

                char interest_rate_str[20];
                if(savings){
                    std::cout << "Savings:" << dynamic_cast<Bank::SavingsAccount*>(it)->get_interest_rate() << std::endl;
                    snprintf(interest_rate_str, 20, "%.2f", dynamic_cast<Bank::SavingsAccount*>(it)->get_interest_rate());
                }
                else{
                    snprintf(interest_rate_str, 20, "%.2f", dynamic_cast<Bank::CurrentAccount*>(it)->get_interest_rate());
                }
                
                char balance_str[20];
                snprintf(balance_str, 20, "%.2f", it->balance);

                // TODO - time
                char time_str[40];
                auto tmr = localtime(&it->open_time);
                strftime(time_str, 40, "%c", tmr);
                // snprintf(time_str, 40, "%ld", it->open_time);
                POI
                cols[1] = std::string(account_no_str);
                cols[2] = std::string(id_str);
                cols[3] = std::string(balance_str);
                cols[4] = std::string(interest_rate_str);
                cols[5] = std::string(time_str);
                
                
                cols_coll.push_back(cols);
                for(int i=0;i<num_cols;i++){
                    col_lengths[i] = std::max(col_lengths[i], int(cols[i].size()));
                }
            }

            for(auto it:cols_coll){
                char temp_buff[1000];
                
                int space_sep = 4;
                snprintf(temp_buff, 1000, "%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s", col_lengths[0],it[0].c_str(), space_sep, "", col_lengths[1],it[1].c_str(), space_sep, "" ,col_lengths[2],it[2].c_str(), space_sep, "", col_lengths[3],it[3].c_str(), space_sep, "", col_lengths[4],it[4].c_str(), space_sep, "", col_lengths[5],it[5].c_str());
                
                // snprintf(temp_buff, 200, "%*s%*s%*s%*s%*s", col_lengths[0],it[0].c_str(), space_sep, "", col_lengths[1],it[1].c_str(), space_sep, "" ,col_lengths[2],it[2].c_str());
                lines.push_back(std::string(temp_buff));
                

            }
            POI
            return lines;
        }
        bool is_saving(Bank::Account* acct){
            return (dynamic_cast<Bank::SavingsAccount*>(acct) == nullptr);
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
                    case Bank::TransactionType::TRANSFER:
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
                
                cols_coll.push_back(cols);
                for(int i=0;i<5;i++){
                    col_lengths[i] = std::max(col_lengths[i], int(cols[i].size()));
                }
            }

            for(auto it:cols_coll){
                char temp_buff[200];
                
                int space_sep = 4;
                snprintf(temp_buff, 200, "%*s%*s%*s%*s%*s%*s%*s%*s%*s", col_lengths[0],it[0].c_str(), space_sep, "", col_lengths[1],it[1].c_str(), space_sep, "" ,col_lengths[2],it[2].c_str(), space_sep, "", col_lengths[3],it[3].c_str(), space_sep, "", col_lengths[4],it[4].c_str());
                lines.push_back(std::string(temp_buff));

            }

            return lines;
        }


}





void cli_client(){
    int mode=0;
    
    // RaviBank::AccountHolder* loggedInHolder = nullptr;
    int read_from_file = ncurses_menu({"Open New Bank", "Read Data From File"});
    WorldBank::Bank* bank_ptr;
    if(read_from_file){
         bank_ptr = WorldBank::read_data_file("./.bankdata");
        if(bank_ptr != nullptr){
            
        }
        else{
            ncurses_flash("Failed to read from file");
            read_from_file = false;
        }
    }
    if(!read_from_file){
        auto manager_username = ncurses_input_string("Set Manager Username:");
        auto manager_password = ncurses_input_string("Set Manager Password:", true);
        bank_ptr = new WorldBank::Bank(manager_username, manager_password);
    }
    WorldBank::Bank bank = (*bank_ptr);
    
    POI
    // RaviBank::Bank bank = (*bank_ptr);
    
    
    // RaviBank::Bank::Account acct(10, 11);
    initscr();
    noecho();
    cbreak();
    
    while(1){
        if (mode == 0){
            mode = 1 + ncurses_menu({"Login as Customer", "Register as New Customer", "Login as Bank Manager", "Write to File", "Quit"});
            printf("Done");
            // break;
        }
        else if (mode == 1){
            std::string username = ncurses_input_string("Username: ");
            std::string password = ncurses_input_string("Password: ", true);
            if (bank.loginHolder(username, password)){
                ncurses_flash("Login Successful");
                mode = 7;
            }
            else{
                ncurses_flash("Incorrect username or password");
                mode - 0;
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
        else if (mode == 3){
            std::string manager_username = ncurses_input_string("Manager Username:");
            std::string manager_pwd = ncurses_input_string("Manager Password:", true);
            if(bank.loginManager(manager_username, manager_pwd)){
                ncurses_flash("Manager login successful");
                while(1){
                    int choice = ncurses_menu({"See All Holders", "See All Accounts", "See All Transactions", "Fast Forward", "Logout"});

                    if(choice == 0){
                        // auto holder_lines = RaviBank::generate_holder_table(bank.holders);
                        
                        int holder_index = ncurses_menu(WorldBank::generate_holder_table(bank.holders), true);
                        if(holder_index != -1){
                        int account_index = ncurses_menu(bank.bank_manager.generate_account_table(bank.holders[holder_index]->getAccounts()), true);
                        POI
                        if(account_index != -1)
                            int transaction_index = ncurses_menu(WorldBank::generate_statement_table(bank.accounts[account_index]->get_statement()), true);
                        }
                    }
                    else if(choice == 1){
                        int account_index = ncurses_menu(bank.bank_manager.generate_account_table(bank.accounts), true, "Choose Account to View Transactions");
                        if(account_index != -1)
                            int transaction_index = ncurses_menu(WorldBank::generate_statement_table(bank.accounts[account_index]->get_statement()), true);
                    }
                    else if(choice == 2){
                        int choice = ncurses_menu(WorldBank::generate_statement_table(bank.get_transactions()), true);
                    }
                    else if(choice == 3){
                        time_t days = ncurses_int_input("Enter Days to Fast Forward: ");
                        bank.fast_forward(days*DURATION_DAY);
                        ncurses_flash("Updated balances");
                    }
                    else{
                        mode = 0;
                        bank.logout();
                        break;
                    }
                }
            }
            else{
                ncurses_flash("Incorrect credentials, try again");
                mode = 0;
            }
        }
        else if (mode == 4){
            if(bank.write_to_file()){
                ncurses_flash("Wrote succsefully");
            }
            else{
                ncurses_flash("Failed to write");
            }
            mode = 0;
        }
        else if (mode == 5){
            return;
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
                    int account_action = ncurses_menu({"View Statement","View Account Details", "Deposit", "Withdraw", "Transfer", "Close Account", "Cancel"});
                    account_action-=2;
                    if(account_action == -2){
                        std::cout << std::endl << std::endl;
                        ncurses_menu(WorldBank::generate_statement_table(account->get_statement()), true);
                        

                    }
                    else if(account_action == -1){
                        ncurses_menu(bank.bank_manager.generate_account_table({account}), true);
                        // char temp[100];
                        // snprintf(temp, 100, "Balance: %.2f", account->get_balance());
                        // ncurses_flash(temp);
                    }
                    else if(account_action == 0){
                        double amount = ncurses_double_input("Deposit amount: ");
                        
                        printf("1372");
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
                        acc = bank.createAccount(1);
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
    // try{
    //     std::cout << std::stoi("ab134asdf"); 
    // }
    // catch(std::exception err){
    //     printf("Hello");
    // }
    // std::cout << RaviBank::compound_calculator(10000, 5, 2*DURATION_YEAR, DURATION_YEAR);
    
    cli_client();
    // if(RaviBank::read_data_file("./.bankdata")){
    //     std::cout << "Succcess";
    // }
    // else{
    //     std::cout << "Failure";
    // }
    endwin();
}
