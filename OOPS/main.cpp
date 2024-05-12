#include<bits/stdc++.h>
#include<sqlite3.h>
using namespace std;

int day ; // amount of days from a given date. all dates are relative to this day count.
int transID ; 
string theUser ;

class BranchManager
{
public:
    string username = "chandra3";
    string password = "chandraISbest@123";

    void getStatementOfAccount(int accNum);

    void getAccountHolders(){
        fstream fin1;
        fin1.open("11users.txt");
        //vector<string> row(2,0); 
        string line, word; 
        getline(fin1, line);
        while (getline(fin1, line)){
            //cout << line << endl ;
            stringstream s(line);
            while(s >> word){
                cout << word.c_str() << endl;
                break;
            }
        }
    fin1.close();
    return;
    }

    void fastforward();
};

class BankAccount
{
public:
    int accNo;
    int balance;
    int opendate;
    //string bank statement[];
    string getStatements();

    void addStatements(char st, int amt){
        fstream fout;
        fout.open("11statement.txt", ios::out | ios::app);
        fout << accNo << " " << ++transID << " "  << st << " "  << amt << " "  << balance << "\n";
    fout.close();
    return;
    }

    void deposit(int amt){
        balance += amt ;
        addStatements('d',amt);
    }
    void withdraw(int amt){
        balance -= amt ;
        addStatements('d',amt);
    }
    void transfer(int amt){
        balance -= amt ;
        addStatements('d',amt);

    }
};

class SavingsAccount : public BankAccount
{
private:
    float interestRate;
public:
    float getRate(){
        return interestRate;
    };
    void setRate(float newRate){
        interestRate = newRate;
        cout << "Updated interest rate is " << interestRate << endl;
    };
};

class CheckingsAccount : public BankAccount
{
    int interestRate = 0;
    int getRate(){
        //try catch bs
        return 0;
    };
};

class BankAccountHolder
{
private:
    //data
public:
    string name;
    string username;
    string password;
    //list of bank accounts

    string getAccounts(){
        //csv
        fstream fin2;
        fin2.open("11accounts.csv", ios::in);
        return "0";
    }

    string getPassword(string user){
        fstream fin1;
        fin1.open("11users.txt");
        string line, word; 
        getline(fin1, line);
        while (getline(fin1, line)){
            stringstream s(line);
            while(s >> word){
                if (word.c_str()== user){
                    s >> word;
                    cout << word.c_str() << endl;
                    return word.c_str();
                }
                else continue;
            }
        }   
    fin1.close();
    return "ERR";
    }

    void createPassword();

    void createAccount(){
        BankAccount acc ;
        fstream fin1;
        fin1.open("11accounts.txt");
        string line, word; 
        while (getline(fin1, line)){
            stringstream s(line);
            while(s >> word){
                acc.accNo = stoi(word) +1;
            }
        }   
        fin1.close();
        cout << "Enter deposit amount" << endl;
        cin >> acc.balance;
        acc.deposit(acc.balance);
        acc.opendate = day;
        cout << "Select account type\n 1. Checking Account \n 2. Savings Account \n" ;
        int ch;
        char type;
        cin >> ch ;
        switch(ch){ //idk make some diff b/w both
        case 1: 
            cout << "Savings account created." << endl ;
            type = 's';
            break;
        case 2: 
            cout << "Checking account created." << endl ;
            type = 'c';
            break;
        default: 
            break;
        }
        fstream fout;
        fout.open("11accounts.txt", ios::out | ios::app);
        fout << acc.accNo << theUser << type << acc.balance << day ;
        fout.close();
        return;
    }
};

int firstChoice(){
    cout << "Hello! Welcome to the Babu Bank of India (BBI)\n";
    cout << "Please select what you would like to do today\n";
    cout << "1. Login as Account-Holder\n";
    cout << "2. Don't have an account? Sign up here\n";
    cout << "3. Forgot your password. Reset here\n";
    cout << "4. Login as Bank-Manager\n";
    int ch;
    cin >> ch;
    return ch;
}

int manChoice(){
    cout << "Success! You have logged in as Branch Manager." << endl ;
    cout << "What would you like to do today?\n";
    cout << "1. Get statement of accounts\n";
    cout << "2. Get account holders\n";
    cout << "3. Fast Forward\n";
    int ch;
    cin >> ch;
    return ch;
}

