#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>


using namespace std;

struct transaction {
	string date;
	string type;
	float amount;
};

class bankAccount {
private:
	int acc_no;
	float balance;
	string open_date;
	string type;
	vector<transaction> transactions;

public:
	bankAccount(int acc_no, float balance, string open_date, string type){
		this->acc_no = acc_no;
		this->balance = balance;
		this->open_date = open_date;
		this->type = type;
	}
	void deposit(float amt) {
		balance += amt;
		transaction t;
		t.date = date();
		t.type = "deposit";
		t.amount = amt;
		transactions.push_back(t);
	}

	void withdraw(float amt) {
		if (amt <= balance) {
			balance -= amt;
			transaction t;
			t.date = date();
			t.type = "withdraw";
			transactions.push_back(t);
		}
		else {
			cout << "Can't withdraw more than current balance. Current balance: " << balance << endl;
		}
	}
	string date() {
		auto t = std::time(nullptr);
	    auto tm = *std::localtime(&t);

	    std::ostringstream oss;
	    oss << std::put_time(&tm, "%d-%m-%Y");
	    auto str = oss.str();
	    return str;

	}
};

int main(){

	auto t = time(nullptr);
    auto tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y");
    auto str = oss.str();
    cout << str;
}