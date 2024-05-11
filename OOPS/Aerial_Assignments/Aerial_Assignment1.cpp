#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include<sstream>
using namespace std;

class User
{
    public:
    string username;
    string password;
    int AccountnumS;
    int AccountnumC;
    int deposit;
    int Upperlimit;
    void changePassword(User o1);
    void createAccount(User o1);
    void getAccounts(User o1);
};

class BankManager
{
    public:
    const string username = "manager1";
    const string password = "password1";
    void managerDetails();
    
};

void BankManager::managerDetails()
{
    BankManager manager1;
    ifstream inFile("BankManager.txt");
        string line;
        vector<BankManager> lines;
        if(inFile.is_open())
        {
            lines.push_back(manager1);
            ofstream outFile("BankManager.txt",ios::app);
            if(outFile.is_open())
            {
                for(const BankManager& line : lines)
                {
                    outFile << manager1.username<<','<<manager1.password<<endl;
                    outFile.close();
                }
            }
            inFile.close();
        }

} 


void signup();
void login();
void login_questions(User o1);
void welcome();
void createSavingsAccount(User o1);
void createCurrentAccount(User o1);
void getSavingsAccount(User o1);
void getCurrentAccount(User o1);
void BankManagerlogin(BankManager o1);

void signup()
{
    User tempUser;
    string filename = "accountHolders.txt";
    cout<<"Enter a username: ";
    cin>>tempUser.username;
    cout<<"Enter a password: ";
    cin>>tempUser.password;
    ifstream inFile(filename);
    vector<User> lines;
    string line;
    string username;

    if(inFile.is_open())
    {
        while(getline(inFile, line))
        {
            size_t pos = line.find(',');
            username = line.substr(0,pos);

            if(tempUser.username == username)
            {
                cout<<"Username already exists. "<<endl;
                signup();
            }
        }
        lines.push_back(tempUser);
        ofstream outFile("accountHolders.txt",ios::app);
        if(outFile.is_open())
        {
            for(const User& line : lines)
            {
                outFile << tempUser.username<<','<<tempUser.password<<endl;
                outFile.close();
                cout<<"Signup successfull!"<<endl<<endl<<
                "Now you can login with your new id"<<endl;
            }
        }
        inFile.close();
    }
        
        login();
     
}

void login()
{
    User tempUser;
    string filename = "accountHolders.txt";
    cout<<"Enter username: ";
    cin>>tempUser.username;
    cout<<"Enter password: ";
    cin>>tempUser.password;
    ifstream inFile("accountHolders.txt");
    string line;
    string username, password;
    int count = 0;

    if(inFile.is_open())
    {
        while(getline(inFile, line))
        {
            size_t pos = line.find(',');
            username = line.substr(0,pos);
            password = line.substr(pos + 1);

            if(tempUser.username == username && tempUser.password == password)
                {
                    count = 1;
                    break;

                }
            else
            {
                count = 0;
                continue;
            }
            
        }

        if(count == 1)
        {
            cout<<"Login successful! Welcome "<<username<<endl<<endl;
            login_questions(tempUser);
            inFile.close();
        }
        else
        {
            char choice;
            cout<<"Invalid username or password"<<endl;
            cout<<"Do you want to signup?"<<endl;
            cout<<"(y/n) ";
            cin>>choice;
            if(choice == 'y')
            {
                signup();
            }
            else if(choice == 'n')
            {
                login();
            }
            else
            {
                cout<<"Invalid choice"<<endl;
                return;
            }
            inFile.close();
            return;
        }
        
        

    }
    else
    {
        cout<<"Unable to open file"<<endl;
         return;
    }

}

void login_questions(User o1)
{
    int choice;
    cout<<"How can we help you?"<<endl;
    cout<<"1. Get Accounts"<<endl;
    cout<<"2. Create Accounts"<<endl;
    cout<<"3. Change password"<<endl;
    cout<<"4. Logout"<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            o1.getAccounts(o1);
            break;
        }
        case 2:
        {
            o1.createAccount(o1);
            break;
        }
        case 3:
        {
            o1.changePassword(o1);
            break;
        }
        case 4:
        {
            cout<<""<<endl;
            welcome();
            break;
        }
    }
}

void User::changePassword(User o1)
{
    string password1;
    string password2;
    cout<<"Enter new password"<<endl;
    cin>>password1;
    cout<<"Confirm new password"<<endl;
    cin>>password2;
    if(password1 == password2)
    {
        o1.password = password2;
        ifstream inFile("accountHolders.txt");
        string line;
        string username;
        vector<string> lines;
        if(inFile.is_open())
        {
            while(getline(inFile,line))
            {
                size_t pos = line.find(',');
                username = line.substr(0,pos);
                if(o1.username != username)
                {
                    lines.push_back(line);
                }
            }
            inFile.close();
        }
        ofstream outFile("accountHolders.txt");
        if(outFile.is_open())
        {
            for(const string& line : lines)
            {
                outFile<<line<<endl;
            }
        }
        if(outFile.is_open())
        {
            outFile << o1.username<<','<<o1.password<<endl;
            outFile.close();
        }
        cout<<"Password changed successfully!"<<endl<<endl;
        login_questions(o1);
    }
    else
    {
        cout<<"The passwords doesn't match."<<endl<<"Retry!"<<endl<<endl;
        changePassword(o1);
    }

}

