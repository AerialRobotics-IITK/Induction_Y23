#include <bits/stdc++.h>
using namespace std;
int i = 0;
time_t curr_time = time(0);
char *date = ctime(&curr_time);
string new_lin = "\n";
class BankAccountHolder;
// vector <BankAccountHolder> BAH;
// vector <BankAccount> BA;
string strw = "Money Withdrawn : ";
string strd = "Money Deposited : ";
string strc = "Current Balance : ";
string bm_user = "BM";
string bm_psswd = "CR7 sucks LM10isGOAT";
class BankAccount
{
    friend class BankAccountHolder;

private:
    long long int AccountNumber;
    double Balance;
    vector<string> transaction;
    vector<string> &temp = transaction;
    string opening_date;

public:
    void deposit(double amt)
    {
        cout << "Enter the amount you want you to deposit";
        // cin.ignore();
        cin >> amt;
        Balance += amt;
        string amt1 = to_string(amt);
        string cb = to_string(Balance);
        string curr_date = date;
        string fin = strd + amt1 + strc + cb + date + new_lin;
        transaction.push_back(fin);
        // break;
    }
    void withdraw(double amt)
    {
        cout << "Enter the amount you want to withdraw";
        cin >> amt;
        do
        {
            if ((Balance - amt) >= 500)
            {
                Balance -= amt;
                string amt1 = to_string(amt);
                string cb = to_string(Balance);
                string curr_date = date;
                string fin = strw + amt1 + strc + cb + date + new_lin;
                transaction.push_back(fin);
                break;
            }
            else
            {
                cout << "Withdrawing this amount leaves lesser money than the minimum limit";
                cin.ignore();
            }
        } while (1);
    }
    vector<string> getStatements()
    {
        return temp;
    }
    long long int acnum(void)
    {
        return AccountNumber;
    }
    float balance(void)
    {
        return Balance;
    }
    double *ret_balance()
    {
        return &Balance;
    }
    // void transfer(BankAccountHolder& user1,BankAccountHolder& user2,double trans_amt){
    //     // user1.
    // }
    friend class BankManager;
};
class Savings : public BankAccount
{
private:
    float int_rate = rand() % 7;

public:
    float get_int_rate(void)
    {
        return int_rate;
    }

