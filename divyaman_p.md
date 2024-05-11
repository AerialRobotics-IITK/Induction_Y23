Bank Management System
This repository contains a simple Bank Management System implemented in C++. The system allows users to sign up, create bank accounts, deposit and withdraw funds, view account statements, and provides a branch manager interface for administrative tasks.

Components
BankAccount Class
The BankAccount class represents a generic bank account. It has attributes such as accountNumber, balance, openDate, and transactionHistory. This class provides methods to deposit, withdraw funds, and display account statements.

SavingsAccount Class
The SavingsAccount class inherits from BankAccount and represents a savings account. It includes an additional attribute interestRate and a method depositInterest() to calculate and deposit interest.

CheckingAccount Class
The CheckingAccount class inherits from BankAccount and represents a checking account. It does not have an interest rate.

BankAccountHolder Class
The BankAccountHolder class represents a bank account holder. It contains attributes such as name, username, netBankingPassword, and a vector of accounts. It provides methods to create accounts, deposit, withdraw, and display statements.

BranchManager Class
The BranchManager class implements a singleton pattern and represents the branch manager of the bank. It manages authentication, provides operations like listing account holders, getting statements of specific accounts, and fast-forwarding time for interest calculation.

User Interface
The signUp() function allows users to sign up by providing their name, username, and password. The branchManagerMenu() function provides a menu for branch manager operations. The mainMenu() function provides the main user interface for account holders.

Main Function
The main() function initializes the system, sets up the branch manager, and enters an infinite loop to run the main menu.

Usage
To use the system:

Compile the code using a C++ compiler.
Run the executable file.
Follow the prompts to sign up or log in as a user or branch manager.
Perform desired operations such as creating accounts, depositing, withdrawing, or viewing statements.
FOR BRANCH MANAGER LOGIN USE 
ID - admin
password - admin123
