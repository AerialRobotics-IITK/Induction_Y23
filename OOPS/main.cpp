//bank cli app using oops
//user class with all the functions
//bank account class which will have username  as parameter
//admin class which will have all the functions

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

struct transaction
{
	string type;
	double amount;
	string date;
	transaction(string type, double amount, string date)
	{
		this->type = type;
		this->amount = amount;
		this->date = date;
	}
};

class bankAccount
{ //variables under bankAccount should be accountNumber, balance, opendate, type which can be savings or current, and a vector of transactions for transaction history
//functions should deposit(), withdraw(), transfer()
private:
	string accountNumber;
	double balance;
	string openDate;
	string type;
	vector<transaction> transactions;
public:
	bankAccount(string accountNumber, double balance, string openDate, string type)
	{
		this->accountNumber = accountNumber;
		this->balance = balance;
		this->openDate = openDate;
		this->type = type;
	}
	void deposit(double amount)
	{
		balance += amount;
		transaction t("Deposit", amount, date());
		transactions.push_back(t);
	}
	void withdraw(double amount)
	{
		if (balance - amount < 0)
		{
			std::cout << "Insufficient funds" << endl;
		}
		else
		{
			balance -= amount;
			transaction t("Withdraw", amount, date());
			transactions.push_back(t);
		}
	}
	void transfer(double amount, bankAccount &receiver)
	{
		if (balance - amount < 0)
		{
			std::cout << "Insufficient funds" << std::endl;
		}
		else
		{
			balance -= amount;
			receiver.deposit(amount);
			transaction t("Transfer", amount, date());
			transactions.push_back(t);
		}
	}
	int getBalance()
	{
		return balance;
	}
	string getAccountNumber()
	{
		return accountNumber;
	}
	string getType()
	{
		return type;
	}
	size_t getTransactionsSize() const {
        return transactions.size();
    }
	string getTransactionType(int index){
		return transactions[index].type;
	}
	double getTransactionAmount(int index){
		return transactions[index].amount;
	}
	string getTransactionDate(int index){
		return transactions[index].date;
	}
	void addTransaction(transaction t)
	{
		transactions.push_back(t);
	}
	virtual void addInterest(int days) = 0;
	string date() {
		auto t = std::time(nullptr);
		auto timePtr = std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(timePtr, "%d-%m-%Y");
		return oss.str();
	}
};

class bankAccountHolder
{//use private and public to make the variables and functions private and public
//variables under user should be name, username, netbanking password and list of bankAccounts under this user
private:
	string name;
	string username;
	string netBankingPassword;
	vector<bankAccount> bankAccounts;
public:
	bankAccountHolder(string name, string username, string netBankingPassword)
	{
		this->name = name;
		this->username = username;
		this->netBankingPassword = netBankingPassword;
	
	}
	//functions should be getAccounts(), changePassword() and createAccount()
	void listAccounts()
	{
		//print with widths of 20 and pipes running through the columns
		std::cout << left << setw(20) << "Account Number" << "|" << setw(20) << "Balance" << "|" << setw(20) << "Type" << "|" << endl;
		std::cout << "-----------------------------------------------" << endl;
		for (int i = 0; i < bankAccounts.size(); i++)
		{
			std::cout << left << setw(20) << bankAccounts[i].getAccountNumber() << "|" << setw(20) << bankAccounts[i].getBalance() << "|" << setw(20) << bankAccounts[i].getType() << "|" << endl;
		}
	}
	void createAccount(string accountNumber, double balance, string openDate, string type)
	{
		//create a new derived class object and add it to the bankAccounts vector
		savingsAccount b(accountNumber, balance, openDate); // Remove the 'type' argument
		bankAccounts.push_back(b);
	}
};