void userChoice(){
    cout << "\nWhat would you like to do today?\n";
    cout << "1. Create a new Savings/Checking Account\n";
    cout << "2. Deposit,Withdraw or Transfer Money\n";
    cout << "3. \n";
    cout << "4. Display all your current accounts\n";
    cout << "5. Get statement of your accounts\n";
    cout << "6. Log Out.\n";
    int ch,amt;
    cin >> ch;
    char dwt;
    BankAccountHolder bah;
    BankAccount ba;
    switch(ch){
        case 1: 
            bah.createAccount();
            break;
        case 2: 
            cout << "Enter amount\n";
            cin >> amt;
            cout << "Do you want to deposit/ withdraw/ transfer? (d/w/t)\n" ;
            cin >> dwt ;
            switch(dwt){
                case 'd' :
                    ba.deposit(amt); break;
                case 'w' :
                    ba.withdraw(amt); break;
                case 't' :
                    ba.transfer(amt); break;
                default : cout << "Error\n" ; break;
            }
            break;
        case 3: 
            break;
        case 4: 
            break;
        case 5: 
            break;
        case 6: 
            return;
            break;
        default: 
            break;
    }
    userChoice();
    return;
}

string readUsers(string user){ // unused func for trial
    fstream fin1;
    fin1.open("11users.txt");
    //vector<string> row(2,0); 
    string line, word; 
    getline(fin1, line);
    while (getline(fin1, line)){
        //cout << line << endl ;
        stringstream s(line);
        while(s >> word){
            //cout << word.c_str() << endl;
            if (word.c_str()== user){
                s >> word;
                //cout << word.c_str() << endl;
                return word.c_str();
            }
            else continue;
        }
    }
    fin1.close();
    return "ERR";
    //string username, pass, manager;
    //while (fin1 >> username >> "," >> pass >> "," >> manager) { 
        // row.clear(); 
        // cout << "\n"; 
        // getline(fin1, line); 
        // //cout << line ;
        // stringstream s(line); 
        // string username, pass, manager; 
        // s << username << "," << pass << "," << manager ;
        // cout << pass;
        // while (getline(s, word, ',')) { 
        //     cout << word << "\t";
        //     row.push_back(word); 
        // }
        // if(user == user){
        //     cout << "Found";
        //     return row[1];
        // }
    // }
}

void setGlobal(){ 
    fstream fin1;
    fin1.open("11statement.txt");
    string line, word; 
    getline(fin1, line);
    while (getline(fin1, line)){
        stringstream s(line);
        s >> word;
        s >> word;
        //transID = stoi(word.c_str()) ;
        s >> word;
        s >> word;
        s >> word;
        s >> word;
        //day = stoi(word.c_str()) ;
    }
    fin1.close();
    return;
}

int main(){
    std::string secpass, chpass1, chpass2, manusern, manpass, newusern, usern, pass, chk;
    BranchManager man;
    BankAccountHolder bah;
    setGlobal();
    cout << transID << "\t" << day ;
    int ch = firstChoice();
    switch(ch)
    {
    case 0: 
        //trials
        //readUsers();
        break;
    case 1: 
        //login process... verify if acc exists and login
        cout << "Enter your username\n";
        cin >> usern;
        pass = bah.getPassword(usern); // returns password
        //cout << pass << endl ;
        if (pass == "ERR") cout << "No such user found\n" ;
        else {
        cout << "Enter your password\n";
        cin >> chk;
            if(chk == pass){
                cout << "Success! You have logged in." << endl ;
                userChoice() ;
            }
            else cout<< "Incorrect Password. Try Again.\n";
        }
        break;
    
    case 2:
        cout << "Create a new account\n";
        cout << "Enter a valid username. Only letters numbers and underscores are allowed\n";
        cin >> newusern ;
        bah.username = newusern;
        bah.createAccount();
        cout << "Set your password\n";
        cin >> chpass1;
        cout << "Re-enter your password\n";
        cin >> chpass2;
        if(chpass1 == chpass2){
            //BankAccountHolder::createPassword();
            cout << "Success! Your account has been created. Please exit and login again to enter your account" << endl;
        }
        //add acc to list
        break;

    case 3: 
        cout << "Enter your username" << endl;
        cout << "Please enter the numbers seen on the screen. 5g9hb833" << endl;
        cin >> secpass ;
        if (secpass == "5g9hb833") {
            // add lines from case 2
        }


    case 4:
        cout << "Enter your manager username\n";
        cin >> manusern;
        if(man.username == manusern){
            cout << "Enter your password\n";
            cin >> manpass;
            if(man.password == manpass){
                cout << "Login Success!" << endl ;
                int chman = manChoice();
                switch(chman){
                    case 1: "Enter account number to view details\n" ;
                        //man.getStatementOfAccount(int accNum);
                        //here
                        break;
                    case 2:
                        //accounts
                        //man.getAccountHolders();
                        break;
                    case 3:
                        //fastt
                        //man.fastforward();
                        break;
                    default: break;
                }

            }
            else {
                cout << "Password did not match. Please try again." << endl ;
            }
        }
        else {
            cout << "No such user found. Try again." << endl ;
        }
        break;
    
    default:
        cout << "No such option found. Please try again." << endl;
        break;
    }

    return 0;
};
