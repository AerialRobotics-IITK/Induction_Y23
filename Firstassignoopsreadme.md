
>-We have defined a glocal list accounts of type Bankaccntholder to keep track of all people making an account in the bank 

># Defining Bankaccntholder class
>
> - we have mainly two functions changepassword() and getaccount()
> - the get() function is used to set username and password as they are private members and cannot be directly accessed .
> - and there is a pointer function o link BankAccount class to Bankaccntholder 

># Defining its functions
> -changepassword helps to enumerate among all accounts by matching username to reach the account we are talking about and then helps to change the password to the one taken as inout from the user 
>- setaccountdetails helps to link the person to a bankaccount 


># Definig BankAccount class

>-it has three functions transfer,deposit and withdraw 
> -it has a list of string type called transaction which keeps track of transactions made in the account 
> - it also has function getbalance to be able to retrieve the balance in the account at any given time 


># Derived classes : Savingsaccount and Checkingaccount
>-we earlier madebalance as a protected member so that it can be acessed by both these account types 
>-we define constructor in both accounts 
>- We also use bool value of isopen to close the accounts
>- Interest Rate for saving account is dependent on balance and the time spent since opening of the account 


># We define Bankaccntholder 
> ### We had to find the only human readable file in the inhere directory
>
> - we used ssh bandit4@bandit.labs.overthewire.org -p 2220 to log into the fourth level where we entered the password we were given 
> - There was only one directory we found running on the bandit server when we did ls -alps by that name 
> - We cd inhere/ to open the directory
> - we simply find . -type f |xargs file , and end up with file07 , the only one with ASCII TEXT in it. Then we cat file07 to find the password for **level 5**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 5
> ### We had to find a human readable , 1033 bytes and non-executable file in inhere directory 
> - we used ssh bandit5@bandit.labs.overthewire.org -p 2220 to log into the fifth level where we entered the password we were given 
> - There was only one directory we found running on the bandit server when we did ls -alps by that name 
> - We cd inhere/ to open the directory
> - we simply find . -type f -size 1033c ! executable to find the file. we then cat file name for password for **level 6**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 6
> ### We had to find a file somewhere on the server owned by user bandit7 , group bandit6 , 33 bytes in size 
> - we used ssh bandit6@bandit.labs.overthewire.org -p 2220 to log into the fifth level where we entered the password we were given 
>- We simply had to type find / -type f - user bandit7 - group bandit6 size 33c , and then locate the password among all the files it located satisfying this criteria  
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 7
> ### We had to find the password next to the word millionth in data.txt
> - we used ssh bandit7@bandit.labs.overthewire.org -p 2220 to log into the seventh level where we entered the password we were given 
> - we cat the data.txt file
> - we type in strings data.txt | grep millionth  for password for **level 6**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 8
> ### We had to find the only line which occurs once in the data.txt file 
> - we used ssh bandit8@bandit.labs.overthewire.org -p 2220 to log into the fifth level where we entered the password we were given 
> - we cat the data.txt file
> - we write sort data | uniq -c to get how many times each line occurs and the line occuring once is the password for **level 9**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 9
> ### We had to find one of the few human readable strings which has a lot of '-' in the start 
> - we used ssh bandi9@bandit.labs.overthewire.org -p 2220 to log into the ninth level where we entered the password we were given 
> - we write strings data.txt | grep '='
> - thus we analyse and get the password for **level 9**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 10
> ### We had to find the password in data.txt which was encoded in base64
> - we used ssh bandit10@bandit.labs.overthewire.org -p 2220 to log into the tenth level where we entered the password we were given 
> -we write base64 -d data.txt to decode and find the password for **level 9**. 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 11
> ### We had to find the password in data.txt where all the lowercase and uppercase letters had been rotated by 13 positions
> - we used ssh bandit11@bandit.labs.overthewire.org -p 2220 to log into the eleventh level where we entered the password we were given 
> -I could not find the command to decode the code stored on typing cat data.txt so I converted it using the net 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 12
> ### We had to find the password in data.txt which was encoded in base64
> - we used ssh bandit10@bandit.labs.overthewire.org -p 2220 to log into the eleventh level where we entered the password we were given 
> - xxd -r data.txt > data 
> - We proceeded to exit from the bandit server by typing exit

># LEVEL 13
> ### We had to find the password in data.txt which was encoded in base64
> - we used ssh bandit10@bandit.labs.overthewire.org -p 2220 to log into the tenth level where we entered the password we were given 
> -we write base64 -d data.txt to decode and find the password for **level 9**. 
> - We proceeded to exit from the bandit server by typing exits
># LEVEL 14
># LEVEL 15