class branchManager
{//variables under admin should be username and password
//methods should getStatementOfAccount(), getAccountHolders(), fastforward()
private:
	string username;
	string password;
public:
	branchManager(string username, string password)
	{
		this->username = username;
		this->password = password;
	}
	void getStatementOfAccount(bankAccount &account)
	{
		std::cout << left << setw(20) << "Type" << "|" << setw(20) << "Amount" << "|" << setw(20) << "Date" << "|" << endl;
		std::cout << "-----------------------------------------------" << endl;
		for (int i = 0; i < account.getTransactionsSize(); i++)
		{
			std::cout << left << setw(20) << account.getTransactionType(i) << "|" << setw(20) << account.getTransactionAmount(i) << "|" << setw(20) << account.getTransactionDate(i) << "|" << endl;
		}
	}
	string getName() {
		return name;
	}
	void getAccountHolders(vector<bankAccountHolder> &accountHolders)
	{
		std::cout << left << setw(20) << "Name" << "|" << setw(20) << "Username" << "|" << endl;
		std::cout << "-----------------------------------------------" << endl;
		for (int i = 0; i < accountHolders.size(); i++)
		{
			std::cout << left << setw(20) << accountHolders[i].getName() << "|" << setw(20) << accountHolders[i].getUsername() << "|" << endl;
		}
	}
	void fastForward(int days, vector<bankAccount> &accounts)
	{
		//call addInterest() for each account in accounts
		for (int i = 0; i < accounts.size(); i++)
		{
			accounts[i].addInterest(days);
		}
	}
};

class savingsAccount : public bankAccount {
private:
	double interestRate;
public:
	savingsAccount(string accountNumber, double balance, string openDate, string type, double interestRate) : bankAccount(accountNumber, balance, openDate, type)
	{
		this->interestRate = interestRate;
	}
	double getInterestRate()
	{
		return interestRate;
	}
	void setInterestRate(double interestRate)
	{
		this->interestRate = interestRate;
	}
	void addInterest(int days)
	{
		double balance = getBalance();
		double interest =  balance * interestRate * days / 365;
		balance += interest;
		transaction t("Interest", interest, date());
		addTransaction(t);
	}
	string date() {
		auto t = std::time(nullptr);
		auto timePtr = std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(timePtr, "%d-%m-%Y");
		return oss.str();
	}
};

//current account inherits from bankAccount
class currentAccount : public bankAccount
{
	//has attribute interest rate which is always 0
	//method getInterestRate() should return 0

public:
	currentAccount(string accountNumber, double balance, string openDate, string type) : bankAccount(accountNumber, balance, openDate, type)
	{
	}
	void addInterest(int days)
	{
	}
	double getInterestRate()
	{
		return 0;
	}
};

void register(){
	string name, username, netBankingPassword;
	std::cout << "Enter name: ";
	cin >> name;
	std::cout << "Enter username: ";
	cin >> username;
	std::cout << "Enter netbanking password: ";
	cin >> netBankingPassword;
	//check if username already exists
	//if it does, print "Username already exists"
	//else, create a new bankAccountHolder object and add it to the accountHolders vector
	//print "Registration successful"
	//check in accountHolders
	for (int i = 0; i < accountHolders.size(); i++)
	{
		if (accountHolders[i].username == username)
		{
			std::cout << "Username already exists" << endl;
			return;
		}
	}
	//create a new bankAccountHolder object and add it to the accountHolders vector
	bankAccountHolder b(name, username, netBankingPassword);
	accountHolders.push_back(b);
	std::cout << "Registration successful" << endl;
}

int main(){
	//object with all the bankAccountHolders
	vector<bankAccountHolder> accountHolders;
	int input;
	//print out options line by line with numbers
	std::cout << "1. Register" << endl;
	std::cout << "2. Login" << endl;
	std::cout << "3. Exit" << endl;
	cin >> input;
	if (input == 1)
	{
		//register
		register();
	}
	else if (input == 2)
	{
		//login
	}
	else if (input == 3)
	{
		//exit
	}
	else
	{
		std::cout << "Invalid input" << endl;
	}
	return 0;
}