void welcome()
{
    int choice;
        cout<<"Welcome to Bank Management System."<<endl;
        cout<<"1. Signup"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Login as Bank Manager"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice number: "<<endl;
        cin>>choice;

        switch(choice)
        {
            case 1:
                {
                    signup();
                    break;
                }
            case 2:
               { 
                    login();
                    break;
                }
            case 3:
            {
                BankManager manager1;
                BankManagerlogin(manager1);
                break;
            }
            case 4:
                {
                    cout<<"Exiting..."<<endl;
                    break ;
                }
            default:
            {
                cout<<"Invalid choice."<<endl<<endl;
                welcome();
            }
        }

}

void User::createAccount(User o1)
{
    int choice;
    cout<<""<<endl;
    cout<<"Which type of Account do you want to create?"<<endl;
    cout<<"1. Savings Account"<<endl;
    cout<<"2. Current/Checkin Account"<<endl;
    cout<<"Enter your choice: "<<endl;
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            createSavingsAccount(o1);
            break;
        }
        case 2:
        {
            createCurrentAccount(o1);
            break;
        }
        default:
        {
            cout<<"Invalid choice"<<endl;
            login_questions(o1);
            break;
        }
    }
}

void createSavingsAccount(User o1)
{
    cout<<""<<endl;
    random_device rd;
    uniform_int_distribution<int> dist(100000000, 999999999);
    int AccountNum = dist(rd);
    o1.AccountnumS = AccountNum;
    o1.Upperlimit = 10000;
    int deposit;
    cout<<"Enter initial deposit: "<<endl;
    cin>>deposit;
    o1.deposit = deposit;
    
    ifstream inFile("SavingsAccount.txt");
    string line;
    vector<User> lines;
    if(inFile.is_open())
    {
        lines.push_back(o1);
        ofstream outFile("SavingsAccount.txt",ios::app);
        if(outFile.is_open())
        {
            for(const User& line : lines)
            {
                outFile << o1.AccountnumS<<','<<o1.deposit<<endl;
                outFile.close();
                cout<<"Your new Savings account is successfully created with the following details: "<<endl;
                cout<<"Account Number: "<<AccountNum<<endl;
                cout<<"Balance: "<<deposit<<" INR"<<endl;
                cout<<"Upper Transaction Limit: "<<o1.Upperlimit<<endl<<endl;
            }
        }
        inFile.close();
    }
    login_questions(o1);
}

void createCurrentAccount(User o1)
{
    cout<<""<<endl;
    random_device rd;
    uniform_int_distribution<int> dist(100000000, 999999999);
    int AccountNum = dist(rd);
    o1.AccountnumC = AccountNum;
    ifstream inFile("CurrentAccount.txt");
    string line;
    vector<User> lines;
    if(inFile.is_open())
    {
        lines.push_back(o1);
        ofstream outFile("CurrentAccount.txt",ios::app);
        if(outFile.is_open())
        {
            for(const User& line : lines)
            {
                outFile << o1.AccountnumC<<endl;
                outFile.close();
                cout<<"Your new Current account is successfully created with the following details: "<<endl;
                cout<<"Account Number: "<<AccountNum<<endl;
            }
        }
        inFile.close();
    }
    login_questions(o1);

}

void User::getAccounts(User o1)
{
    cout<<""<<endl;
    cout<<"Which type of account's details you would like to see?"<<endl;
    int choice;
    cout<<"1. Savings Account"<<endl;
    cout<<"2. Current Account"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            getSavingsAccount(o1);
            break;
        }
        case 2:
        {
            getCurrentAccount(o1);
            break;
        }
        default:
        {
            cout<<"Invalid choice"<<endl;
            getAccounts(o1);
            break;
        }
    }
    
}

void getSavingsAccount(User o1)
{
    if(o1.AccountnumS)
    {
        cout<<"Account number: "<<o1.AccountnumS<<endl;
        cout<<"Balance: "<<o1.deposit;
    }
    else
    {
        cout<<"You have no Savings Account."<<endl;
    }
    login_questions(o1);
}

void getCurrentAccount(User o1)
{
    if(o1.AccountnumC)
    {
        cout<<"Current Account Number: "<<o1.AccountnumC<<endl;
    }
    else
    {
        cout<<"You have no Current Account."<<endl;
    }
    login_questions(o1);
}

void BankManagerlogin(BankManager manager1)
{
    string username;
    string password;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;
    if(username == manager1.username && password == manager1.password)
    {
        int choice;
        cout<<"Logged in succesfully!"<<endl<<endl;
        cout<<"What would you like to do?"<<endl;
        cout<<"1. Get Statement of Account."<<endl;
        cout<<"2. Get Account Holder."<<endl;
        cout<<"3. Fast forward."<<endl;
        cout<<"4. Logout"<<endl;
        cout<<"Enter you choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                welcome();
                break;
            }
            default:
            {
                cout<<"Invalid choice"<<endl;
                return ;
            }
        }
    }
    else
    {
        cout<<"Invalid username or password"<<endl;
        welcome();
    }
}

int main()
{
    welcome();
    return 0;
}