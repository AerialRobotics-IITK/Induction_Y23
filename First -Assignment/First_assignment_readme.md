
># Online Banking System 
>-We have defined a global list accounts of type Bankaccntholder to keep track of all people making an account in the bank 
>- we import the chrono header file and so that we can measure time since epoch , convert it into an integer secondsValue and use it further in calculation of interest rate 

>## Defining Bankaccntholder class
>
> - we have mainly two functions changepassword() and getaccount()
> - the get() function is used to set username and password as they are private members and cannot be directly accessed .
> - and there is a pointer function o link BankAccount class to Bankaccntholder 

>## Defining its functions
> -changepassword helps to enumerate among all accounts by matching username to reach the account we are talking about and then helps to change the password to the one taken as inout from the user 
>- setaccountdetails helps to link the person to a bankaccount 


>## Definig BankAccount class

>-it has three functions transfer,deposit and withdraw 
> -it has a list of string type called transaction which keeps track of transactions made in the account 
> - it also has function getbalance to be able to retrieve the balance in the account at any given time 


>## Derived classes : Savingsaccount and Checkingaccount
>-we earlier madebalance as a protected member so that it can be acessed by both these account types 
>-we define constructor in both accounts 
>- We also use bool value of isopen to close the accounts
>- Interest Rate for saving account is dependent on balance and the time spent since opening of the account 


># We define Bankaccntholder 
> - We define the functions needed . 
> - We create a list ownaccounts of the accounts unnder the banking account that the user has made 
> - in getAccountNumber() we return accountDetails as a pointer pointing to the Accountnumber of Bankaccount 
> -under createaccount we declare a new bankaccount and a bankaccountholder 
> - we try to set the opening balance ,, username and password of this bank account 
> - if the bank account doesnt already exist , we ensure that by enumeratin through alll accountds and comparing username to ensure uniqueness. 
> - if the account a;ready exists we try to compare and find it from our list of accounts
> - there is also a failsafe in place using while(1) which ensures in case no such account exists with the help of the flag value we are able to identify that 
> -we set accountnumber in order of the bankaccounts being formed 
> -we include BAH in the list of accounts 
> -We ask if they want to open a savings or current account and then push_back said account into the ownaccounts list


>## We define Branch Manager 
 
> - we create it as a singleton object
> - we make the branch manager a static instance pointer which is not changed in creation of multiple objects and remains the same 
> -initialy instance is a nullptr
> - function fastforwarrd skips days on which the iinterestrate is dependent 
>