    // void set_int_rate(void)
    // {
    //     int_rate = rand() % 7;
    // }
    friend class BankManager;
};
class Current : public BankAccount
{
private:
    float int_rate = 0;

public:
    void getInterestRate(void)
    {
        try
        {
            float tmp = int_rate;
            if (tmp == 0)
                cout << "The interest rate is 0";
            else
            {
                throw(int_rate);
            }
        }
        catch (float tmp1)
        {
            cout << "The interest rate is not zero";
            cout << "The interest rate here is " << tmp1;
        }
    }
};
class BankAccountHolder
{
    friend class BanckAccount;

private:
    string name;
    string username;
    string password;
    char type[4];
    // vector<int> account_list_by_numbers;

public:
    void signup(void)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your username: ";
        // cin.ignore();
        getline(cin, username);
        cout << "Enter your password: ";
        // cin.ignore();
        getline(cin, password);
        cout << "Online account setup,you can login to create a bank account now with user number : " << i <<" name : "<<name<<" with username : "<<username<<" and password : "<<password<<"\n";
        i++;
        // tot_signed_up++;
    }
    // void getAccounts(void)
    // {
    //     cout << "Your name : " << name << endl
    //          << "Your username : " << username;
    //     for (int i = 0; i < account_list_by_numbers.size(); i++)
    //     {
    //         cout << account_list_by_numbers[i] << " ";
    //     }
    //     cout << "\n";
    // }
    void changepassword(void)
    {
        do
        {
            string tmp1;
            cout << "enter your initial password";
            cin.ignore();
            getline(cin, tmp1);
            char *tmp2;
            strcpy(tmp2, tmp1.c_str());
            if (!(strcmp(tmp2, password.c_str())))
            {
                cout << "Enter your new password";
                cin.ignore();
                getline(cin, password);
                cout << "Password updated successfully";
                cin.ignore();
                break;
            }
            else
            {
                cout << "You have entered the wrong password,please try again";
                cin.ignore();
            }
        } while (1);
    }
    void createSAccount(BankAccount &user_account, Savings &suser_account)
    {
        char str[4] = "SAV";
        strcpy(type, str);
        long long int c = rand() % 1001;
        user_account.AccountNumber = c;
        suser_account.AccountNumber = c;
        cout << "You need a minimum balance of 500 to open the account,enter the money you want to deposit";
        cin.ignore();
        double balance;
        cin >> balance;
        do
        {
            if (balance > 500)
            {
                user_account.Balance = balance;
                suser_account.Balance = balance;
                break;
            }
            else
            {
                cout << "Please enter a valid ammount";
                cin.ignore();
            }
        } while (1);
        string ope_sta = "Your savings bank account has been successfully created\nCurrent Balance : ";
        string bal = to_string(balance);
        string acnum = to_string(c);
        string temp = "With Account Num : ";
        string temp1 = "With interest rate : ";
        string int_rate = to_string(suser_account.get_int_rate());
        string curr_date = date;
        ope_sta = ope_sta + bal + temp + bal + temp1 + int_rate + date + new_lin;
        user_account.transaction.push_back(ope_sta);
    }
    void createCAccount(BankAccount &user_account, Current &cuser_account)
    {
        char str[4] = "CUR";
        strcpy(type, str);
        long long int c = rand() % 1001;
        user_account.AccountNumber = c;
        cuser_account.AccountNumber = c;
        cout << "You need a minimum balance of 500 to open the account,enter the money you want to deposit";
        cin.ignore();
        double balance;
        cin >> balance;
        do
        {
            if (balance > 500)
            {
                user_account.Balance = balance;
                cuser_account.Balance = balance;
                break;
            }
            else
            {
                cout << "Please enter a valid ammount";
                cin.ignore();
            }
        } while (1);
        string ope_sta = "Your current bank account has been successfully created\nCurrent Balance : ";
        string bal = to_string(balance);
        string acnum = to_string(c);
        string temp = "With Account Num : ";
        string curr_date = date;
        ope_sta = ope_sta + bal + temp + bal + date + new_lin;
        user_account.transaction.push_back(ope_sta);
    }
    string Username(void)
    {
        return username;
    }
    string Password(void)
    {
        return password;
    }
    friend class BankManager;
};

vector<BankAccountHolder> BAH;
vector<BankAccount> BA;
vector<Savings> SBA;
vector<Current> CBA;
class BankManager
{
    // friend class BankAccount;
    // friend class BankAccountHolder;

public:
    string username;
    string password;
    void getStatementOfAccount(int user_num)
    {
        cout << "Your username : " << BAH[user_num].Username() << "\n"
             << "The statement of your account reads as follows : ";
        for (int i = 0; i < BA[user_num].getStatements().size(); i++)
        {
            cout << BA[user_num].getStatements()[i];
        }
    }
    void listofaccounts(int i)
    {
        for (int j = 0; j < i; j++)
        {
            cout << "Name : " << BAH[j].Username() << "Account Number :" << BA[j].acnum() << "\n";
        }
    }
    double fastforward(int days, Savings &account)
    {
        double *curr_bal = account.ret_balance();
        double bal = *curr_bal;
        int int_rate = account.get_int_rate();
        int num = days / 30;
        double new_bal = bal * (1 + double(((num) * (int_rate))) / 100);
        // double*
        *curr_bal = new_bal;
        string temp = "Your account has been fast-forwarded, new balance = ";
        string new_ba = to_string(new_bal);
        string curr_date = date;
        string fin = temp + new_ba + curr_date + new_lin;
        return *curr_bal;
        // return new_bal;
        /*try to update the balance here like how to update a private variable here*/
    }
};
int main()
{
    int check = 0;
    while (!check)
    {
        cout << "Enter C if you are a customer and B if you are the manager" << endl;
        char tmp;
        cin >> tmp;
        if (tmp == 'C')
        {
            check = 1;
            do
            {
                cout << "Enter S if you want to signup and L if you want to login" << endl;
                cin >> tmp;
                if (tmp == 'S')
                {
                    check = 0;
                    BankAccountHolder user;
                    user.signup();
                    BAH.push_back(user);
                    
                }
                else if (tmp == 'L')
                {
                    cout << "Enter your user number : ";
                    // cin.ignore();
                    int user_num;
                    cin >> user_num;
                    cout<<user_num;
                    string tmp1;
                    string tmp2;
                    check = 0;
                    cout << "Enter your username: ";
                    cin.ignore();
                    getline(cin, tmp1);
                    cout <<tmp1<< "Enter your password: ";
                    // cin.ignore();
                    getline(cin, tmp2);
                    if (((BAH[user_num].Username()== tmp1)) && (BAH[user_num].Password() == tmp2))
                    {
                        char tmp;
                        cout << "Enter Y if you want to create a bank account,S to view statement ,W to make withdrawl, D for a deposit and L for a logout\n";
                        cin.ignore();
                        cin >> tmp;
                        if (tmp == 'Y')
                        {
                            char s;
                            cout << "enter S for a savings account and C for a current account";
                            cin.ignore();
                            cin >> s;
                            if (s == 'S')
                            {
                                BAH[user_num].createSAccount(BA[user_num], SBA[user_num]);
                            }
                            else
                            {
                                BAH[user_num].createCAccount(BA[user_num], CBA[user_num]);
                            }
                        }
                        else if (tmp == 'S')
                        {
                            for (int i = 0; i < BA[user_num].getStatements().size(); i++)
                            {
                                cout << BA[user_num].getStatements()[i];
                            }
                        }
                        else if (tmp == 'W')
                        {
                            double tmp;
                            cout << "Enter the amount you want to withdraw";
                            cin.ignore();
                            cin >> tmp;
                            BA[user_num].withdraw(tmp);
                        }
                        else if (tmp == 'D')
                        {
                            double tmp;
                            cout << "Enter the amount you want to deposit";
                            cin.ignore();
                            cin >> tmp;
                            BA[user_num].deposit(tmp);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    cout << "You have chosen a wrong option kindly retry." << endl;
                }
            } while (check);
        }
        else if (tmp == 'B')
        {

            string tmp1, tmp2;
            cout << "Enter your username : ";
            cin.ignore();
            getline(cin, tmp1);
            cout << "Enter the password : ";
            // cin.ignore();
            getline(cin, tmp2);
            if ((tmp1 == bm_user) && (tmp2 ==  bm_psswd))
            {
                char tmp_man;
                cout << "Welcome Bank Manager\n";
                BankManager bm;
                cout << "Press S if you want statement of any account,L is you want list of account holders along with their account numbers and F for fastforwarding aany account";
                cin.ignore();
                cin >> tmp_man;
                if (tmp_man == 'S')
                {
                    cout << "Enter the user number for which details are required";
                    int a;
                    cin >> a;
                    bm.getStatementOfAccount(a);
                }
                else if (tmp_man == 'L')
                {
                    bm.listofaccounts(i);
                }
                else if (tmp_man == 'F')
                {
                    int days, usr_num;
                    cout << "Enter the days and the user number(in that order)";
                    // cin.ignore();
                    cin >> days >> usr_num;
                    double new_bal = bm.fastforward(days, SBA[usr_num]);

                    cout << "The new balance will be " << new_bal;
                }
            }
            else
                cout << "!!You have entered wrong or unmatching credentials you are being taken to the main login page!!";
            check = 0;
        }
        else
        {
            cout << "You have chosen an unavailable option please retry" << endl;
        }
    }
    return 0;
}
